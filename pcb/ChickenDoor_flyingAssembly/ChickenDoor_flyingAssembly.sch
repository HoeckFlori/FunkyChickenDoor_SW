EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L arduino:Arduino_Mega2560_Shield XA?
U 1 1 5EDD6316
P 3700 3750
F 0 "XA?" H 3700 1369 60  0000 C CNN
F 1 "Arduino_Mega2560_Shield" H 3700 1263 60  0000 C CNN
F 2 "" H 4400 6500 60  0001 C CNN
F 3 "https://store.arduino.cc/arduino-mega-2560-rev3" H 4400 6500 60  0001 C CNN
	1    3700 3750
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x16_Female J?
U 1 1 5EDD9B3A
P 9400 2300
F 0 "J?" H 9150 1250 50  0000 C CNN
F 1 "Conn_01x16_Female" H 9500 1350 50  0000 C CNN
F 2 "" H 9400 2300 50  0001 C CNN
F 3 "~" H 9400 2300 50  0001 C CNN
	1    9400 2300
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5EDDB4FB
P 1300 5200
F 0 "#PWR?" H 1300 4950 50  0001 C CNN
F 1 "GND" H 1305 5027 50  0000 C CNN
F 2 "" H 1300 5200 50  0001 C CNN
F 3 "" H 1300 5200 50  0001 C CNN
	1    1300 5200
	1    0    0    -1  
$EndComp
Wire Wire Line
	2400 5000 1300 5000
Wire Wire Line
	1300 5000 1300 5200
$Comp
L power:GND #PWR?
U 1 1 5EDDCCDC
P 7700 3600
F 0 "#PWR?" H 7700 3350 50  0001 C CNN
F 1 "GND" H 7705 3427 50  0000 C CNN
F 2 "" H 7700 3600 50  0001 C CNN
F 3 "" H 7700 3600 50  0001 C CNN
	1    7700 3600
	1    0    0    -1  
$EndComp
Wire Wire Line
	7700 3600 7700 3500
Wire Wire Line
	7700 3500 8300 3500
Wire Wire Line
	7700 3500 7700 1600
Wire Wire Line
	7700 1600 9200 1600
$Comp
L power:+3V3 #PWR?
U 1 1 5EDDDAF5
P 2050 5450
F 0 "#PWR?" H 2050 5300 50  0001 C CNN
F 1 "+3V3" H 2065 5623 50  0000 C CNN
F 2 "" H 2050 5450 50  0001 C CNN
F 3 "" H 2050 5450 50  0001 C CNN
	1    2050 5450
	1    0    0    -1  
$EndComp
Wire Wire Line
	2400 5500 2050 5500
Wire Wire Line
	2050 5500 2050 5450
Connection ~ 7700 3500
Text Notes 9450 3150 0    63   ~ 0
01  GND\n02  VSS\n03  NC\n04  NC\n05  NC\n06  RESET\n07  A0\n08  SDA\n09  SCK\n10  CS\n11  SD - SCK\n12  SD - MISO\n13  SD - MOSI\n14  SD - CS\n15  LED +\n16  LED -
Wire Wire Line
	9200 3000 9000 3000
Wire Wire Line
	9200 2100 7400 2100
Wire Wire Line
	9200 2200 6600 2200
Wire Wire Line
	9200 2300 6600 2300
Wire Wire Line
	9200 2400 6600 2400
Wire Wire Line
	9200 2500 6600 2500
Text Label 6600 2100 0    50   ~ 0
TFT_reset
Text Label 6600 2200 0    50   ~ 0
TFT_DataOrCommand
Text Label 6600 2300 0    50   ~ 0
TFT_SPI_MOSI
Text Label 6600 2400 0    50   ~ 0
TFT_SPI_Clock
Text Label 6600 2500 0    50   ~ 0
TFT_CS
Wire Wire Line
	5000 2200 5900 2200
Wire Wire Line
	5000 2300 5900 2300
Wire Wire Line
	5000 2400 5900 2400
Wire Wire Line
	5000 5700 5900 5700
Wire Wire Line
	5000 5800 5900 5800
Text Label 5900 2200 2    50   ~ 0
TFT_DataOrCommand
Text Label 5900 2300 2    50   ~ 0
TFT_reset
Text Label 5900 2400 2    50   ~ 0
TFT_CS
Text Label 5900 5700 2    50   ~ 0
TFT_SPI_MOSI
Text Label 5900 5800 2    50   ~ 0
TFT_SPI_Clock
Text Notes 7950 1250 0    50   ~ 10
1,8 inch 128x160 SPI Serial TFT LCD Display Modul + SD Card Slot\n(1,8TFT V1.0 !!!)
$Comp
L Connector:Conn_01x04_Female J?
U 1 1 5EE14116
P 9400 4700
F 0 "J?" H 9100 4250 50  0000 L CNN
F 1 "Conn_01x04_Female" H 9100 4350 50  0000 L CNN
F 2 "" H 9400 4700 50  0001 C CNN
F 3 "~" H 9400 4700 50  0001 C CNN
	1    9400 4700
	1    0    0    -1  
