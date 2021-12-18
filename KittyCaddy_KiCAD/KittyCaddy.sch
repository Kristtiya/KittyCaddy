EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "Kitty Caddy"
Date "10/2/2021"
Rev "Rev 1.0"
Comp "Kristtiya Guerra & Co."
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L power:GND #PWR0101
U 1 1 6159CEBF
P 2400 5000
F 0 "#PWR0101" H 2400 4750 50  0001 C CNN
F 1 "GND" H 2405 4827 50  0000 C CNN
F 2 "" H 2400 5000 50  0001 C CNN
F 3 "" H 2400 5000 50  0001 C CNN
	1    2400 5000
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0102
U 1 1 615D9F0E
P 5400 4450
F 0 "#PWR0102" H 5400 4200 50  0001 C CNN
F 1 "GND" H 5405 4277 50  0000 C CNN
F 2 "" H 5400 4450 50  0001 C CNN
F 3 "" H 5400 4450 50  0001 C CNN
	1    5400 4450
	1    0    0    -1  
$EndComp
$Comp
L KittyCaddy:Buck_5V U1
U 1 1 615C7451
P 2850 2400
F 0 "U1" H 2850 2515 50  0000 C CNN
F 1 "D24V3F5" H 2850 2424 50  0000 C CNN
F 2 "KittyCaddy:D24V3F5" H 2850 2400 50  0001 C CNN
F 3 "" H 2850 2400 50  0001 C CNN
F 4 "Polulu: https://www.pololu.com/product/2098" H 2850 2400 50  0001 C CNN "Vendor"
	1    2850 2400
	1    0    0    -1  
$EndComp
$Comp
L KittyCaddy:DRV8825 U2
U 1 1 615930B4
P 1850 4100
F 0 "U2" H 1950 4165 50  0000 C CNN
F 1 "DRV8825" H 1950 4074 50  0000 C CNN
F 2 "Module:Pololu_Breakout-16_15.2x20.3mm" H 1950 4050 50  0001 C CNN
F 3 "" H 1950 4050 50  0001 C CNN
F 4 "https://www.pololu.com/product/2133" H 1850 4100 50  0001 C CNN "Vendor"
	1    1850 4100
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0104
U 1 1 6159B9EE
P 2200 2950
F 0 "#PWR0104" H 2200 2700 50  0001 C CNN
F 1 "GND" H 2205 2777 50  0000 C CNN
F 2 "" H 2200 2950 50  0001 C CNN
F 3 "" H 2200 2950 50  0001 C CNN
	1    2200 2950
	1    0    0    -1  
$EndComp
Text GLabel 5900 3450 2    50   Input ~ 0
Emit
$Comp
L Switch:SW_Push SW1
U 1 1 61633F35
P 5250 5050
F 0 "SW1" H 5350 5150 50  0000 C CNN
F 1 "SW_Push" H 5250 5244 50  0001 C CNN
F 2 "KittyCaddy:DigikeyEG1833-ND" H 5250 5250 50  0001 C CNN
F 3 "~" H 5250 5250 50  0001 C CNN
	1    5250 5050
	1    0    0    -1  
$EndComp
Text GLabel 5450 5250 2    50   Input ~ 0
Mid
Text GLabel 5450 5050 2    50   Input ~ 0
Up
Text GLabel 5450 5450 2    50   Input ~ 0
Down
$Comp
L Connector:Barrel_Jack_Switch J1
U 1 1 615B0B5B
P 1500 2800
F 0 "J1" H 1557 3117 50  0000 C CNN
F 1 "12 V Power" H 1557 3026 50  0000 C CNN
F 2 "Connector_BarrelJack:BarrelJack_Horizontal" H 1550 2760 50  0001 C CNN
F 3 "~" H 1550 2760 50  0001 C CNN
F 4 "https://www.pololu.com/product/1139" H 1500 2800 50  0001 C CNN "Vendor"
	1    1500 2800
	1    0    0    -1  
