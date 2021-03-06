EESchema Schematic File Version 4
LIBS:BruCON_0x0a-cache
EELAYER 29 0
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
L power:+5V #PWR02
U 1 1 5B1A4408
P 6100 6100
F 0 "#PWR02" H 6100 5950 50  0001 C CNN
F 1 "+5V" H 6115 6273 50  0000 C CNN
F 2 "" H 6100 6100 50  0001 C CNN
F 3 "" H 6100 6100 50  0001 C CNN
	1    6100 6100
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR01
U 1 1 5B1A4431
P 5850 6100
F 0 "#PWR01" H 5850 5950 50  0001 C CNN
F 1 "+3.3V" H 5865 6273 50  0000 C CNN
F 2 "" H 5850 6100 50  0001 C CNN
F 3 "" H 5850 6100 50  0001 C CNN
	1    5850 6100
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR03
U 1 1 5B1A476E
P 6350 6100
F 0 "#PWR03" H 6350 5850 50  0001 C CNN
F 1 "GND" H 6355 5927 50  0000 C CNN
F 2 "" H 6350 6100 50  0001 C CNN
F 3 "" H 6350 6100 50  0001 C CNN
	1    6350 6100
	-1   0    0    1   
$EndComp
$Comp
L Connector:USB_B_Micro J4
U 1 1 5B1A49C6
P 8500 3700
F 0 "J4" H 8555 4167 50  0000 C CNN
F 1 "USB_B_Micro" H 8555 4076 50  0000 C CNN
F 2 "Connector_USB:USB_Micro-B_Molex_47346-0001" H 8650 3650 50  0001 C CNN
F 3 "~" H 8650 3650 50  0001 C CNN
	1    8500 3700
	1    0    0    -1  
$EndComp
Text GLabel 6350 6100 3    50   Input ~ 0
GND
Text GLabel 6100 6100 3    50   Input ~ 0
+5V
Text GLabel 5850 6100 3    50   Input ~ 0
+3.3V
Text GLabel 8500 4100 3    50   Input ~ 0
GND
Wire Wire Line
	8400 4100 8500 4100
$Comp
L Connector_Generic:Conn_01x02 J3
U 1 1 5B1A4DDC
P 8450 4700
F 0 "J3" H 8370 4375 50  0000 C CNN
F 1 "Conn_01x02" H 8370 4466 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 8450 4700 50  0001 C CNN
F 3 "~" H 8450 4700 50  0001 C CNN
	1    8450 4700
	-1   0    0    1   
$EndComp
Text GLabel 8650 4700 3    50   Input ~ 0
GND
Wire Wire Line
	8800 3500 8950 3500
$Comp
L Connector_Generic:Conn_01x02 CONN_BATT1
U 1 1 5B1A5607
P 9150 5300
F 0 "CONN_BATT1" H 9070 4975 50  0000 C CNN
F 1 "Conn_01x02" H 9070 5066 50  0000 C CNN
F 2 "brucon_0xb:JST-PH-SM4-TB-2" H 9150 5300 50  0001 C CNN
F 3 "~" H 9150 5300 50  0001 C CNN
	1    9150 5300
	-1   0    0    1   
$EndComp
$Comp
L Device:C C10
U 1 1 5B1A57B6
P 8950 4100
F 0 "C10" H 9065 4146 50  0000 L CNN
F 1 "4.7uF" H 9065 4055 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 8988 3950 50  0001 C CNN
F 3 "~" H 8950 4100 50  0001 C CNN
	1    8950 4100
	1    0    0    -1  
$EndComp
Wire Wire Line
	8950 3950 8950 3500
Text GLabel 8950 4250 0    50   Input ~ 0
GND
$Comp
L BruCON_0x0a-rescue:MCP112-315-Brucon U8
U 1 1 5B1B259E
P 10500 6250
F 0 "U8" H 10800 6350 50  0000 C CNN
F 1 "MCP112-315" H 10250 6050 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 10500 6250 50  0001 C CNN
F 3 "" H 10500 6250 50  0001 C CNN
	1    10500 6250
	1    0    0    -1  
$EndComp
Text GLabel 10900 6250 2    50   Input ~ 0
VBAT
Text GLabel 10250 6350 0    50   Input ~ 0
GND
Wire Wire Line
	10000 6150 10250 6150
$Comp
L Connector_Generic:Conn_02x05_Counter_Clockwise J1
U 1 1 5B1C459A
P 1150 7200
F 0 "J1" H 1200 7617 50  0000 C CNN
F 1 "Hirose DF23C-10DS-0.5" H 1200 7526 50  0000 C CNN
F 2 "DF23C-10DS-0.5V(51):DF23C-10DS-0.5V(51)" H 1150 7200 50  0001 C CNN
F 3 "~" H 1150 7200 50  0001 C CNN
	1    1150 7200
	1    0    0    -1  
$EndComp
Text Notes 10550 6500 0    50   ~ 0
cutout 3v vbat
Text GLabel 9150 6300 3    50   Input ~ 0
CUT3VVBAT
Text Notes 9000 5700 0    50   ~ 0
LiPO Charging + Power Connections
$Comp
L Interface_USB:CP2102N-A01-GQFN24 U2
U 1 1 5B1AA594
P 6300 1950
F 0 "U2" H 6300 3028 50  0000 C CNN
F 1 "CP2102N-A01-GQFN24" H 6800 2750 50  0000 C CNN
F 2 "Package_DFN_QFN:QFN-24-1EP_4x4mm_P0.5mm_EP2.6x2.6mm" H 6750 1150 50  0001 L CNN
F 3 "http://www.silabs.com/support%20documents/technicaldocs/cp2102n-datasheet.pdf" H 6350 900 50  0001 C CNN
	1    6300 1950
	1    0    0    -1  
