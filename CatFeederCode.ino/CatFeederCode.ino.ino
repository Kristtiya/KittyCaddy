#include <Adafruit_GFX.h>
#include <Adafruit_GrayOLED.h>
#include <Adafruit_SPITFT.h>
#include <Adafruit_SPITFT_Macros.h>
#include <gfxfont.h>
#include <SpeedyStepper.h>

#include <EEPROM.h>
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

#define UpButton    2 // Up Button
#define MenuButton  3 // Menu Button
#define DownButton  4 // Down Button


RTC_DS3231 rtc;
SpeedyStepper stepper;


// -----------
//   TIME
// -----------
bool h12Flag;
bool pmFlag;

uint8_t hours;
uint8_t minutes;
uint8_t seconds;

uint8_t new_hours;
uint8_t new_minutes;
uint8_t new_seconds;

uint8_t alarm_hh;
uint8_t alarm_mm;
uint8_t alarm_ss;

// -----------
//   BUTTONS
// -----------
int hold; //Status for if menu button is held- 0: Short Press 1: Long Press
int UpStatus;
int MenuStatus;
int DownStatus;

// -- Debounce --
int buttonState;             // the current reading from the input pin
int currentState;     // the current reading from the input pin

int lastButtonState = HIGH;   // the previous reading from the input pin - starting at HIGH
int lastFlicker = HIGH;
unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long ButtonHoldTIme = 750;    // the debounce time; increase if the output flickers

// -----------
//   GENERAL 
// -----------
char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
bool statechange;
int clock_cursor;


// -----------
//   PIN ASSIGNMENT 
// -----------
const int MOTOR_STEP_PIN = 6; // MOTOR PIN
const int MOTOR_DIRECTION_PIN = 5; //MOTOR DIRECTION PIN
const byte M0Pin = 9; // MOTOR STEP
const byte M1Pin = 8; // MOTOR STEP
const byte M2Pin = 7; // MOTOR STEP
const byte Enable = 11; // ENABLE MOTOR PIN
const int SensorEmit = A0;


// -----------
//   STATES
// -----------
int sensorValue = 0;        // value read from homing Sensor
int FEEDERMODE;             // Choosing feeder mode
int NEWMODE;
int MODETOGGLE;
bool CURSORACTIVE;
bool changeMode;
bool rotate;
bool toggle;


// -----------
//   DISPLAY
// -----------

// -- Declaration for an SSD1306 display connected to I2C (SDA, SCL pins) --
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// -- Bitmap --
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

  // -- Setting up variables
  CURSORACTIVE = 0;
  new_hours = 0;
  new_minutes = 0;
  new_seconds = 0;

    uint8_t alarm_hh = EEPROM.read(1);
    uint8_t alarm_mm = EEPROM.read(2);
    uint8_t alarm_ss = EEPROM.read(3);
  
  clock_cursor = 0; //Set cursor for clock to 0
  FEEDERMODE = 0;
  MODETOGGLE = 0;
  NEWMODE = FEEDERMODE;
  toggle = false;
  bool rotate = false;
  statechange =  false;
  changeMode = false;

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

  // ----- Button ----- //
  pinMode(UpButton, INPUT_PULLUP);
  pinMode(MenuButton, INPUT_PULLUP);
  pinMode(DownButton, INPUT_PULLUP);

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
  //CheckAlarmTime(hours, minutes, seconds);      
  // ----- BUTTON STATUS -----
  int UpStatus = digitalRead(2); // Up Button
  int DownStatus = digitalRead(4); //Down Button
  MenuStatus = ButtonControl(3); // Menu Button

  // ----- Display ----
  display.clearDisplay();
  MENU();
  if (FEEDERMODE == 0){ //When in Feeding Mode (idle)
    displayTime(hours, minutes, seconds);}
  if (FEEDERMODE == 1){
    CURSORACTIVE = true;
      setTime(new_hours, new_minutes, new_seconds);
    }
  if(FEEDERMODE == 2){
    CURSORACTIVE = true;
    uint8_t alarm_hh = EEPROM.read(1);
    uint8_t alarm_mm = EEPROM.read(2);
    uint8_t alarm_ss = EEPROM.read(3);
    setAlarm(alarm_hh, alarm_mm, alarm_ss);
  }
  display.display();  
}

