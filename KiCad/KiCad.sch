EESchema Schematic File Version 4
EELAYER 26 0
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
L RF_Module:ESP-12E ESP8266_NodeMCU
U 1 1 5E9C82D2
P 3450 2350
F 0 "ESP8266_NodeMCU" H 3450 3328 50  0000 C CNN
F 1 "ESP-12E" H 3450 3237 50  0000 C CNN
F 2 "RF_Module:ESP-12E" H 3450 2350 50  0001 C CNN
F 3 "http://wiki.ai-thinker.com/_media/esp8266/esp8266_series_modules_user_manual_v1.1.pdf" H 3100 2450 50  0001 C CNN
	1    3450 2350
	1    0    0    -1  
$EndComp
$Comp
L Sensor:HC-SR501 PIR
U 1 1 5E9C8464
P 3500 2250
F 0 "PIR" H 5328 1601 50  0000 L CNN
F 1 "HC-SR501" H 5328 1510 50  0000 L CNN
F 2 "" H 5300 1850 50  0001 C CNN
F 3 "" H 5300 1850 50  0001 C CNN
	1    3500 2250
	1    0    0    -1  
$EndComp
Wire Wire Line
	3450 3050 3450 3100
Wire Wire Line
	3450 3100 4950 3100
Wire Wire Line
	3450 1550 4300 1550
Wire Wire Line
	4300 1550 4300 2800
Wire Wire Line
	4300 2800 4950 2800
Wire Wire Line
	4050 2450 4200 2450
Wire Wire Line
	4200 2450 4200 2950
Wire Wire Line
	4200 2950 4950 2950
$EndSCHEMATC