$EndComp
Text GLabel 8800 3700 2    50   Input ~ 0
D+
Text GLabel 8800 3800 2    50   Input ~ 0
D-
Text GLabel 5700 2350 0    50   Input ~ 0
D+
Text GLabel 5700 2450 0    50   Input ~ 0
D-
$Comp
L BruCON_0x0a-rescue:MIC2288YD5-Brucon U5
U 1 1 5B1B30C5
P 9850 2550
F 0 "U5" H 9850 2975 50  0000 C CNN
F 1 "MIC2288YD5" H 9850 2884 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-23-5" H 9850 2550 50  0001 C CNN
F 3 "" H 9850 2550 50  0001 C CNN
	1    9850 2550
	1    0    0    -1  
$EndComp
$Comp
L BruCON_0x0a-rescue:L-adafruit M2
U 1 1 5B1B31BF
P 9650 2000
F 0 "M2" V 9865 2000 50  0000 C CNN
F 1 "10uH" V 9774 2000 50  0000 C CNN
F 2 "Inductor_SMD:L_0805_2012Metric" H 9680 2150 20  0001 C CNN
F 3 "" H 9650 2000 50  0001 C CNN
	1    9650 2000
	0    -1   -1   0   
$EndComp
$Comp
L Device:C C13
U 1 1 5B1B3498
P 10900 2600
F 0 "C13" H 11015 2646 50  0000 L CNN
F 1 "10uF" H 11015 2555 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 10938 2450 50  0001 C CNN
F 3 "~" H 10900 2600 50  0001 C CNN
	1    10900 2600
	1    0    0    -1  
$EndComp
$Comp
L Device:R R17
U 1 1 5B1B35DB
P 10500 2600
F 0 "R17" H 10570 2646 50  0000 L CNN
F 1 "1.5k 1%" H 10570 2555 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 10430 2600 50  0001 C CNN
F 3 "~" H 10500 2600 50  0001 C CNN
	1    10500 2600
	1    0    0    -1  
$EndComp
$Comp
L Device:D_Schottky D2
U 1 1 5B1B3946
P 10350 2000
F 0 "D2" H 10350 2215 50  0000 C CNN
F 1 "FM5817" H 10350 2124 50  0000 C CNN
F 2 "brucon:DO-214-FM5817" H 10380 2150 20  0001 C CNN
F 3 "" H 10350 2000 50  0001 C CNN
	1    10350 2000
	-1   0    0    1   
$EndComp
$Comp
L Device:R R16
U 1 1 5B1B39F2
P 10500 2200
F 0 "R16" H 10570 2246 50  0000 L CNN
F 1 "9.0k 1%" H 10570 2155 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 10430 2200 50  0001 C CNN
F 3 "~" H 10500 2200 50  0001 C CNN
	1    10500 2200
	1    0    0    -1  
$EndComp
Wire Wire Line
	10500 2750 10900 2750
Connection ~ 10500 2750
Text GLabel 10250 2750 3    50   Input ~ 0
GND
Wire Wire Line
	9350 2000 9250 2000
Wire Wire Line
	9250 2000 9250 2350
Wire Wire Line
	9250 2000 8950 2000
Connection ~ 9250 2000
Text GLabel 8950 2000 0    50   Input ~ 0
VBAT
Wire Wire Line
	10200 2350 10200 2000
Wire Wire Line
	9500 2350 9250 2350
Wire Wire Line
	10200 2500 10350 2500
Wire Wire Line
	10350 2500 10350 2400
Wire Wire Line
	10350 2400 10500 2400
Wire Wire Line
	10500 2400 10500 2350
Wire Wire Line
	10500 2450 10500 2400
Connection ~ 10500 2400
Wire Wire Line
	10500 2000 10500 2050
Wire Wire Line
	10900 2000 10900 2450
Connection ~ 10500 2000
Wire Wire Line
	10900 2000 11050 2000
Connection ~ 10900 2000
Text GLabel 10650 1400 0    50   Input ~ 0
LCD_BACKLIGHT
Text Notes 8600 3050 0    50   ~ 0
boost: lcd backlight
Text GLabel 6900 1650 2    50   Input ~ 0
USBRX
Text GLabel 6900 1750 2    50   Input ~ 0
USBTX
Text GLabel 3800 1600 2    50   Input ~ 0
USBTX
Text GLabel 3800 1500 2    50   Input ~ 0
USBRX
Text GLabel 1950 1450 1    50   Input ~ 0
+3.3V
Text GLabel 1000 1600 0    50   Input ~ 0
CUT3VVBAT
Text GLabel 3800 2700 2    50   Input ~ 0
GND
Text GLabel 3800 2600 2    50   Input ~ 0
GND
Text GLabel 2450 3100 0    50   Input ~ 0
GND
Text GLabel 1950 2750 0    50   Input ~ 0
GND
$Comp
L Device:R R1
U 1 1 5B1D0F6A
P 1150 1600
F 0 "R1" V 943 1600 50  0000 C CNN
F 1 "100k" V 1034 1600 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 1080 1600 50  0001 C CNN
F 3 "~" H 1150 1600 50  0001 C CNN
	1    1150 1600
	0    -1   -1   0   
$EndComp
Wire Wire Line
	1950 1550 1950 1600
$Comp
L Device:C C1
U 1 1 5B1DAFE1
P 1550 1450
F 0 "C1" H 1665 1496 50  0000 L CNN
F 1 "1uF" H 1665 1405 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 1588 1300 50  0001 C CNN
F 3 "~" H 1550 1450 50  0001 C CNN
	1    1550 1450
	1    0    0    -1  
$EndComp
Connection ~ 1550 1600
Wire Wire Line
	1550 1600 1950 1600
