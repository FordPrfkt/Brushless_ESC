EESchema Schematic File Version 2
LIBS:power
LIBS:device
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:74xgxx
LIBS:ac-dc
LIBS:actel
LIBS:Altera
LIBS:analog_devices
LIBS:brooktre
LIBS:cmos_ieee
LIBS:dc-dc
LIBS:diode
LIBS:elec-unifil
LIBS:ESD_Protection
LIBS:ftdi
LIBS:gennum
LIBS:graphic
LIBS:hc11
LIBS:ir
LIBS:Lattice
LIBS:logo
LIBS:maxim
LIBS:microchip_dspic33dsc
LIBS:microchip_pic10mcu
LIBS:microchip_pic12mcu
LIBS:microchip_pic16mcu
LIBS:microchip_pic18mcu
LIBS:microchip_pic32mcu
LIBS:motor_drivers
LIBS:msp430
LIBS:nordicsemi
LIBS:nxp_armmcu
LIBS:onsemi
LIBS:Oscillators
LIBS:Power_Management
LIBS:powerint
LIBS:pspice
LIBS:references
LIBS:relays
LIBS:rfcom
LIBS:sensors
LIBS:silabs
LIBS:stm8
LIBS:stm32
LIBS:supertex
LIBS:switches
LIBS:transf
LIBS:ttl_ieee
LIBS:video
LIBS:Xicor
LIBS:Zilog
LIBS:crystal
LIBS:crystal-epson
LIBS:Brushless_ESC-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 2 3
Title "Brushless ESC"
Date "2015-09-19"
Rev "1.0"
Comp "Daniel Walter"
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Text HLabel 6150 4550 2    60   Output ~ 0
PWM
Text HLabel 3100 4100 0    60   Input ~ 0
V_Bat
Text HLabel 6150 3900 2    60   Input ~ 0
BEMF_A
Text HLabel 6150 3800 2    60   Input ~ 0
BEMF_B
Text HLabel 6150 3700 2    60   Input ~ 0
BEMF_C
Text HLabel 6150 4850 2    60   Input ~ 0
BEMF_Center
$Comp
L C C1
U 1 1 55E381AA
P 1900 1650
F 0 "C1" H 1925 1750 50  0000 L CNN
F 1 "100nF" H 1925 1550 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603_HandSoldering" H 1938 1500 30  0001 C CNN
F 3 "" H 1900 1650 60  0000 C CNN
	1    1900 1650
	1    0    0    -1  
$EndComp
$Comp
L C C2
U 1 1 55E3821A
P 2150 1650
F 0 "C2" H 2175 1750 50  0000 L CNN
F 1 "100nF" H 2175 1550 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603_HandSoldering" H 2188 1500 30  0001 C CNN
F 3 "" H 2150 1650 60  0000 C CNN
	1    2150 1650
	1    0    0    -1  
$EndComp
Text HLabel 6150 2850 2    60   Input ~ 0
SS
Text HLabel 6150 3050 2    60   Input ~ 0
MISO
Text HLabel 6150 2950 2    60   Input ~ 0
MOSI
Text HLabel 6150 3150 2    60   Input ~ 0
SCK
Text HLabel 6150 3600 2    60   Input ~ 0
BatCurrent+
Text HLabel 6150 4750 2    60   Output ~ 0
IN_A
Text HLabel 6150 4650 2    60   Output ~ 0
IN_B
Text HLabel 6150 4350 2    60   Output ~ 0
IN_C
Text HLabel 6150 4950 2    60   Output ~ 0
/SD_A
Text HLabel 6150 4450 2    60   Output ~ 0
/SD_B
Text HLabel 6150 4250 2    60   Output ~ 0
/SD_C
Text HLabel 6150 2650 2    60   Input ~ 0
PPM
$Comp
L LED D1
U 1 1 55E38A30
P 7150 3800
F 0 "D1" H 7150 3900 50  0000 C CNN
F 1 "LED" H 7150 3700 50  0000 C CNN
F 2 "LEDs:LED-0805" H 7150 3800 60  0001 C CNN
F 3 "" H 7150 3800 60  0000 C CNN
	1    7150 3800
	-1   0    0    -1  