$EndComp
Text Notes 9450 4950 0    63   ~ 0
01 SCL\n02 SDA\n03 VCC\n04 GND
Text Notes 7950 4300 0    50   ~ 10
RTC DS3231 I²C AT24C32 RealTimeClock
$Comp
L power:GND #PWR?
U 1 1 5EE1931E
P 9000 5150
F 0 "#PWR?" H 9000 4900 50  0001 C CNN
F 1 "GND" H 9005 4977 50  0000 C CNN
F 2 "" H 9000 5150 50  0001 C CNN
F 3 "" H 9000 5150 50  0001 C CNN
	1    9000 5150
	1    0    0    -1  
$EndComp
Wire Wire Line
	9200 4900 9000 4900
Wire Wire Line
	9000 4900 9000 5150
Wire Wire Line
	9200 4800 9000 4800
Wire Wire Line
	9000 4800 9000 4550
Wire Wire Line
	9200 4600 7950 4600
Wire Wire Line
	9200 4700 7950 4700
Text Label 7950 4600 0    50   ~ 0
RTC_SCL
Text Label 7950 4700 0    50   ~ 0
RTC_SDA
Wire Wire Line
	1500 2500 2400 2500
Text Label 1500 2500 0    50   ~ 0
RTC_SCL
Text Label 1500 2400 0    50   ~ 0
RTC_SDA
Wire Wire Line
	2400 2400 1500 2400
$Comp
L Device:R R?
U 1 1 5EE28B8A
P 8700 3100
F 0 "R?" V 8493 3100 50  0000 C CNN
F 1 "18R" V 8584 3100 50  0000 C CNN
F 2 "" V 8630 3100 50  0001 C CNN
F 3 "~" H 8700 3100 50  0001 C CNN
	1    8700 3100
	0    1    1    0   
$EndComp
Wire Wire Line
	8850 3100 9200 3100
$Comp
L power:+5V #PWR?
U 1 1 5EE38FDB
P 1750 5500
F 0 "#PWR?" H 1750 5350 50  0001 C CNN
F 1 "+5V" H 1765 5673 50  0000 C CNN
F 2 "" H 1750 5500 50  0001 C CNN
F 3 "" H 1750 5500 50  0001 C CNN
	1    1750 5500
	1    0    0    -1  
$EndComp
Wire Wire Line
	2400 5600 1750 5600
Wire Wire Line
	1750 5600 1750 5500
$Comp
L power:+5V #PWR?
U 1 1 5EE3C499
P 9000 1450
F 0 "#PWR?" H 9000 1300 50  0001 C CNN
F 1 "+5V" H 9015 1623 50  0000 C CNN
F 2 "" H 9000 1450 50  0001 C CNN
F 3 "" H 9000 1450 50  0001 C CNN
	1    9000 1450
	1    0    0    -1  
$EndComp
Wire Wire Line
	9200 1700 9000 1700
Connection ~ 9000 1700
Wire Wire Line
	9000 1700 9000 3000
$Comp
L power:+5V #PWR?
U 1 1 5EE41E7D
P 9000 4550
F 0 "#PWR?" H 9000 4400 50  0001 C CNN
F 1 "+5V" H 9015 4723 50  0000 C CNN
F 2 "" H 9000 4550 50  0001 C CNN
F 3 "" H 9000 4550 50  0001 C CNN
	1    9000 4550
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 5EE6340C
P 7400 1750
F 0 "R?" H 7470 1796 50  0000 L CNN
F 1 "10k" H 7470 1705 50  0000 L CNN
F 2 "" V 7330 1750 50  0001 C CNN
F 3 "~" H 7400 1750 50  0001 C CNN
	1    7400 1750
	1    0    0    -1  
$EndComp
Wire Wire Line
	9000 1500 7400 1500
Wire Wire Line
	7400 1500 7400 1600
Wire Wire Line
	7400 1900 7400 2100
Connection ~ 7400 2100
Wire Wire Line
	7400 2100 6600 2100
Text Notes 5300 3000 0    50   ~ 0
D22 - back \nD24 - enter\nD26 - up\nD28 - down
$Comp
L Transistor_BJT:BC547 Q?
U 1 1 5F443A1A
P 8200 3300
F 0 "Q?" H 8391 3346 50  0000 L CNN
F 1 "BC547" H 8391 3255 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-92_Inline" H 8400 3225 50  0001 L CIN
F 3 "http://www.fairchildsemi.com/ds/BC/BC547.pdf" H 8200 3300 50  0001 L CNN
	1    8200 3300
	1    0    0    -1  
$EndComp
Wire Wire Line
	9000 1450 9000 1500
Connection ~ 9000 1500
Wire Wire Line
	9000 1500 9000 1700
Wire Wire Line
	8300 3100 8550 3100
Wire Wire Line
	8000 3300 6600 3300
Text Label 6600 3300 0    50   ~ 0
Dimming
$EndSCHEMATC