Text GLabel 1550 1300 1    50   Input ~ 0
GND
Text GLabel 3800 2500 2    50   Input ~ 0
IO0
$Comp
L Switch:SW_SPST SW_RESET1
U 1 1 5B1F3B96
P 3450 6900
F 0 "SW_RESET1" H 3450 7135 50  0000 C CNN
F 1 "SW_SPST" H 3450 7044 50  0000 C CNN
F 2 "brucon:FSM4JSMATR" H 3450 6900 50  0001 C CNN
F 3 "" H 3450 6900 50  0001 C CNN
	1    3450 6900
	1    0    0    -1  
$EndComp
$Comp
L Device:C C2
U 1 1 5B1F3DD4
P 3650 7100
F 0 "C2" H 3765 7146 50  0000 L CNN
F 1 "1uF" H 3765 7055 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 3688 6950 50  0001 C CNN
F 3 "~" H 3650 7100 50  0001 C CNN
	1    3650 7100
	1    0    0    -1  
$EndComp
Wire Wire Line
	3650 6900 3650 6950
Text GLabel 6900 1950 2    50   Input ~ 0
DTR
Text GLabel 6900 1550 2    50   Input ~ 0
RTS
$Comp
L Device:R R9
U 1 1 5B24E75C
P 5850 6900
F 0 "R9" V 5643 6900 50  0000 C CNN
F 1 "1.0k 1%" V 5734 6900 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 5780 6900 50  0001 C CNN
F 3 "~" H 5850 6900 50  0001 C CNN
	1    5850 6900
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R10
U 1 1 5B24E806
P 5850 7400
F 0 "R10" V 5643 7400 50  0000 C CNN
F 1 "1.0k 1%" V 5734 7400 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 5780 7400 50  0001 C CNN
F 3 "~" H 5850 7400 50  0001 C CNN
	1    5850 7400
	0    -1   1    0   
$EndComp
$Comp
L Device:Q_NPN_BEC Q2
U 1 1 5B24E966
P 6200 6900
F 0 "Q2" H 6391 6946 50  0000 L CNN
F 1 "BT3904" H 6391 6855 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 6400 7000 50  0001 C CNN
F 3 "~" H 6200 6900 50  0001 C CNN
	1    6200 6900
	1    0    0    -1  
$EndComp
$Comp
L Device:Q_NPN_BEC Q3
U 1 1 5B24E9E4
P 6200 7400
F 0 "Q3" H 6391 7446 50  0000 L CNN
F 1 "BT3904" H 6391 7355 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 6400 7500 50  0001 C CNN
F 3 "~" H 6200 7400 50  0001 C CNN
	1    6200 7400
	1    0    0    1   
$EndComp
Text GLabel 5700 6900 0    50   Input ~ 0
DTR
Text GLabel 5700 7400 0    50   Input ~ 0
RTS
Wire Wire Line
	6300 6700 6650 6700
Text GLabel 1750 1600 3    50   Input ~ 0
EN
Text GLabel 6650 6700 2    50   Input ~ 0
EN
Text GLabel 6650 7600 2    50   Input ~ 0
IO0
Text GLabel 6900 1450 2    50   Input ~ 0
CTS
Wire Notes Line
	2900 6550 2900 7750
Wire Notes Line
	2900 7750 6900 7750
Wire Notes Line
	6900 7750 6900 6550
Text Notes 2950 7700 0    50   ~ 0
autoprog uart
Text GLabel 6400 2850 2    50   Input ~ 0
GND
Wire Wire Line
	6300 2850 6400 2850
$Comp
L Device:R R7
U 1 1 5B27C34B
P 5300 2400
F 0 "R7" V 5093 2400 50  0000 C CNN
F 1 "47.5k" V 5184 2400 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 5230 2400 50  0001 C CNN
F 3 "~" H 5300 2400 50  0001 C CNN
	1    5300 2400
	-1   0    0    -1  
$EndComp
$Comp
L Device:R R6
U 1 1 5B27C451
P 5300 2100
F 0 "R6" V 5093 2100 50  0000 C CNN
F 1 "22.1k" V 5184 2100 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 5230 2100 50  0001 C CNN
F 3 "~" H 5300 2100 50  0001 C CNN
	1    5300 2100
	-1   0    0    -1  
$EndComp
Wire Wire Line
	5150 2250 5150 1950
Wire Wire Line
	5150 1950 5200 1950
Connection ~ 5300 2250
Text GLabel 5300 2550 3    50   Input ~ 0
GND
Wire Wire Line
	5300 1950 5400 1950
Connection ~ 5300 1950
Wire Wire Line
	5700 1350 5550 1350
$Comp
L Device:C C4
U 1 1 5B295290
P 5200 1800
F 0 "C4" H 5315 1846 50  0000 L CNN
F 1 "4.7uF" H 5315 1755 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 5238 1650 50  0001 C CNN
F 3 "~" H 5200 1800 50  0001 C CNN
	1    5200 1800
	1    0    0    -1  
$EndComp
Connection ~ 5200 1950
Wire Wire Line
	5200 1950 5300 1950
Connection ~ 5400 1950
Wire Wire Line
	5400 1950 5700 1950
Text GLabel 5200 1650 1    50   Input ~ 0
GND
Wire Wire Line
	6200 1050 6300 1050
$Comp
L Device:C C7
U 1 1 5B2A0320
P 6200 900
F 0 "C7" H 6315 946 50  0000 L CNN
F 1 "0.1uF" H 6400 900 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 6238 750 50  0001 C CNN
F 3 "~" H 6200 900 50  0001 C CNN
	1    6200 900 
	1    0    0    -1  
$EndComp
Wire Wire Line
	6200 750  6000 750 
Text GLabel 6000 750  0    50   Input ~ 0
GND
Wire Wire Line
	6000 1050 6200 1050