$EndComp
$Comp
L GND #PWR05
U 1 1 55E38EAC
P 7600 3350
F 0 "#PWR05" H 7600 3100 50  0001 C CNN
F 1 "GND" H 7600 3200 50  0000 C CNN
F 2 "" H 7600 3350 60  0000 C CNN
F 3 "" H 7600 3350 60  0000 C CNN
	1    7600 3350
	-1   0    0    -1  
$EndComp
Wire Wire Line
	7400 3300 7600 3300
Wire Wire Line
	7600 3300 7600 3350
Connection ~ 7400 3300
$Comp
L GND #PWR06
U 1 1 55E39164
P 3350 5100
F 0 "#PWR06" H 3350 4850 50  0001 C CNN
F 1 "GND" H 3350 4950 50  0000 C CNN
F 2 "" H 3350 5100 60  0000 C CNN
F 3 "" H 3350 5100 60  0000 C CNN
	1    3350 5100
	1    0    0    -1  
$EndComp
Wire Wire Line
	3450 4850 3350 4850
Wire Wire Line
	3350 4750 3350 5100
$Comp
L +5V #PWR07
U 1 1 55E3935A
P 3150 2400
F 0 "#PWR07" H 3150 2250 50  0001 C CNN
F 1 "+5V" H 3150 2540 50  0000 C CNN
F 2 "" H 3150 2400 60  0000 C CNN
F 3 "" H 3150 2400 60  0000 C CNN
	1    3150 2400
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR08
U 1 1 55E394C4
P 2150 1350
F 0 "#PWR08" H 2150 1200 50  0001 C CNN
F 1 "+5V" H 2150 1490 50  0000 C CNN
F 2 "" H 2150 1350 60  0000 C CNN
F 3 "" H 2150 1350 60  0000 C CNN
	1    2150 1350
	1    0    0    -1  
$EndComp
Wire Wire Line
	1900 1350 1900 1500
Connection ~ 2150 1350
Wire Wire Line
	2150 1500 2150 1350
$Comp
L GND #PWR09
U 1 1 55E3966E
P 2150 1900
F 0 "#PWR09" H 2150 1650 50  0001 C CNN
F 1 "GND" H 2150 1750 50  0000 C CNN
F 2 "" H 2150 1900 60  0000 C CNN
F 3 "" H 2150 1900 60  0000 C CNN
	1    2150 1900
	1    0    0    -1  
$EndComp
Wire Wire Line
	1900 1800 1900 1900
Connection ~ 2150 1900
Wire Wire Line
	2150 1800 2150 1900
Text HLabel 6150 4100 2    60   Input ~ 0
Reset
Wire Wire Line
	6150 4850 5350 4850
$Comp
L R R1
U 1 1 55E41F1D
P 5750 3500
F 0 "R1" V 5830 3500 50  0000 C CNN
F 1 "220R" V 5750 3500 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 5680 3500 30  0001 C CNN
F 3 "" H 5750 3500 30  0000 C CNN
	1    5750 3500
	0    1    1    0   
$EndComp
$Comp
L R R26
U 1 1 55E48201
P 5750 2650
F 0 "R26" V 5830 2650 50  0000 C CNN
F 1 "1k" V 5750 2650 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 5680 2650 30  0001 C CNN
F 3 "" H 5750 2650 30  0000 C CNN
	1    5750 2650
	0    1    1    0   
$EndComp
Wire Wire Line
	5350 4550 6150 4550
$Comp
L R R28
U 1 1 55E48896
P 5750 3050
F 0 "R28" V 5830 3050 50  0000 C CNN
F 1 "1k" V 5750 3050 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 5680 3050 30  0001 C CNN
F 3 "" H 5750 3050 30  0000 C CNN
	1    5750 3050
	0    1    1    0   
$EndComp
$Comp
L R R29
U 1 1 55E4890A
P 5750 2950
F 0 "R29" V 5830 2950 50  0000 C CNN
F 1 "1k" V 5750 2950 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 5680 2950 30  0001 C CNN
F 3 "" H 5750 2950 30  0000 C CNN
	1    5750 2950
	0    1    1    0   