$EndComp
$Comp
L power:+12V #PWR02
U 1 1 615B1426
P 2350 2300
F 0 "#PWR02" H 2350 2150 50  0001 C CNN
F 1 "+12V" H 2365 2473 50  0000 C CNN
F 2 "" H 2350 2300 50  0001 C CNN
F 3 "" H 2350 2300 50  0001 C CNN
	1    2350 2300
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR04
U 1 1 615B1C02
P 3250 2700
F 0 "#PWR04" H 3250 2550 50  0001 C CNN
F 1 "+5V" H 3265 2873 50  0000 C CNN
F 2 "" H 3250 2700 50  0001 C CNN
F 3 "" H 3250 2700 50  0001 C CNN
	1    3250 2700
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x04 J2
U 1 1 615B252F
P 2600 4600
F 0 "J2" H 2680 4592 50  0000 L CNN
F 1 "digikey:17HS13-1204S" H 2680 4501 50  0000 L CNN
F 2 "Connector_Molex:Molex_KK-254_AE-6410-04A_1x04_P2.54mm_Vertical" H 2600 4600 50  0001 C CNN
F 3 "~" H 2600 4600 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/molex/0022232041/26671" H 2600 4600 50  0001 C CNN "Vendor"
	1    2600 4600
	1    0    0    -1  
$EndComp
Wire Wire Line
	1800 2900 1800 2800
Connection ~ 1800 2800
Wire Wire Line
	2200 2950 2200 2800
Wire Wire Line
	2200 2800 2450 2800
$Comp
L power:GND #PWR05
U 1 1 615FDD8F
P 5050 5450
F 0 "#PWR05" H 5050 5200 50  0001 C CNN
F 1 "GND" H 5055 5277 50  0000 C CNN
F 2 "" H 5050 5450 50  0001 C CNN
F 3 "" H 5050 5450 50  0001 C CNN
	1    5050 5450
	1    0    0    -1  
$EndComp
Text Notes 1050 2000 0    50   ~ 10
Power
$Comp
L power:+5V #PWR06
U 1 1 615FECBE
P 5600 2450
F 0 "#PWR06" H 5600 2300 50  0001 C CNN
F 1 "+5V" H 5615 2623 50  0000 C CNN
F 2 "" H 5600 2450 50  0001 C CNN
F 3 "" H 5600 2450 50  0001 C CNN
	1    5600 2450
	1    0    0    -1  
$EndComp
Text GLabel 5900 3850 2    50   Input ~ 0
SDA
Text GLabel 5900 3950 2    50   Input ~ 0
SCL
Text Notes 4300 2000 0    50   ~ 10
Microcontroller\n
Wire Notes Line
	1050 2000 3500 2000
Wire Notes Line
	3500 2000 3500 3350
Wire Notes Line
	3500 3350 1050 3350
Wire Notes Line
	1050 3350 1050 2000
Wire Notes Line
	7050 6050 7050 4350
Wire Notes Line
	10950 6050 7050 6050
Wire Notes Line
	10950 4350 10950 6050
Wire Notes Line
	7050 4350 10950 4350
$Comp
L power:+BATT #PWR010
U 1 1 6163BDA3
P 8700 5400
F 0 "#PWR010" H 8700 5250 50  0001 C CNN
F 1 "+BATT" H 8715 5573 50  0000 C CNN
F 2 "" H 8700 5400 50  0001 C CNN
F 3 "" H 8700 5400 50  0001 C CNN
	1    8700 5400
	1    0    0    -1  
$EndComp
$Comp
L KittyCaddy:DS3231_Precision_RTC U5
U 1 1 615F9CC9
P 9450 4900
F 0 "U5" H 9750 4850 50  0000 C CNN
F 1 "DS3231" H 9500 4850 50  0000 C CNN
F 2 "KittyCaddy:DS3231" H 9450 4900 50  0001 C CNN
F 3 "" H 9450 4900 50  0001 C CNN
F 4 "https://www.adafruit.com/product/3013" H 9450 4900 50  0001 C CNN "Vendor"
	1    9450 4900
	1    0    0    -1  