$Comp
L Device:C C6
U 1 1 5B2A0317
P 6000 900
F 0 "C6" H 6115 946 50  0000 L CNN
F 1 "4.7uF" H 5700 900 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 6038 750 50  0001 C CNN
F 3 "~" H 6000 900 50  0001 C CNN
	1    6000 900 
	1    0    0    -1  
$EndComp
Connection ~ 6200 1050
Wire Notes Line
	10700 3150 8050 3150
Wire Notes Line
	8550 1850 11200 1850
Wire Notes Line
	11200 6050 9250 6050
Wire Notes Line
	6650 5800 6650 6500
Wire Notes Line
	6650 6500 11200 6500
Wire Wire Line
	5300 2250 5700 2250
$Comp
L Device:R R8
U 1 1 5B3A044C
P 5550 1200
F 0 "R8" H 5620 1246 50  0000 L CNN
F 1 "1.0k 1%" H 5620 1155 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 5480 1200 50  0001 C CNN
F 3 "~" H 5550 1200 50  0001 C CNN
	1    5550 1200
	1    0    0    -1  
$EndComp
Wire Wire Line
	5550 1050 6000 1050
Connection ~ 6000 1050
Text GLabel 3200 7250 3    50   Input ~ 0
GND
Wire Wire Line
	3250 6900 3250 7250
Wire Wire Line
	3200 7250 3250 7250
Connection ~ 3250 7250
Wire Wire Line
	3250 7250 3650 7250
$Comp
L Device:R R4
U 1 1 5B3BCB9F
P 3800 6900
F 0 "R4" V 3593 6900 50  0000 C CNN
F 1 "10K" V 3684 6900 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 3730 6900 50  0001 C CNN
F 3 "~" H 3800 6900 50  0001 C CNN
	1    3800 6900
	0    1    1    0   
$EndComp
Connection ~ 3650 6900
Text GLabel 3950 6900 2    50   Input ~ 0
EN
Text GLabel 4400 7250 3    50   Input ~ 0
GND
Text GLabel 5150 6900 2    50   Input ~ 0
IO0
$Comp
L Device:R R3
U 1 1 5B3C34C6
P 3500 3100
F 0 "R3" V 3293 3100 50  0000 C CNN
F 1 "10k" V 3384 3100 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 3430 3100 50  0001 C CNN
F 3 "~" H 3500 3100 50  0001 C CNN
	1    3500 3100
	0    1    1    0   
$EndComp
Text GLabel 3650 3100 2    50   Input ~ 0
GND
Text GLabel 950  7000 0    50   Input ~ 0
+3.3V
Text GLabel 1450 7000 2    50   Input ~ 0
+3.3V
Text GLabel 1450 7400 2    50   Input ~ 0
GND
Text GLabel 1450 7300 2    50   Input ~ 0
LCD_SCK
Text GLabel 950  7400 0    50   Input ~ 0
LCD_DIO
Text GLabel 1450 7100 2    50   Input ~ 0
LCD_CS
Text GLabel 950  7200 0    50   Input ~ 0
LCD_RST
Text GLabel 3800 1900 2    50   Input ~ 0
LCD_SCK
Text GLabel 3800 1300 2    50   Input ~ 0
LCD_DIO
Text GLabel 3800 1400 2    50   Input ~ 0
LCD_CS
Text GLabel 3800 2000 2    50   Input ~ 0
LCD_RST
Text GLabel 3800 1700 2    50   Input ~ 0
EN_BACKLIGHT
Text Notes 6950 6400 0    50   ~ 0
3.3v ldo
$Comp
L BruCON_0x0a-rescue:NCP5661-Brucon U3
U 1 1 5B40E8B9
P 7950 6150
F 0 "U3" H 7975 6525 50  0000 C CNN
F 1 "NCP5661" H 7975 6434 50  0000 C CNN
F 2 "CSK:DFN6-3.6x2.15mmP0.95" H 7950 6150 50  0001 C CNN
F 3 "" H 7950 6150 50  0001 C CNN
	1    7950 6150
	1    0    0    -1  
$EndComp
Text GLabel 7550 6150 0    50   Input ~ 0
VBAT
Wire Wire Line
	7550 6150 7550 6300
Text GLabel 7550 6000 0    50   Input ~ 0
CUT3VVBAT
Text GLabel 8400 6000 2    50   Input ~ 0
GND
Text GLabel 8400 6150 2    50   Input ~ 0
+3.3V
Text GLabel 950  7100 0    50   Input ~ 0
LCD_BACKLIGHT
$Comp
L power:GNDREF #PWR0101
U 1 1 5B41E326
P 6450 6100
F 0 "#PWR0101" H 6450 5850 50  0001 C CNN
F 1 "GNDREF" V 6455 5972 50  0000 R CNN
F 2 "" H 6450 6100 50  0001 C CNN
F 3 "" H 6450 6100 50  0001 C CNN
	1    6450 6100
	0    -1   -1   0   
$EndComp
Wire Wire Line
	6350 6100 6450 6100
Connection ~ 10200 2000
Wire Wire Line
	9950 2000 10200 2000
Wire Wire Line
	10400 2000 10500 2000
Wire Wire Line
	3250 3100 3250 3150
Text GLabel 1350 4550 1    50   Input ~ 0
DIR_UP
Text GLabel 1600 4550 1    50   Input ~ 0
DIR_DOWN
Text GLabel 1800 4550 1    50   Input ~ 0
DIR_LEFT
Text GLabel 2000 4550 1    50   Input ~ 0
DIR_RIGHT
Text GLabel 2200 4550 1    50   Input ~ 0
BUTTON_A
Text GLabel 2450 4550 1    50   Input ~ 0
BUTTON_B
Text GLabel 1950 2650 0    50   Input ~ 0
DIR_UP
Text GLabel 1950 2550 0    50   Input ~ 0
DIR_RIGHT
Text GLabel 2550 3100 3    50   Input ~ 0
DIR_LEFT
Text GLabel 1950 2450 0    50   Input ~ 0
DIR_DOWN
Text GLabel 1950 2050 0    50   Input ~ 0
BUTTON_A
Text GLabel 1950 2150 0    50   Input ~ 0
BUTTON_B
Wire Wire Line
	6300 7600 6650 7600