// |---------------------------------------------|
// |                 FUNCTIONS                   |
// |---------------------------------------------|

// ----- DEBOUNCE BUTTON ----
int ButtonControl(int button){
     hold = 0;
     int reading = digitalRead(button);
      if (reading != lastFlicker) {
        lastDebounceTime = millis(); // reset the debouncing timer
        lastFlicker = reading;
      }
     if (reading == LOW){
      if ((millis() - lastDebounceTime) > ButtonHoldTIme) {
        if (lastButtonState == HIGH && reading == LOW) {
          hold = 1;
          return(LOW);
        }
        else if (lastButtonState ==HIGH && reading == HIGH){
          //Serial.print("Button Released");
          lastButtonState = reading;
          return(HIGH);
          delay(100);
        }
      }
      else{
        hold = 0;
        return(reading);}
     }
     else{
      return(reading);
     }
}

// ----------- Display Time ------------------
// Used to display a time value by taking 3 inputs, hh: hours, mm: minutes, ss: seconds
// Allows to be used to display alarm and set-time, not jsut current time. 

void displayTime(uint8_t hh, uint8_t mm, uint8_t ss){
char h[3];
char m[3];
char s[3];

  char *AmPm;
  if (hh <= 12)
    AmPm = "AM";
  else
    AmPm = "PM";

  if (hh >= 13)
    hh = hh - 12;
    
  display.setTextColor(SSD1306_WHITE);
  //Print Time to list
  sprintf(h, "%02d:", hh);
  sprintf(m, "%02d", mm);
  sprintf(s, "%02d", ss);
  if(CURSORACTIVE == true){
    if(clock_cursor == 0){
          // Display Hours and Minutes
        display.setTextColor(BLACK, WHITE); //Invert Color
        display.setTextSize(2); // Draw 2X-scale text
        display.setCursor(40, 30);
        display.println(h);
        display.setCursor(76, 30);
        display.setTextColor(SSD1306_WHITE);
        display.println(m);
      // Display Seconds
        display.setCursor(105, 37);
        display.setTextSize(1);
        display.println(s);
        display.setCursor(105, 29);
        display.println(AmPm);  
    }
    if(clock_cursor == 1){
            // Display Hours and Minutes
        display.setTextColor(SSD1306_WHITE);
        display.setTextSize(2); // Draw 2X-scale text
        display.setCursor(40, 30);
        display.println(h);
        display.setTextColor(BLACK, WHITE); //Invert Color
        display.setCursor(75, 30);
        display.println(m);
      // Display Seconds
        display.setTextColor(SSD1306_WHITE);
        display.setCursor(105, 37);
        display.setTextSize(1);
        display.println(s);
        display.setCursor(105, 29);
        display.println(AmPm);
    }
    if(clock_cursor == 2){
     // Display Hours and Minutes
        display.setTextColor(SSD1306_WHITE);
        display.setTextSize(2); // Draw 2X-scale text
        display.setCursor(40, 30);
        display.println(h);
        display.setCursor(75, 30);
        display.println(m);
      // Display Seconds
        display.setTextColor(BLACK, WHITE); //Invert Color
        display.setCursor(105, 37);
        display.setTextSize(1);
        display.println(s);
        display.setTextColor(SSD1306_WHITE);
        display.setCursor(105, 29);
        display.println(AmPm);
    }
  }else{
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
        display.println(s);
        display.setCursor(105, 29);
        display.println(AmPm);
  }
      
}

// ----------- Sensor ------------------
// Used to read the homing sensor and determine if above home or not
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
// Used to rotate the motor to the next home point
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
    display.clearDisplay();
    MENU();
    display.setTextColor(SSD1306_WHITE);
    display.setTextSize(2); // Draw 2X-scale text
    display.setCursor(40, 30);
    display.println("Rotating Motor");

    if ((sensorValue < 500) && (stopFlag == false))
    {
      stepper.setupStop();
      stopFlag = true;
    }
  }
}