$EndComp
$Comp
L R R30
U 1 1 55E48957
P 5750 3150
F 0 "R30" V 5830 3150 50  0000 C CNN
F 1 "1k" V 5750 3150 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 5680 3150 30  0001 C CNN
F 3 "" H 5750 3150 30  0000 C CNN
	1    5750 3150
	0    1    1    0   
$EndComp
Wire Wire Line
	6150 3150 5900 3150
Wire Wire Line
	5900 2950 6150 2950
Wire Wire Line
	6150 3050 5900 3050
Wire Wire Line
	5600 3150 5350 3150
Wire Wire Line
	5350 2950 5600 2950
Wire Wire Line
	5600 3050 5350 3050
$Comp
L R R27
U 1 1 55E48C68
P 5750 2850
F 0 "R27" V 5830 2850 50  0000 C CNN
F 1 "1k" V 5750 2850 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 5680 2850 30  0001 C CNN
F 3 "" H 5750 2850 30  0000 C CNN
	1    5750 2850
	0    1    1    0   
$EndComp
Wire Wire Line
	5600 2850 5350 2850
Wire Wire Line
	5900 2850 6150 2850
$Comp
L R R25
U 1 1 55E48DE0
P 5750 4100
F 0 "R25" V 5830 4100 50  0000 C CNN
F 1 "1k" V 5750 4100 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 5680 4100 30  0001 C CNN
F 3 "" H 5750 4100 30  0000 C CNN
	1    5750 4100
	0    -1   1    0   
$EndComp
Wire Wire Line
	5350 4100 5600 4100
Wire Wire Line
	5900 4100 6150 4100
Wire Wire Line
	5350 2650 5600 2650
Wire Wire Line
	1900 1900 2400 1900
Wire Wire Line
	1900 1350 2400 1350
$Comp
L ATMEGA88PA-A IC1
U 1 1 55E6535B
P 4350 3750
F 0 "IC1" H 3600 5000 40  0000 L BNN
F 1 "ATMEGA88PA-A" H 4750 2350 40  0000 L BNN
F 2 "Housings_QFP:TQFP-32_7x7mm_Pitch0.8mm" H 4350 3750 30  0000 C CIN
F 3 "" H 4350 3750 60  0000 C CNN
	1    4350 3750
	1    0    0    -1  
$EndComp
Wire Wire Line
	3450 4750 3350 4750
Connection ~ 3350 4850
Wire Wire Line
	3450 4950 3350 4950
Connection ~ 3350 4950
$Comp
L C C3
U 1 1 55E66953
P 2400 1650
F 0 "C3" H 2425 1750 50  0000 L CNN
F 1 "100nF" H 2425 1550 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603_HandSoldering" H 2438 1500 30  0001 C CNN
F 3 "" H 2400 1650 60  0000 C CNN
	1    2400 1650
	1    0    0    -1  
$EndComp
Wire Wire Line
	2400 1350 2400 1500
Wire Wire Line
	2400 1900 2400 1800
$Comp
L C_Small C6
U 1 1 55E683A7
P 7400 3150
F 0 "C6" H 7410 3220 50  0000 L CNN
F 1 "8pF" H 7410 3070 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 7400 3150 60  0001 C CNN
F 3 "" H 7400 3150 60  0000 C CNN
	1    7400 3150
	1    0    0    -1  
$EndComp
$Comp
L C_Small C7
U 1 1 55E684F6
P 7400 3450
F 0 "C7" H 7410 3520 50  0000 L CNN
F 1 "8pF" H 7410 3370 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 7400 3450 60  0001 C CNN
F 3 "" H 7400 3450 60  0000 C CNN
	1    7400 3450
	1    0    0    -1  
$EndComp
Wire Wire Line
	7400 3250 7400 3350
Wire Wire Line
	5350 3250 6950 3250
Wire Wire Line
	5350 3350 6950 3350
Wire Wire Line
	5900 2650 6150 2650