Wire Wire Line
	5700 7200 6300 7200
Wire Wire Line
	5700 6900 5700 7200
Wire Wire Line
	5700 7400 5700 7250
Wire Wire Line
	5700 7250 5950 7250
Wire Wire Line
	5950 7250 5950 7100
Wire Wire Line
	5950 7100 6300 7100
Wire Wire Line
	5200 1650 5400 1650
Wire Wire Line
	9850 2750 10500 2750
Text GLabel 9500 2500 0    50   Input ~ 0
EN_BACKLIGHT
Text GLabel 950  7300 0    50   Input ~ 0
GND
$Comp
L Device:LED LED4
U 1 1 5B4D61AD
P 4450 2900
F 0 "LED4" H 4287 2804 50  0000 R CNN
F 1 "LED" H 4287 2895 50  0000 R CNN
F 2 "LED_SMD:LED_0603_1608Metric" H 4480 3050 20  0001 C CNN
F 3 "" H 4450 2900 50  0001 C CNN
	1    4450 2900
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R2
U 1 1 5B4D62D7
P 4450 2600
F 0 "R2" V 4243 2600 50  0000 C CNN
F 1 "75R" V 4334 2600 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 4380 2600 50  0001 C CNN
F 3 "~" H 4450 2600 50  0001 C CNN
	1    4450 2600
	-1   0    0    -1  
$EndComp
Wire Wire Line
	3800 2100 4450 2100
Wire Wire Line
	4450 2100 4450 2450
Text GLabel 4450 3050 0    50   Input ~ 0
GND
Wire Notes Line
	8550 500  11200 500 
$Comp
L Switch:SW_DPDT_x2 SW1
U 1 1 5CD2C31F
P 9350 6300
F 0 "SW1" H 9350 6585 50  0000 C CNN
F 1 "SW_DPDT_x2" H 9350 6494 50  0000 C CNN
F 2 "brucon_0xb:JS102000-SAQN" H 9350 6300 50  0001 C CNN
F 3 "" H 9350 6300 50  0001 C CNN
	1    9350 6300
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x01_Female J5
U 1 1 5CE363C1
P 1350 4750
F 0 "J5" V 1196 4798 50  0000 L CNN
F 1 "Conn_01x01_Female" V 1287 4798 50  0000 L CNN
F 2 "brucon_0xb:touch_10mm" H 1350 4750 50  0001 C CNN
F 3 "~" H 1350 4750 50  0001 C CNN
	1    1350 4750
	0    1    1    0   
$EndComp
Wire Wire Line
	1300 1600 1550 1600
$Comp
L Connector:Conn_01x01_Female J6
U 1 1 5CE3DAFC
P 1600 4750
F 0 "J6" V 1446 4798 50  0000 L CNN
F 1 "Conn_01x01_Female" V 1537 4798 50  0000 L CNN
F 2 "brucon_0xb:touch_10mm" H 1600 4750 50  0001 C CNN
F 3 "~" H 1600 4750 50  0001 C CNN
	1    1600 4750
	0    1    1    0   
$EndComp
$Comp
L Connector:Conn_01x01_Female J7
U 1 1 5CE3DD74
P 1800 4750
F 0 "J7" V 1646 4798 50  0000 L CNN
F 1 "Conn_01x01_Female" V 1737 4798 50  0000 L CNN
F 2 "brucon_0xb:touch_10mm" H 1800 4750 50  0001 C CNN
F 3 "~" H 1800 4750 50  0001 C CNN
	1    1800 4750
	0    1    1    0   
$EndComp
$Comp
L Connector:Conn_01x01_Female J8
U 1 1 5CE3DF6D
P 2000 4750
F 0 "J8" V 1846 4798 50  0000 L CNN
F 1 "Conn_01x01_Female" V 1937 4798 50  0000 L CNN
F 2 "brucon_0xb:touch_10mm" H 2000 4750 50  0001 C CNN
F 3 "~" H 2000 4750 50  0001 C CNN
	1    2000 4750
	0    1    1    0   
$EndComp
$Comp
L Connector:Conn_01x01_Female J9
U 1 1 5CE3E26C
P 2200 4750
F 0 "J9" V 2046 4798 50  0000 L CNN
F 1 "Conn_01x01_Female" V 2137 4798 50  0000 L CNN
F 2 "brucon_0xb:touch_10mm" H 2200 4750 50  0001 C CNN
F 3 "~" H 2200 4750 50  0001 C CNN
	1    2200 4750
	0    1    1    0   
$EndComp
$Comp
L Connector:Conn_01x01_Female J10
U 1 1 5CE3E4CA
P 2450 4750
F 0 "J10" V 2296 4798 50  0000 L CNN
F 1 "Conn_01x01_Female" V 2387 4798 50  0000 L CNN
F 2 "brucon_0xb:touch_10mm" H 2450 4750 50  0001 C CNN
F 3 "~" H 2450 4750 50  0001 C CNN
	1    2450 4750
	0    1    1    0   
$EndComp
Wire Wire Line
	8950 4250 9450 4250
Wire Wire Line
	9450 4250 9450 4050