$EndComp
Text GLabel 9050 5300 0    50   Input ~ 0
SCL
Text GLabel 9050 5200 0    50   Input ~ 0
SDA
Text GLabel 7450 5200 0    50   Input ~ 0
SCL
Text GLabel 7450 5100 0    50   Input ~ 0
SDA
$Comp
L power:+5V #PWR011
U 1 1 616318D5
P 9050 4800
F 0 "#PWR011" H 9050 4650 50  0001 C CNN
F 1 "+5V" H 9065 4973 50  0000 C CNN
F 2 "" H 9050 4800 50  0001 C CNN
F 3 "" H 9050 4800 50  0001 C CNN
	1    9050 4800
	1    0    0    -1  
$EndComp
Wire Wire Line
	7150 5300 7450 5300
$Comp
L power:+5V #PWR07
U 1 1 61630BFA
P 7150 5300
F 0 "#PWR07" H 7150 5150 50  0001 C CNN
F 1 "+5V" H 7165 5473 50  0000 C CNN
F 2 "" H 7150 5300 50  0001 C CNN
F 3 "" H 7150 5300 50  0001 C CNN
	1    7150 5300
	1    0    0    -1  
$EndComp
Text Notes 7050 4350 0    50   ~ 10
SDA/SCL Bus\n
Text Notes 7050 2000 0    50   ~ 10
Homing Sensor
Wire Notes Line
	10050 2000 7050 2000
Wire Notes Line
	10050 3750 10050 2000
Wire Notes Line
	7050 3750 10050 3750
Wire Notes Line
	7050 2000 7050 3750
Wire Wire Line
	7850 3100 8050 3100
Connection ~ 7850 3100
Wire Wire Line
	7850 3400 7850 3100
Wire Wire Line
	7800 3100 7850 3100
Wire Wire Line
	8000 2800 8050 2800
Wire Wire Line
	7800 2700 8050 2700
$Comp
L power:GND #PWR0107
U 1 1 61604C15
P 8000 2800
F 0 "#PWR0107" H 8000 2550 50  0001 C CNN
F 1 "GND" H 7850 2750 50  0000 C CNN
F 2 "" H 8000 2800 50  0001 C CNN
F 3 "" H 8000 2800 50  0001 C CNN
	1    8000 2800
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x05 J3
U 1 1 61600DB3
P 8250 2900
F 0 "J3" H 8200 3200 50  0000 L CNN
F 1 "digikey:OPB740WZ" H 7950 3300 50  0000 L CNN
F 2 "Connector_Molex:Molex_KK-254_AE-6410-05A_1x05_P2.54mm_Vertical" H 8250 2900 50  0001 C CNN
F 3 "" H 8250 2900 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/molex/0022232051/26673" H 8250 2900 50  0001 C CNN "Vendor"
	1    8250 2900
	1    0    0    -1  
$EndComp
$Comp
L Device:R_US R2
U 1 1 615FFB3F
P 7800 2550
F 0 "R2" H 7868 2596 50  0000 L CNN
F 1 "100" H 7868 2505 50  0000 L CNN
F 2 "KittyCaddy:CFR-25JT-52-100R" V 7840 2540 50  0001 C CNN
F 3 "~" H 7800 2550 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/yageo/CFR-25JT-52-100R/13921496" H 7800 2550 50  0001 C CNN "Vendor"
	1    7800 2550
	-1   0    0    1   