// ----- ALARM -----
// Used for a state change- determines if current time matches alarm
bool CheckAlarmTime(uint8_t hh, uint8_t mm, uint8_t ss, uint8_t alarm_hh, uint8_t alarm_mm, uint8_t alarm_ss){
  if((hh == alarm_hh) && (mm == alarm_mm) && (ss == alarm_ss)){
    enableMotor();
  }}

// --------------- MENU ---------------
// The Menu function determines what is being displayed on screen. It also takes in user input to change mode.
void MENU(){
  char *MODES[] = {"FEEDING MODE","CHANGE TIME","SET ALARM"}; //Current Mode
  // - BITMAP
  display.drawBitmap(0,0,logo_bmp,128,64,SSD1306_WHITE); // Draws bitmap border
  display.setTextSize(1); // Draw 2X-scale text 
  display.setCursor(40, 10); // Move cursor
  display.setTextColor(SSD1306_WHITE); // Select text color

  // - REREAD BUTTONS - for some reason, the button input read in the loop does not maintain its value in the MENU()
  // The solution was to reread the button inputs. This likely slows down the code by a little and is redundant. It
  // is a quick fix
  
  int UpStatus = digitalRead(2); // Up Button
  int DownStatus = digitalRead(4); //Down Button
  if(CURSORACTIVE == false){
    
  }
  if (MenuStatus == LOW && hold == 0 && CURSORACTIVE == false){  // Toggle between Current mode and changemode
    MODETOGGLE++;}
  if (MODETOGGLE >= 3){ //If mode toggle is 3 or greater, reset to 0
    MODETOGGLE = 0;}
    if (NEWMODE >= 3){ //If mode toggle is 3 or greater, reset to 0
    NEWMODE = 0;}
    if (NEWMODE < 0){
    NEWMODE = 3;}
    
  if (MODETOGGLE == 1 && CURSORACTIVE == false){ // MODE SELECTION SCREEN
    display.clearDisplay(); // Clear Display
    display.drawBitmap(0,0,logo_bmp,128,64,SSD1306_WHITE); //Draw Bitmap
    display.setTextColor(BLACK, WHITE); //Invert Color
    display.setCursor(40, 10); // Cursor for 
    display.println(MODES[NEWMODE]);

    if(UpStatus == 0 ){
      NEWMODE++;
    }
    if(DownStatus == 0){
      NEWMODE--;
    }
  }
      if (MODETOGGLE == 2 && CURSORACTIVE == false){
      FEEDERMODE = NEWMODE;
      MODETOGGLE++;}
  else{
    display.setTextColor(SSD1306_WHITE); // Select text color
    display.println(MODES[FEEDERMODE]);
  }}