Text GLabel 10650 3650 2    50   Input ~ 0
VBAT
$Comp
L Device:R R25
U 1 1 5CE48D23
P 10750 4200
F 0 "R25" H 10820 4246 50  0000 L CNN
F 1 "1.47k 1%" H 10820 4155 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 10680 4200 50  0001 C CNN
F 3 "~" H 10750 4200 50  0001 C CNN
	1    10750 4200
	1    0    0    -1  
$EndComp
$Comp
L BruCON_0x0a-rescue:AAT3693 U4
U 1 1 5CE41BDC
P 9900 3800
F 0 "U4" H 9925 4215 50  0000 C CNN
F 1 "AAT3693-AA" H 9925 4124 50  0000 C CNN
F 2 "brucon_0xb:aat3693" H 9550 4150 50  0001 C CNN
F 3 "" H 9550 4150 50  0001 C CNN
	1    9900 3800
	1    0    0    -1  
$EndComp
Wire Wire Line
	10400 3950 10550 3950
Wire Wire Line
	10550 3950 10550 4050
$Comp
L Device:R R21
U 1 1 5CE4E3BE
P 9050 3400
F 0 "R21" H 9120 3446 50  0000 L CNN
F 1 "1.47k 1%" H 9120 3355 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 8980 3400 50  0001 C CNN
F 3 "~" H 9050 3400 50  0001 C CNN
	1    9050 3400
	1    0    0    -1  
$EndComp
$Comp
L Device:R R22
U 1 1 5CE4EAC9
P 9150 3400
F 0 "R22" H 9220 3446 50  0000 L CNN
F 1 "1.47k 1%" H 9220 3355 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 9080 3400 50  0001 C CNN
F 3 "~" H 9150 3400 50  0001 C CNN
	1    9150 3400
	1    0    0    -1  
$EndComp
$Comp
L Device:LED D1
U 1 1 5CE4FD0C
P 9200 3850
F 0 "D1" H 9193 3595 50  0000 C CNN
F 1 "LED" H 9193 3686 50  0000 C CNN
F 2 "LED_SMD:LED_0603_1608Metric" H 9200 3850 50  0001 C CNN
F 3 "~" H 9200 3850 50  0001 C CNN
	1    9200 3850
	-1   0    0    1   
$EndComp
$Comp
L Device:LED D3
U 1 1 5CE508F0
P 9300 3700
F 0 "D3" H 9293 3445 50  0000 C CNN
F 1 "LED" H 9293 3536 50  0000 C CNN
F 2 "LED_SMD:LED_0603_1608Metric" H 9300 3700 50  0001 C CNN
F 3 "~" H 9300 3700 50  0001 C CNN
	1    9300 3700
	-1   0    0    1   
$EndComp
Wire Wire Line
	9050 3550 9050 3850
Wire Wire Line
	9450 3700 9450 3750
Wire Wire Line
	9350 3850 9450 3850
Wire Wire Line
	9150 3700 9150 3550
Wire Wire Line
	8950 3500 8950 3250
Wire Wire Line
	8950 3250 9050 3250
Wire Wire Line
	9450 3250 9450 3650
Connection ~ 8950 3500
Connection ~ 9050 3250
Wire Wire Line
	9050 3250 9150 3250
Connection ~ 9150 3250
$Comp
L Device:C C12
U 1 1 5CE5D5DB
P 10500 3500
F 0 "C12" H 10615 3546 50  0000 L CNN
F 1 "10uF" H 10615 3455 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 10538 3350 50  0001 C CNN
F 3 "~" H 10500 3500 50  0001 C CNN
	1    10500 3500
	1    0    0    -1  
$EndComp
Text GLabel 10500 3350 0    50   Input ~ 0
GND
Wire Wire Line
	10400 3650 10500 3650
Connection ~ 10500 3650
Wire Wire Line
	10500 3650 10650 3650
$Comp
L Device:R R23
U 1 1 5CE63CFE
P 9200 3950
F 0 "R23" H 9270 3996 50  0000 L CNN
F 1 "10k 1%" H 9270 3905 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 9130 3950 50  0001 C CNN
F 3 "~" H 9200 3950 50  0001 C CNN
	1    9200 3950
	0    -1   -1   0   
$EndComp
Wire Wire Line
	8950 3950 9050 3950
Connection ~ 8950 3950
Wire Wire Line
	9350 3950 9450 3950
Text GLabel 9900 3300 2    50   Input ~ 0
STAT1
Text GLabel 9600 3350 2    50   Input ~ 0
STAT2
Wire Wire Line
	9450 3700 9400 3700
Wire Wire Line
	9400 3700 9400 3300
Connection ~ 9450 3700
Wire Wire Line
	9450 3850 9550 3850
Wire Wire Line
	9550 3850 9550 3350
Wire Wire Line
	9550 3350 9600 3350
Connection ~ 9450 3850
Text GLabel 1700 1000 1    50   Input ~ 0
STAT1
Text GLabel 1800 1000 1    50   Input ~ 0
STAT2
Wire Wire Line
	9150 3250 9450 3250
Connection ~ 9450 3250
$Comp
L Device:R R24
U 1 1 5CE70F18
P 11050 3600
F 0 "R24" H 11120 3646 50  0000 L CNN
F 1 "10k 1%" H 10950 3450 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 10980 3600 50  0001 C CNN
F 3 "~" H 11050 3600 50  0001 C CNN
	1    11050 3600
	-1   0    0    1   
$EndComp
$Comp
L Device:R R27
U 1 1 5CE7B47F
P 11050 3900
F 0 "R27" H 11120 3946 50  0000 L CNN
F 1 "10k 1%" H 11120 3855 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 10980 3900 50  0001 C CNN
F 3 "~" H 11050 3900 50  0001 C CNN
	1    11050 3900
	-1   0    0    1   