$EndComp
$Comp
L power:+5V #PWR09
U 1 1 615FF469
P 7800 2400
F 0 "#PWR09" H 7800 2250 50  0001 C CNN
F 1 "+5V" H 7815 2573 50  0000 C CNN
F 2 "" H 7800 2400 50  0001 C CNN
F 3 "" H 7800 2400 50  0001 C CNN
	1    7800 2400
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0105
U 1 1 615FD4C9
P 9500 5700
F 0 "#PWR0105" H 9500 5450 50  0001 C CNN
F 1 "GND" H 9505 5527 50  0000 C CNN
F 2 "" H 9500 5700 50  0001 C CNN
F 3 "" H 9500 5700 50  0001 C CNN
	1    9500 5700
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0106
U 1 1 616043AC
P 8050 3000
F 0 "#PWR0106" H 8050 2750 50  0001 C CNN
F 1 "GND" H 8055 2827 50  0000 C CNN
F 2 "" H 8050 3000 50  0001 C CNN
F 3 "" H 8050 3000 50  0001 C CNN
	1    8050 3000
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR0103
U 1 1 6159D43A
P 7450 5400
F 0 "#PWR0103" H 7450 5150 50  0001 C CNN
F 1 "GND" H 7455 5227 50  0000 C CNN
F 2 "" H 7450 5400 50  0001 C CNN
F 3 "" H 7450 5400 50  0001 C CNN
	1    7450 5400
	1    0    0    -1  
$EndComp
$Comp
L KittyCaddy:SSD1306_IIC_OLED_Display U4
U 1 1 61595AE6
P 7700 4950
F 0 "U4" H 7750 5050 50  0000 L CNN
F 1 "SSD1306_IIC_OLED_Display" H 7350 4950 50  0000 L CNN
F 2 "KittyCaddy:IIC_Display" H 7800 4950 50  0001 C CNN
F 3 "" H 7800 4950 50  0001 C CNN
F 4 "https://www.amazon.com/dp/B08VNRH5HR" H 7700 4950 50  0001 C CNN "Vendor"
	1    7700 4950
	1    0    0    -1  
$EndComp
Wire Notes Line
	1050 3700 1050 5500
Wire Notes Line
	1050 5500 3500 5500
Wire Notes Line
	3500 5500 3500 3700
Wire Notes Line
	3500 3700 1050 3700
Text Notes 1050 3700 0    50   ~ 10
Motor\n
Wire Wire Line
	2400 4400 2650 4400
Wire Wire Line
	2400 4300 2500 4300
Wire Wire Line
	2500 4300 2500 4100
$Comp
L power:+12V #PWR03
U 1 1 6164C52E
P 2900 4100
F 0 "#PWR03" H 2900 3950 50  0001 C CNN
F 1 "+12V" H 2915 4273 50  0000 C CNN
F 2 "" H 2900 4100 50  0001 C CNN
F 3 "" H 2900 4100 50  0001 C CNN
	1    2900 4100
	1    0    0    -1  
$EndComp
Text GLabel 1500 5000 0    50   Input ~ 0
DIR
Text GLabel 1500 4900 0    50   Input ~ 0
STEP
Text GLabel 1500 4400 0    50   Input ~ 0
M0
Text GLabel 1500 4500 0    50   Input ~ 0
M1
Text GLabel 1500 4600 0    50   Input ~ 0
M2
Wire Notes Line
	4250 2000 6450 2000
Wire Notes Line
	6450 2000 6450 5850
Wire Notes Line
	6450 5850 4250 5850
Wire Notes Line
	4250 5850 4250 2000
NoConn ~ 8050 2900
Wire Wire Line
	8700 5400 9050 5400
Wire Wire Line
	9050 4800 9050 5100
$Comp
L Device:CP1 C1
U 1 1 61653AD0
P 2050 2450
F 0 "C1" V 1798 2450 50  0000 C CNN
F 1 "100uF" V 1889 2450 50  0000 C CNN
F 2 "Capacitor_THT:CP_Radial_D8.0mm_P3.50mm" H 2050 2450 50  0001 C CNN
F 3 "~" H 2050 2450 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/illinois-capacitor/107CKH063M/5343973" V 2050 2450 50  0001 C CNN "Vendor"
	1    2050 2450
	0    1    1    0   
