#include <Adafruit_GFX.h>
#include <Adafruit_GrayOLED.h>
#include <Adafruit_SPITFT.h>
#include <Adafruit_SPITFT_Macros.h>
#include <gfxfont.h>
#include <SpeedyStepper.h>

#include <ezButton.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "RTClib.h"

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define LOGO_HEIGHT  128 // Height of OLED
#define LOGO_WIDTH    64 // Width of OLED

//----BUTTONS
#define UpButton    2 // Up Button
#define MenuButton  3 // Menu Button
#define DownButton  4 // Down Button


RTC_DS3231 rtc;
SpeedyStepper stepper;

//Time
bool h12Flag;
bool pmFlag;
bool rotate;
bool toggle;

// BUTTONS
unsigned long minButtonLongPressDuration = 3000;    // Time we wait before we see the press as a long press
unsigned long buttonLongPressMillis;                // Time in ms when we the button was pressed
bool buttonStateLongPress = false;                  // True if it is a long press

const int intervalButton = 50;                      // Time between two readings of the button state
unsigned long previousButtonMillis;                 // Timestamp of the latest reading
int buttonStatePrevious = HIGH;                      // previousstate of the switch
unsigned long buttonPressDuration;                  // Time the button is pressed in ms

//// GENERAL ////

unsigned long currentMillis;          // Variabele to store the number of milleseconds since the Arduino has started

long buttonTimer = 0;
long longPressTime = 250;

boolean buttonActive = false;
boolean longPressActive = false;

//
char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
bool statechange;

uint8_t hours;
uint8_t minutes;
uint8_t seconds;

uint8_t new_hours;
uint8_t new_minutes;
uint8_t new_seconds;

int cursor;
//
//Pin Assignments
//
const int MOTOR_STEP_PIN = 6; // MOTOR PIN
const int MOTOR_DIRECTION_PIN = 5; //MOTOR DIRECTION PIN
const byte M0Pin = 9; // MOTOR STEP
const byte M1Pin = 8; // MOTOR STEP
const byte M2Pin = 7; // MOTOR STEP
const byte Enable = 11; // ENABLE MOTOR PIN
const int SensorEmit = A0;

// ------ Buttons ------
int UpStatus;
int MenuStatus;
int DownStatus;

// -- Debounce --
int buttonState;             // the current reading from the input pin
int lastButtonState = HIGH;   // the previous reading from the input pin
unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers

const int SHORT_PRESS_TIME = 1000; // 500 milliseconds
int lastState = HIGH;  // the previous state from the input pin
int currentState;     // the current reading from the input pin
unsigned long pressedTime  = 0;
unsigned long releasedTime = 0;




int sensorValue = 0;        // value read from homing Sensor
int FEEDERMODE;             // Choosing feeder mode

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