$EndComp
$Comp
L Device:C C8
U 1 1 5CE8A9F8
P 10400 4200
F 0 "C8" H 10515 4246 50  0000 L CNN
F 1 "0.1uF" H 10515 4155 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 10438 4050 50  0001 C CNN
F 3 "~" H 10400 4200 50  0001 C CNN
	1    10400 4200
	1    0    0    -1  
$EndComp
Text GLabel 10250 4350 3    50   Input ~ 0
GND
Wire Wire Line
	10250 4350 10400 4350
Connection ~ 10400 4350
Wire Wire Line
	11050 4350 11050 4050
$Comp
L Device:R R14
U 1 1 5CE9604C
P 600 2300
F 0 "R14" H 670 2346 50  0000 L CNN
F 1 "100k 1%" H 670 2255 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 530 2300 50  0001 C CNN
F 3 "~" H 600 2300 50  0001 C CNN
	1    600  2300
	1    0    0    -1  
$EndComp
$Comp
L Device:R R13
U 1 1 5CE96F69
P 600 2000
F 0 "R13" H 670 2046 50  0000 L CNN
F 1 "100k 1%" H 670 1955 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 530 2000 50  0001 C CNN
F 3 "~" H 600 2000 50  0001 C CNN
	1    600  2000
	1    0    0    -1  
$EndComp
$Comp
L Device:R R20
U 1 1 5CE990CA
P 1000 2300
F 0 "R20" H 1070 2346 50  0000 L CNN
F 1 "100k 1%" H 1070 2255 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 930 2300 50  0001 C CNN
F 3 "~" H 1000 2300 50  0001 C CNN
	1    1000 2300
	1    0    0    -1  
$EndComp
$Comp
L Device:R R19
U 1 1 5CE990D4
P 1000 2000
F 0 "R19" H 1070 2046 50  0000 L CNN
F 1 "27k 1%" H 1070 1955 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 930 2000 50  0001 C CNN
F 3 "~" H 1000 2000 50  0001 C CNN
	1    1000 2000
	1    0    0    -1  
$EndComp
Text GLabel 800  2450 3    50   Input ~ 0
GND
Wire Wire Line
	600  2450 1000 2450
Text GLabel 8950 3250 0    50   Input ~ 0
VBUS
Text GLabel 1000 1850 2    50   Input ~ 0
VBAT
Text GLabel 600  1850 2    50   Input ~ 0
VBUS
Wire Wire Line
	600  2150 900  2150
Wire Wire Line
	900  2150 900  1750
Wire Wire Line
	900  1750 1650 1750
Wire Wire Line
	1650 1750 1650 1850
Wire Wire Line
	1650 1850 1950 1850
Connection ~ 600  2150
Wire Wire Line
	1000 2150 1400 2150
Wire Wire Line
	1400 2150 1400 1950
Wire Wire Line
	1400 1950 1950 1950
Connection ~ 1000 2150
Wire Wire Line
	1700 1000 1700 1350
Wire Wire Line
	1700 1350 1850 1350
Wire Wire Line
	1850 1750 1950 1750
Wire Wire Line
	1850 1350 1850 1750
Wire Wire Line
	1950 1650 1900 1650
Wire Wire Line
	1900 1650 1900 1000
Wire Wire Line
	1900 1000 1800 1000
Text GLabel 1950 2250 0    50   Input ~ 0
I2C_SDA
Text GLabel 1950 2350 0    50   Input ~ 0
I2C_SCL
$Comp
L Device:R R15
U 1 1 5CED088E
P 750 3400
F 0 "R15" H 820 3446 50  0000 L CNN
F 1 "2k 1%" H 820 3355 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 680 3400 50  0001 C CNN
F 3 "~" H 750 3400 50  0001 C CNN
	1    750  3400
	1    0    0    -1  
$EndComp
$Comp
L Device:R R18
U 1 1 5CED0CBA
P 950 3400
F 0 "R18" H 1020 3446 50  0000 L CNN
F 1 "2k 1%" H 1020 3355 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 880 3400 50  0001 C CNN
F 3 "~" H 950 3400 50  0001 C CNN
	1    950  3400
	1    0    0    -1  
$EndComp
Text GLabel 750  3550 0    50   Input ~ 0
I2C_SCL
Text GLabel 950  3550 2    50   Input ~ 0
I2C_SDA
Text GLabel 750  3250 1    50   Input ~ 0
+3.3V
Wire Wire Line
	750  3250 950  3250
$Comp
L Connector_Generic:Conn_02x02_Top_Bottom J2
U 1 1 5CED9225
P 1000 3900
F 0 "J2" H 1050 4117 50  0000 C CNN
F 1 "Conn_02x02_Top_Bottom" H 1050 4100 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_2x02_P2.54mm_Vertical" H 1000 3900 50  0001 C CNN
F 3 "~" H 1000 3900 50  0001 C CNN
	1    1000 3900
	1    0    0    -1  
$EndComp
Text GLabel 800  3900 0    50   Input ~ 0
+3.3V
Text GLabel 800  4000 0    50   Input ~ 0
GND
Text GLabel 1300 3900 2    50   Input ~ 0
I2C_SDA
Text GLabel 1300 4000 2    50   Input ~ 0
I2C_SCL
Connection ~ 4450 7250
Wire Wire Line
	4450 7250 4850 7250
Wire Wire Line
	4400 7250 4450 7250
Connection ~ 4850 6900
$Comp
L Device:R R5
U 1 1 5B3BD1ED
P 5000 6900
F 0 "R5" V 4793 6900 50  0000 C CNN
F 1 "10K" V 4884 6900 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 4930 6900 50  0001 C CNN
F 3 "~" H 5000 6900 50  0001 C CNN
	1    5000 6900
	0    1    1    0   
$EndComp
Wire Wire Line
	4450 6900 4450 7250
Wire Wire Line
	4850 6900 4850 6950