$EndComp
Wire Wire Line
	1800 2800 2200 2800
Connection ~ 2200 2800
$Comp
L power:GND #PWR01
U 1 1 6165A454
P 1900 2450
F 0 "#PWR01" H 1900 2200 50  0001 C CNN
F 1 "GND" H 1905 2277 50  0000 C CNN
F 2 "" H 1900 2450 50  0001 C CNN
F 3 "" H 1900 2450 50  0001 C CNN
	1    1900 2450
	1    0    0    -1  
$EndComp
Wire Wire Line
	2350 2300 2350 2700
Connection ~ 2350 2700
Wire Wire Line
	2350 2700 2450 2700
Wire Wire Line
	1800 2700 2200 2700
Connection ~ 2200 2700
Wire Wire Line
	2200 2700 2350 2700
Wire Wire Line
	2200 2450 2200 2700
$Comp
L Device:CP1 C2
U 1 1 61660820
P 2650 4250
F 0 "C2" H 2765 4296 50  0000 L CNN
F 1 "100uF" H 2765 4205 50  0000 L CNN
F 2 "Capacitor_THT:CP_Radial_D8.0mm_P3.50mm" H 2650 4250 50  0001 C CNN
F 3 "~" H 2650 4250 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/illinois-capacitor/107CKH063M/5343973" H 2650 4250 50  0001 C CNN "Vendor"
	1    2650 4250
	1    0    0    -1  
$EndComp
Wire Wire Line
	2500 4100 2650 4100
Connection ~ 2650 4100
Wire Wire Line
	2650 4100 2900 4100
$Comp
L MCU_Module:Arduino_Nano_v2.x U3
U 1 1 61690B4B
P 5400 3450
F 0 "U3" H 5750 4400 50  0000 C CNN
F 1 "Arduino_Nano_v2.x" H 5400 2200 50  0000 C CNN
F 2 "Module:Arduino_Nano" H 5400 3450 50  0001 C CIN
F 3 "https://www.arduino.cc/en/uploads/Main/ArduinoNanoManual23.pdf" H 5400 3450 50  0001 C CNN
F 4 "https://www.amazon.com/gp/product/B0713XK923/ref=ppx_yo_dt_b_asin_title_o00_s00?ie=UTF8&psc=1" H 5400 3450 50  0001 C CNN "Vendor"
	1    5400 3450
	1    0    0    -1  
$EndComp
Text GLabel 4900 3550 0    50   Input ~ 0
M2
Text GLabel 4900 3650 0    50   Input ~ 0
M1
Text GLabel 4900 3750 0    50   Input ~ 0
M0
Text GLabel 4900 3450 0    50   Input ~ 0
STEP
Text GLabel 4900 3350 0    50   Input ~ 0
DIR
Text GLabel 4900 3250 0    50   Input ~ 0
Down
Text GLabel 4900 3150 0    50   Input ~ 0
Mid
Text GLabel 4900 3050 0    50   Input ~ 0
Up
$Comp
L Device:C C3
U 1 1 616AF0F2
P 3250 2850
F 0 "C3" H 3365 2896 50  0000 L CNN
F 1 ".1uF" H 3365 2805 50  0000 L CNN
F 2 "KittyCaddy:1C10Z5U104M050B" H 3288 2700 50  0001 C CNN
F 3 "~" H 3250 2850 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/vishay-beyschlag-draloric-bc-components/1C10Z5U104M050B/7056991" H 3250 2850 50  0001 C CNN "Vendor"
	1    3250 2850
	1    0    0    -1  
$EndComp
Connection ~ 3250 2700
$Comp
L power:GND #PWR012
U 1 1 616AF7D7
P 3250 3000
F 0 "#PWR012" H 3250 2750 50  0001 C CNN
F 1 "GND" H 3255 2827 50  0000 C CNN
F 2 "" H 3250 3000 50  0001 C CNN
F 3 "" H 3250 3000 50  0001 C CNN
	1    3250 3000
	1    0    0    -1  