//static const unsigned char PROGMEM logo_bmp[] =
static const unsigned char PROGMEM logo_bmp[] = {
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x7F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE,
0x5D, 0xDD, 0xDD, 0xDD, 0xDD, 0xDD, 0xDD, 0xDD, 0xDD, 0xDD, 0xDD, 0xDD, 0xDD, 0xDD, 0xDD, 0xDC,
0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06,
0x4D, 0xDD, 0xDD, 0xDD, 0xDD, 0xDD, 0xDD, 0xDD, 0xDD, 0xDD, 0xDD, 0xDD, 0xDD, 0xDD, 0xDD, 0xD4,
0x68, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x16,
0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x16,
0x68, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x16,
0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x16,
0x68, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x16,
0x48, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x14,
0x68, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x16,
0x48, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x14,
0x68, 0x60, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x16,
0x60, 0x70, 0x00, 0x00, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x16,
0x68, 0x98, 0x00, 0x00, 0xC8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x16,
0x60, 0x04, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x16,
0x68, 0x86, 0x00, 0x03, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x16,
0x48, 0x81, 0x80, 0x0C, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x14,
0x68, 0x83, 0xA0, 0x2E, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x16,
0x48, 0x81, 0xD0, 0x5C, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x14,
0x68, 0xFF, 0xFF, 0xFF, 0xF8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x16,
0x60, 0x77, 0x77, 0x77, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x16,
0x69, 0xFF, 0xFF, 0xFF, 0xFC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x16,
0x61, 0x77, 0x77, 0x77, 0x74, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x16,
0x69, 0xFF, 0xFF, 0xFF, 0xFC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x16,
0x49, 0xDD, 0xDD, 0xDD, 0xDC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x14,
0x69, 0xFF, 0xFF, 0xFF, 0xFC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x16,
0x49, 0xDD, 0xDD, 0xDD, 0xDC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x14,
0x69, 0xFF, 0xFF, 0xFF, 0xFC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x16,
0x61, 0x77, 0x77, 0x77, 0x74, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x16,
0x69, 0xEF, 0xBF, 0xEF, 0xBC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x16,
0x61, 0x77, 0x37, 0x67, 0x74, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x16,
0x69, 0xFB, 0xBF, 0xEE, 0xFC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x16,
0x49, 0x85, 0x9D, 0xCD, 0x0C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x14,
0x69, 0xFB, 0xB8, 0xEE, 0xFC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x16,
0x49, 0xD5, 0xD8, 0xDD, 0x5C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x14,
0x68, 0xEF, 0xFF, 0xFF, 0xB8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x16,
0x60, 0x77, 0x77, 0x77, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x16,
0x68, 0x7F, 0xFF, 0xFF, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x16,
0x60, 0x17, 0x77, 0x77, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x16,
0x68, 0x04, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x16,
0x48, 0x05, 0xDD, 0xDD, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x14,
0x68, 0x07, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x16,
0x48, 0x05, 0xDD, 0xDD, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x14,
0x68, 0x07, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x16,
0x60, 0x07, 0x77, 0x77, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x16,
0x68, 0x07, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x16,
0x60, 0x07, 0x37, 0x77, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x16,
0x68, 0x07, 0xBF, 0xF7, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x16,
0x48, 0x05, 0x9D, 0xD5, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x14,
0x68, 0x07, 0xBF, 0xF7, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x16,
0x48, 0x05, 0x9D, 0xD5, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x14,
0x68, 0x07, 0xBF, 0xF7, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x16,
0x60, 0x07, 0x37, 0x77, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x16,
0x68, 0x07, 0xBF, 0xF7, 0xFF, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x16,
0x60, 0x07, 0x37, 0x77, 0x77, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x16,
0x68, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x16,
0x48, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x14,
0x6F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF6,
0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04,
0x7F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE,
0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x76,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
// |----------------------------------------------|
// |                   SETUP                      |
// |______________________________________________|

void setup() {
  Serial.begin(9600); //Baud Rate
  
  // ------ Real Time Clock Setup ------
    // initializing the rtc
    if(!rtc.begin()) {
        Serial.println("Couldn't find RTC!");
        Serial.flush();
        while (1) delay(10);
    }
    if(rtc.lostPower()) {
        // this will adjust to the date and time at compilation
        rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    }
   
  // ----- DISPLAY I2C SETUP ----- 
    // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
    if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  FEEDERMODE = 0;
  toggle = false;
  
  // ----- Button ----- //
  pinMode(UpButton, INPUT_PULLUP);
  pinMode(MenuButton, INPUT_PULLUP);
  pinMode(DownButton, INPUT_PULLUP);

  statechange =  false;
  // ------ STEPPER MOTOR ------ 
  // Connect and configure stepper motor
  stepper.connectToPins(MOTOR_STEP_PIN, MOTOR_DIRECTION_PIN);
  pinMode(M0Pin, LOW);
  pinMode(M1Pin, HIGH);
  pinMode(M2Pin, HIGH);
   
  // ------ VISUALS FOR DISPLAY ------- //
  // Display Company Logo
//  CompanyIntro(); 
//  // Invert and restore display, pausing in-between
//  display.invertDisplay(true);
//  delay(1000);
//  display.invertDisplay(false);
//  delay(1000);
//  display.clearDisplay();
//  display.display();

}

// |----------------------------------------------|
// |                   LOOP                       |
// |______________________________________________|

void loop() {
  // ----- TIME ------
  DateTime now = rtc.now(); //Obtain Current Time/Date
  seconds = now.second(); // Current Seconds
  minutes = now.minute(); // Current Minutes
  hours = now.hour(); // Current Hour

  // ----- ALARM ------
  CheckAlarmTime(hours, minutes, seconds);
    if (rotate == true) {
      enableMotor();}
      
  // ----- BUTTON STATUS -----
  int UpStatus = digitalRead(2);
  int MenuStatus = digitalRead(3);
  int DownStatus = digitalRead(4);
  DebounceButton(3);
  
  currentState = MenuStatus;
  if(lastState == HIGH && currentState == LOW)        // button is pressed
    pressedTime = millis();
  else if(lastState == LOW && currentState == HIGH) { // button is released
    releasedTime = millis();

    long pressDuration = releasedTime - pressedTime;
    if( pressDuration < SHORT_PRESS_TIME )
      Serial.println("A short press is detected");
  }

  // save the the last state
  lastState = currentState;
  
  // ------ CHOOSING MODE ------
  if (MenuStatus == LOW){
    Serial.print(FEEDERMODE);
    FEEDERMODE++;
    statechange = true;
    Serial.print(FEEDERMODE);
    }if ((FEEDERMODE == 3)&&(MenuStatus == LOW)){
      FEEDERMODE = 0;
    } 
  if (UpStatus == HIGH) {
    //digitalWrite(UpButton, LOW);
    //Serial.print("Cold Day");
    } else {
    digitalWrite(UpButton, HIGH);
    enableMotor();
  }
  // ----- Display ----
  display.clearDisplay();
  MENU();
  if (FEEDERMODE == 0){ //When in Feeding Mode (idle)
    toggle = false;
    displayTime(hours, minutes, seconds);}
  if (FEEDERMODE == 1){
    setTime(hours, minutes, seconds);
    displayTime(new_hours, new_minutes, new_seconds);}
  display.display();
  delay(1000);  
}





// |---------------------------------------------|
// |                 FUNCTIONS                   |
// |---------------------------------------------|

// ----------- Display Copyright ------------------
// 
void CompanyIntro(void){
  //display.clearDisplay();
  display.setTextSize(1); // Draw 2X-scale text
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println(F("(c) Kristtiya Guerra & Co."));
  display.display();      // Show initial text
  delay(100);
  display.startscrollright(0x00, 0x1F);
  delay(2000);
  display.stopscroll();
}

// ----------- Display Time ------------------
// 
void displayTime(uint8_t hh, uint8_t mm, uint8_t ss){
char h[3];
char m[3];
char s[2];

  char *AmPm;
  if (hh <= 12)
    AmPm = "AM";
  else
    AmPm = "PM";
    
  display.setTextColor(SSD1306_WHITE);
  //Print Time to list
  sprintf(h, "%02d:", hh);
  sprintf(m, "%02d", mm);
  Serial.print(toggle);

  if(toggle == false){
      // Display Hours and Minutes
        display.setTextColor(SSD1306_WHITE);
        display.setTextSize(2); // Draw 2X-scale text
        display.setCursor(40, 30);
        display.println(h);
        display.setCursor(75, 30);
        display.println(m);
      
      // Display Seconds
        display.setCursor(105, 37);
        display.setTextSize(1);
        display.println(ss);
        display.setCursor(105, 29);
        display.println(AmPm);
  }
  if((toggle = true)&& (FEEDERMODE!=0)){ //If in changemode
    display.setTextSize(2); // Draw 2X-scale text
    if(cursor == 0){
        display.setTextColor(BLACK, WHITE);
        display.setCursor(40, 30);
        display.println(h);
        display.setTextColor(SSD1306_WHITE);
        display.setCursor(75, 30);
        display.println(m);
      // Display Seconds
        display.setCursor(105, 37);
        display.setTextSize(1);
        display.println(ss);
        display.setCursor(105, 29);
        display.println(AmPm);
        }
    if(cursor == 1){
        display.setTextColor(SSD1306_WHITE);
        display.setCursor(40, 30);
        display.println(h);
        display.setTextColor(BLACK, WHITE);
        display.setCursor(75, 30);
        display.println(m);
      // Display Seconds
        display.setTextColor(SSD1306_WHITE);
        display.setCursor(105, 37);
        display.setTextSize(1);
        display.println(ss);
        display.setCursor(105, 29);
        display.println(AmPm);
        }
    if(cursor == 2){
        display.setTextColor(SSD1306_WHITE);
        display.setCursor(40, 30);
        display.println(h);
        display.setCursor(75, 30);
        display.println(m);
      // Display Seconds
        display.setTextColor(BLACK, WHITE);
        display.setCursor(105, 37);
        display.setTextSize(1);
        display.setTextColor(SSD1306_WHITE);
        display.println(ss);
        display.setCursor(105, 29);
        display.println(AmPm);
        }
    if(cursor == 3){
        display.setTextColor(SSD1306_WHITE);
        display.setCursor(40, 30);
        display.println(h);
        display.setCursor(75, 30);
        display.println(m);
      // Display Seconds
        display.setCursor(105, 37);
        display.setTextSize(1);
        display.setTextColor(BLACK, WHITE);
        display.println(ss);
        display.setCursor(105, 29);
        display.println(AmPm);
        }
  }
}

// ----------- Sensor ------------------
void SensorCheck(){
    Serial.print("sensor = ");
    Serial.print(sensorValue);
      if (sensorValue > 500) { 
            stepper.setSpeedInStepsPerSecond(200);
            stepper.setAccelerationInStepsPerSecondPerSecond(50);
            stepper.moveRelativeInSteps(1000);
            }else {
        stepper.setSpeedInStepsPerSecond(0);      
        stepper.setAccelerationInStepsPerSecondPerSecond(0);
      }
}

// ----------- MOTOR ------------------
void enableMotor(){
  stepper.setSpeedInStepsPerSecond(90);
  stepper.setAccelerationInStepsPerSecondPerSecond(100);
  stepper.setCurrentPositionInSteps(0);
  stepper.moveRelativeInSteps(20);
  bool stopFlag = false;
 stepper.setupMoveInSteps(2000);
  while(!stepper.motionComplete())
  {
    stepper.processMovement();
    sensorValue = analogRead(SensorEmit);
    Serial.print(sensorValue);
    if ((sensorValue < 500) && (stopFlag == false))
    {
      stepper.setupStop();
      stopFlag = true;
    }
  }
}

// ----- ALARM -----
bool CheckAlarmTime(uint8_t hh, uint8_t mm, uint8_t ss){
  bool rotate = false;
  if((hh == 8) && (mm == 12) && (ss == 00)){
    Serial.print("ALARM");
    rotate = true;
  }}


// --------------- MENU ---------------

void MENU(){
  char *MODES[] = {"FEEDING MODE","CHANGE TIME","SET ALARM"};
  display.drawBitmap(0,0,logo_bmp,128,64,SSD1306_WHITE);
  display.setTextSize(1); // Draw 2X-scale text
  display.setCursor(40, 10);
  display.setTextColor(SSD1306_WHITE);
  if (statechange = true){
    display.clearDisplay();
    display.drawBitmap(0,0,logo_bmp,128,64,SSD1306_WHITE);
    display.setCursor(40, 10);
    display.println(MODES[FEEDERMODE]);
    display.setTextColor(BLACK, WHITE); //Invert Color
    display.println(MODES[FEEDERMODE]);
    display.clearDisplay();
    display.setTextColor(SSD1306_WHITE);
    display.drawBitmap(0,0,logo_bmp,128,64,SSD1306_WHITE);
    display.setCursor(40, 10);
    display.println(MODES[FEEDERMODE]);
    statechange = false;
  }else{
    statechange = false;
    display.println(MODES[FEEDERMODE]);
  }}
  
// ------ SET TIME ------
uint8_t setTime(uint8_t new_hours, uint8_t new_minutes, uint8_t new_seconds){
  cursor = 0;
  Serial.print("cursor status:");
  Serial.print(cursor);
  toggle = true;
  while(FEEDERMODE = 1){
    if (MenuStatus == LOW){
      cursor++;
      Serial.print(MenuStatus);
    }
    if (cursor = 0){//CHOOOSING HOUR
      if(UpStatus = LOW){// IF up button pressed, Increase Hour
        new_hours++;
      }if(DownStatus = LOW){// IF up button pressed, Increase Hour
        new_hours--;
      }
    }if(cursor = 1){ //CHOOSING MINUTES
      if(UpStatus = LOW){// IF up button pressed, Increase Hour
        new_minutes++;
      }if(DownStatus = LOW){// IF up button pressed, Increase Hour
        new_minutes--;
      }
    }if(cursor = 2){ //CHOOSING SECONDS
      if(UpStatus = LOW){// IF up button pressed, Increase Hour
        new_seconds++;
      }if(DownStatus = LOW){// IF up button pressed, Increase Hour
        new_seconds--;
      }
    }
    return new_hours;
    return new_minutes;
    return new_seconds;
  }  
}

// ----- DEBOUNCE BUTTON ----
bool DebounceButton(int button){
     int reading = digitalRead(button); 
      if (reading != lastButtonState) {
        lastDebounceTime = millis(); // reset the debouncing timer
      }
      if ((millis() - lastDebounceTime) > debounceDelay) {
        if (reading != buttonState) {
          buttonState = reading;
              if (buttonState == LOW) {
                return(LOW);
                Serial.print("wow");
          }
        }
      }
      lastButtonState = reading;
      return(HIGH);
      
      }



// -- BUTTON DETECTION ---- //
// provided by: https://github.com/BasOnTech/Arduino-Beginners-EN/blob/master/E15-switch-long-press/E15-switch-long-press.ino
// Function for reading the MENU button state
void readButtonState() {
  // If the difference in time between the previous reading is larger than intervalButton
  if(currentMillis - previousButtonMillis > intervalButton) {
    // Read the digital value of the button (LOW/HIGH)
    int buttonState = MenuStatus;    }
    // If the button has been pushed AND
    // If the button wasn't pressed before AND
    // IF there was not already a measurement running to determine how long the button has been pressed
    if (buttonState == LOW && buttonStatePrevious == LOW && !buttonStateLongPress) {
      buttonLongPressMillis = currentMillis;
      buttonStatePrevious = HIGH;
      Serial.println("Button pressed");
    }
    // Calculate how long the button has been pressed
    buttonPressDuration = currentMillis - buttonLongPressMillis;
    // If the button is pressed AND
    // If there is no measurement running to determine how long the button is pressed AND
    // If the time the button has been pressed is larger or equal to the time needed for a long press
    if (buttonState == LOW && !buttonStateLongPress && buttonPressDuration >= minButtonLongPressDuration) {
      buttonStateLongPress = true;
      Serial.println("Button long pressed");
    }
    // If the button is released AND
    // If the button was pressed before
    if (buttonState == HIGH && buttonStatePrevious == LOW) {
      buttonStatePrevious = LOW;
      buttonStateLongPress = false;
      Serial.println("Button released");}
      // If there is no measurement running to determine how long the button was pressed AND
      // If the time the button has been pressed is smaller than the minimal time needed for a long press
      // Note: The video shows:
      //       if (!buttonStateLongPress && buttonPressDuration < minButtonLongPressDuration) {
      //       since buttonStateLongPress is set to FALSE on line 75, !buttonStateLongPress is always TRUE
      //       and can be removed.
      if (buttonPressDuration < minButtonLongPressDuration) {
        Serial.println("Button pressed shortly");
      }
    }

//   


// seconds = (millis() / 1000) % 60; // convert to seconds, then modulo divide to 0-59 range
// minutes = (millis() /1000 / 60) % 60; // Gives int number of minutes since start - 0-59
// hours = (millis() /1000 / 3600) % 24; // Gives int number of hourse since start- 0-23