$Comp
L Device:C C3
U 1 1 5B3BD1E1
P 4850 7100
F 0 "C3" H 4965 7146 50  0000 L CNN
F 1 "1uF" H 4965 7055 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 4888 6950 50  0001 C CNN
F 3 "~" H 4850 7100 50  0001 C CNN
	1    4850 7100
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_SPST SW_PROG1
U 1 1 5B3BD1DB
P 4650 6900
F 0 "SW_PROG1" H 4650 7135 50  0000 C CNN
F 1 "SW_SPST" H 4650 7044 50  0000 C CNN
F 2 "brucon:FSM4JSMATR" H 4650 6900 50  0001 C CNN
F 3 "" H 4650 6900 50  0001 C CNN
	1    4650 6900
	1    0    0    -1  
$EndComp
Wire Notes Line
	6900 6550 2900 6550
Wire Wire Line
	9400 3300 9900 3300
Text GLabel 5150 2250 0    50   Input ~ 0
VBUS
Text GLabel 8650 4600 2    50   Input ~ 0
VBUS
$Comp
L Device:R R28
U 1 1 5CF984B2
P 9700 6400
F 0 "R28" V 9493 6400 50  0000 C CNN
F 1 "5k" V 9584 6400 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 9630 6400 50  0001 C CNN
F 3 "~" H 9700 6400 50  0001 C CNN
	1    9700 6400
	0    1    1    0   
$EndComp
Text GLabel 9850 6400 2    50   Input ~ 0
GND
Text GLabel 9350 5200 2    50   Input ~ 0
GND
Text GLabel 9350 5300 2    50   Input ~ 0
VBAT
Connection ~ 11050 3750
Wire Wire Line
	11050 3250 11050 3450
Wire Wire Line
	9450 3250 11050 3250
Wire Wire Line
	10400 3750 11050 3750
Connection ~ 10750 4350
Wire Wire Line
	10750 4350 11050 4350
Wire Wire Line
	10400 4350 10750 4350
Wire Wire Line
	10550 4050 10750 4050
$Comp
L Device:C C9
U 1 1 5D597996
P 8850 6000
F 0 "C9" H 8965 6046 50  0000 L CNN
F 1 "4.7uF" H 8965 5955 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 8888 5850 50  0001 C CNN
F 3 "~" H 8850 6000 50  0001 C CNN
	1    8850 6000
	1    0    0    -1  
$EndComp
Wire Wire Line
	8400 6150 8400 6250
Wire Wire Line
	8400 6250 8850 6250
Wire Wire Line
	8850 6250 8850 6150
Wire Wire Line
	8400 6000 8400 5850
Wire Wire Line
	8400 5850 8850 5850
$Comp
L Device:C C11
U 1 1 5D5A6CE9
P 1400 6600
F 0 "C11" H 1515 6646 50  0000 L CNN
F 1 "10uF" H 1515 6555 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 1438 6450 50  0001 C CNN
F 3 "~" H 1400 6600 50  0001 C CNN
	1    1400 6600
	1    0    0    -1  
$EndComp
Wire Wire Line
	950  7000 950  6750
Wire Wire Line
	950  6750 1400 6750
Connection ~ 1400 6750
Wire Wire Line
	1400 7000 1450 7000
Wire Wire Line
	1400 6750 1400 7000
Wire Wire Line
	1400 6450 2100 6450
Wire Wire Line
	2100 6450 2100 7600
Wire Wire Line
	2100 7600 1450 7600
Wire Wire Line
	1450 7600 1450 7400
$Comp
L Device:C C14
U 1 1 5D5C3CC2
P 2050 750
F 0 "C14" H 2165 796 50  0000 L CNN
F 1 "10uF" H 2165 705 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 2088 600 50  0001 C CNN
F 3 "~" H 2050 750 50  0001 C CNN
	1    2050 750 
	1    0    0    -1  
$EndComp
$Comp
L ESP32-footprints-Shem-Lib:ESP32-WROOM U1
U 1 1 5B1A445A
P 2900 2050
F 0 "U1" H 2875 3437 60  0000 C CNN
F 1 "ESP32-WROOM" H 2875 3331 60  0000 C CNN
F 2 "ESP32-footprints-Lib:ESP32-WROOM" H 3250 3400 60  0001 C CNN
F 3 "" H 2450 2500 60  0001 C CNN
	1    2900 2050
	1    0    0    -1  
$EndComp
Wire Wire Line
	1950 1450 2050 1450
Wire Wire Line
	2050 1450 2050 900 
Wire Wire Line
	1550 1300 1350 1300
Wire Wire Line
	1350 1300 1350 600 
Wire Wire Line
	1350 600  2050 600 
Wire Wire Line
	9550 6200 10000 6200
Wire Wire Line
	10000 6200 10000 6150
$Comp
L Device:R R26
U 1 1 5D676F37
P 10650 1550
F 0 "R26" H 10720 1596 50  0000 L CNN
F 1 "1k 1%" H 10720 1505 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 10580 1550 50  0001 C CNN
F 3 "~" H 10650 1550 50  0001 C CNN
	1    10650 1550
	1    0    0    -1  
$EndComp
Wire Wire Line
	10650 1700 10650 2000
Wire Wire Line
	10500 2000 10650 2000
Connection ~ 10650 2000
Wire Wire Line
	10650 2000 10900 2000
$Comp
L Device:R R11
U 1 1 5B2955AC
P 5400 1800
F 0 "R11" H 5515 1846 50  0000 L CNN
F 1 "1 M" H 5515 1755 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" H 5438 1650 50  0001 C CNN
F 3 "~" H 5400 1800 50  0001 C CNN
	1    5400 1800
	1    0    0    -1  
$EndComp
$EndSCHEMATC