$EndComp
Text GLabel 4900 4050 0    50   Input ~ 0
RESET
Text GLabel 4900 4150 0    50   Input ~ 0
SLEEP
Text GLabel 1500 4300 0    50   Input ~ 0
ENABLE
Text GLabel 4900 3950 0    50   Input ~ 0
ENABLE
Wire Wire Line
	5050 5050 5050 5250
$Comp
L Switch:SW_Push SW2
U 1 1 616B840D
P 5250 5250
F 0 "SW2" H 5350 5350 50  0000 C CNN
F 1 "SW_Push" H 5250 5444 50  0001 C CNN
F 2 "KittyCaddy:DigikeyEG1833-ND" H 5250 5450 50  0001 C CNN
F 3 "~" H 5250 5450 50  0001 C CNN
	1    5250 5250
	1    0    0    -1  
$EndComp
Connection ~ 5050 5250
Wire Wire Line
	5050 5250 5050 5450
$Comp
L Switch:SW_Push SW3
U 1 1 616B869B
P 5250 5450
F 0 "SW3" H 5350 5550 50  0000 C CNN
F 1 "SW_Push" H 5250 5644 50  0001 C CNN
F 2 "KittyCaddy:DigikeyEG1833-ND" H 5250 5650 50  0001 C CNN
F 3 "~" H 5250 5650 50  0001 C CNN
	1    5250 5450
	1    0    0    -1  
$EndComp
Connection ~ 5050 5450
$Comp
L power:+5V #PWR08
U 1 1 61609966
P 7500 3100
F 0 "#PWR08" H 7500 2950 50  0001 C CNN
F 1 "+5V" H 7515 3273 50  0000 C CNN
F 2 "" H 7500 3100 50  0001 C CNN
F 3 "" H 7500 3100 50  0001 C CNN
	1    7500 3100
	1    0    0    -1  
$EndComp
Text GLabel 7700 3400 0    50   Input ~ 0
Emit
Wire Wire Line
	7700 3400 7850 3400
$Comp
L Device:R_US R1
U 1 1 6160DC38
P 7650 3100
F 0 "R1" V 7445 3100 50  0000 C CNN
F 1 "10k" V 7536 3100 50  0000 C CNN
F 2 "KittyCaddy:CF14JT10K0" V 7690 3090 50  0001 C CNN
F 3 "~" H 7650 3100 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/stackpole-electronics-inc/CF14JT10K0/1741265" V 7650 3100 50  0001 C CNN "Vendor"
	1    7650 3100
	0    -1   -1   0   
$EndComp
Wire Wire Line
	1500 4800 1500 4700
Wire Wire Line
	1500 4700 1250 4700
Connection ~ 1500 4700
$Comp
L power:+5V #PWR013
U 1 1 616C95E0
P 1250 4700
F 0 "#PWR013" H 1250 4550 50  0001 C CNN
F 1 "+5V" H 1265 4873 50  0000 C CNN
F 2 "" H 1250 4700 50  0001 C CNN
F 3 "" H 1250 4700 50  0001 C CNN
	1    1250 4700
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x01 J4
U 1 1 61724687
P 1370 5710
F 0 "J4" H 1450 5752 50  0000 L CNN
F 1 "Ground Pin" H 1450 5661 50  0000 L CNN
F 2 "Connector_Pin:Pin_D1.0mm_L10.0mm_LooseFit" H 1370 5710 50  0001 C CNN
F 3 "~" H 1370 5710 50  0001 C CNN
	1    1370 5710
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR014
U 1 1 61725BC9
P 1170 5710
F 0 "#PWR014" H 1170 5460 50  0001 C CNN
F 1 "GND" H 1175 5537 50  0000 C CNN
F 2 "" H 1170 5710 50  0001 C CNN
F 3 "" H 1170 5710 50  0001 C CNN
	1    1170 5710
	1    0    0    -1  
$EndComp
$EndSCHEMATC