$Comp
L GND #PWR010
U 1 1 55E78AA9
P 7500 3800
F 0 "#PWR010" H 7500 3550 50  0001 C CNN
F 1 "GND" H 7500 3650 50  0000 C CNN
F 2 "" H 7500 3800 60  0000 C CNN
F 3 "" H 7500 3800 60  0000 C CNN
	1    7500 3800
	1    0    0    -1  
$EndComp
NoConn ~ 3450 4000
Wire Wire Line
	6150 4450 5350 4450
Wire Wire Line
	5350 4250 6150 4250
Wire Wire Line
	5350 4750 6150 4750
Wire Wire Line
	6150 4950 5350 4950
Wire Wire Line
	5350 4350 6150 4350
Wire Wire Line
	6150 4650 5350 4650
Wire Wire Line
	6150 3600 5350 3600
Wire Wire Line
	5350 3700 6150 3700
Wire Wire Line
	6150 3800 5350 3800
Wire Wire Line
	5350 3900 6150 3900
Wire Wire Line
	6950 3000 7400 3000
Wire Wire Line
	7400 3000 7400 3050
Wire Wire Line
	6950 3600 7400 3600
Wire Wire Line
	7400 3600 7400 3550
Wire Wire Line
	6950 3250 6950 3000
Connection ~ 7150 3000
Wire Wire Line
	6950 3350 6950 3600
Connection ~ 7150 3600
$Comp
L Crystal_Small Y1
U 1 1 55E8E687
P 7150 3300
F 0 "Y1" H 7150 3400 50  0000 C CNN
F 1 "Crystal_Small" H 7150 3200 50  0000 C CNN
F 2 "w_crystal:crystal_smd_5x3.2mm" H 7150 3300 60  0001 C CNN
F 3 "" H 7150 3300 60  0000 C CNN
	1    7150 3300
	0    1    1    0   
$EndComp
Wire Wire Line
	7150 3600 7150 3400
Wire Wire Line
	7150 3200 7150 3000
NoConn ~ 5350 2750
NoConn ~ 5350 4000
$Comp
L L_Small L1
U 1 1 55F59237
P 3150 2800
F 0 "L1" H 3180 2840 50  0000 L CNN
F 1 "10µH" H 3180 2760 50  0000 L CNN
F 2 "w_smd_inductors:inductor_smd_0805" H 3150 2800 60  0001 C CNN
F 3 "" H 3150 2800 60  0000 C CNN
	1    3150 2800
	-1   0    0    1   
$EndComp
Wire Wire Line
	3450 2950 3150 2950
Wire Wire Line
	3150 2950 3150 2900
Wire Wire Line
	3150 2400 3150 2700
Wire Wire Line
	3450 2750 3300 2750
Wire Wire Line
	3300 2750 3300 2650
Wire Wire Line
	3300 2650 3150 2650
Connection ~ 3150 2650
Wire Wire Line
	3450 2650 3450 2550
Wire Wire Line
	3450 2550 3150 2550
Connection ~ 3150 2550
$Comp
L C C4
U 1 1 55F5AC66
P 2850 3450
F 0 "C4" H 2875 3550 50  0000 L CNN
F 1 "100nF" H 2875 3350 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603_HandSoldering" H 2888 3300 30  0001 C CNN
F 3 "" H 2850 3450 60  0000 C CNN
	1    2850 3450
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR011
U 1 1 55F5B2CC
P 2850 3650
F 0 "#PWR011" H 2850 3400 50  0001 C CNN
F 1 "GND" H 2850 3500 50  0000 C CNN
F 2 "" H 2850 3650 60  0000 C CNN
F 3 "" H 2850 3650 60  0000 C CNN
	1    2850 3650
	1    0    0    -1  
$EndComp
Wire Wire Line
	2850 3600 2850 3650
Wire Wire Line
	3450 3250 2850 3250
Wire Wire Line
	2850 3250 2850 3300
Wire Wire Line
	3100 4100 3450 4100
Wire Wire Line
	5350 3500 5600 3500
Wire Wire Line
	5900 3500 6900 3500
Wire Wire Line
	6900 3500 6900 3800
Wire Wire Line
	6900 3800 6950 3800
Wire Wire Line
	7350 3800 7500 3800
$EndSCHEMATC