// ------ SET TIME ------
void setTime(uint8_t new_hours, uint8_t new_minutes, uint8_t new_seconds){
  while(FEEDERMODE == 1){
      
      display.clearDisplay();
      displayTime(new_hours, new_minutes, new_seconds);
      MENU();
      display.display();  

      if(CURSORACTIVE == true){
        if(hours == 24 && UpStatus == 0 || hours >= 25){
          hours = 1;
        }else if(hours == 1 && DownStatus == 0){
          hours = 24;
        }
        if(minutes == 59 && UpStatus == 0){
          minutes = 0;
        }else if(minutes == 0 && DownStatus == 0){
          minutes = 59;
        }
        if(seconds == 59 && UpStatus == 0){
          seconds = 0;
        }else if(seconds == 0 && DownStatus == 0){
          seconds = 59;
        }
            int UpStatus = digitalRead(2); // Up Button
            int DownStatus = digitalRead(4); //Down Button 
            MenuStatus = ButtonControl(3); // Menu Button
            if (MenuStatus == LOW){ //Cursor Control
              clock_cursor= clock_cursor + 1;
            }
            // --CHOOSING HOUR
            if(clock_cursor == 0){
              Serial.print(new_hours);
              if(UpStatus == 0){ 
                new_hours++;
                }
              if(DownStatus == 0){
                new_hours--;}
            }
            // --CHOOSING MINUTE
            if(clock_cursor == 1){ 
              if(UpStatus == 0){
                new_minutes++;}
                if(DownStatus == 0){
                new_minutes--;}}
            // -- CHOOSING SECOND
            if(clock_cursor == 2){ 
              if(UpStatus == 0){
                new_seconds++;}
                if(DownStatus == 0){
                new_seconds--;}
          }
          // -- END OF CURSOR LOOP
          // Once reached, set the new time on the clock, return new time values, and escape while loop
          
          if(clock_cursor == 3){
            MENU();
            CURSORACTIVE = false; //Disable cursor
            clock_cursor = 0; // reset cursor position
            MODETOGGLE = 0; // Get out of toggle mode
            FEEDERMODE = 0; //Return to feeder mode
            rtc.adjust(DateTime(2021, 12, 29, new_hours, new_minutes, new_seconds));}
          }
  }
      }     

// ------ SET ALARM ------
// Set the alarm time. Saves time to memory so if power goes out for a few seconds, alarm time is retained.
void setAlarm(uint8_t alarm_hh, uint8_t alarm_mm, uint8_t alarm_ss){
  while(FEEDERMODE == 2){
      display.clearDisplay();
      displayTime(alarm_hh, alarm_mm, alarm_ss);
      MENU();
      display.display();  
      if(CURSORACTIVE == true){
        if(hours == 24 && UpStatus == 0){
          hours = 1;
        }else if(hours == 1 && DownStatus == 0){
          hours = 24;
        }
        if(minutes == 59 && UpStatus == 0){
          minutes = 0;
        }else if(minutes == 0 && DownStatus == 0){
          minutes = 59;
        }
        if(seconds == 59 && UpStatus == 0){
          seconds = 0;
        }else if(seconds == 0 && DownStatus == 0){
          seconds = 59;
        }
            int UpStatus = digitalRead(2); // Up Button
            int DownStatus = digitalRead(4); //Down Button 
            MenuStatus = ButtonControl(3); // Menu Button
            
            if (MenuStatus == LOW){ //Cursor Control
              clock_cursor= clock_cursor + 1;}
            
            // --CHOOSING HOUR
            if(clock_cursor == 0){
              if(UpStatus == 0){ 
                alarm_hh++;}
              if(DownStatus == 0){
                alarm_hh--;}}
                
            // --CHOOSING MINUTE
            if(clock_cursor == 1){ 
              if(UpStatus == 0){
                alarm_mm++;}
                if(DownStatus == 0){
                alarm_mm--;}}
            
            // -- CHOOSING SECOND
            if(clock_cursor == 2){ 
              if(UpStatus == 0){
                alarm_ss++;}
                if(DownStatus == 0){
                alarm_ss--;}}

          // Once reached, set the new time on the clock, return new time values, and escape while loop
          if(clock_cursor == 3){
            MENU();
            EEPROM.write(1, alarm_hh);
            EEPROM.write(2, alarm_mm);
            EEPROM.write(3, alarm_ss);
            CURSORACTIVE = false; //Disable cursor
            clock_cursor = 0; // reset cursor position
            MODETOGGLE = 0; // Get out of toggle mode
            FEEDERMODE = 0;} //Return to feeder mode
          }// -- END OF CURSOR LOOP
        }// -- END OF WHILE LOOP
      }// -- ENG OF FUNCTION
// ----------- Display Copyright ------------------
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



// seconds = (millis() / 1000) % 60; // convert to seconds, then modulo divide to 0-59 range
// minutes = (millis() /1000 / 60) % 60; // Gives int number of minutes since start - 0-59
// hours = (millis() /1000 / 3600) % 24; // Gives int number of hourse since start- 0-23
