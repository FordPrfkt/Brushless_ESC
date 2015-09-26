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
Sheet 3 3
Title "Brushless ESC"
Date "2015-09-19"
Rev "1.0"
Comp "Daniel Walter"
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L IR2104 U2
U 1 1 55E2144F
P 3050 2100
F 0 "U2" H 3050 2350 50  0000 C CNN
F 1 "IR2104" H 3050 1750 50  0000 C CNN
F 2 "w_smd_dil:so-8" H 3050 2350 60  0001 C CNN
F 3 "" H 3050 2350 60  0000 C CNN
	1    3050 2100
	1    0    0    -1  
$EndComp
$Comp
L Q_NMOS_GSD Q1
U 1 1 55E21456
P 4450 1900
F 0 "Q1" H 4750 1950 50  0000 R CNN
F 1 "IRL7843" H 4950 1850 50  0000 R CNN
F 2 "w_smd_trans:d-pak" H 4650 2000 29  0001 C CNN
F 3 "" H 4450 1900 60  0000 C CNN
	1    4450 1900
	1    0    0    -1  
$EndComp
$Comp
L Q_NMOS_GSD Q2
U 1 1 55E2145D
P 4450 2500
F 0 "Q2" H 4750 2550 50  0000 R CNN
F 1 "IRL7843" H 4950 2450 50  0000 R CNN
F 2 "w_smd_trans:d-pak" H 4650 2600 29  0001 C CNN
F 3 "" H 4450 2500 60  0000 C CNN
	1    4450 2500
	1    0    0    -1  
$EndComp
$Comp
L C C11
U 1 1 55E21464
P 3600 1750
F 0 "C11" H 3625 1850 50  0000 L CNN
F 1 "220nF" H 3625 1650 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 3638 1600 30  0001 C CNN
F 3 "" H 3600 1750 60  0000 C CNN
	1    3600 1750
	1    0    0    -1  
$EndComp
$Comp
L R R5
U 1 1 55E2146B
P 4000 1900
F 0 "R5" V 4080 1900 50  0000 C CNN
F 1 "47R" V 4000 1900 50  0000 C CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 3930 1900 30  0001 C CNN
F 3 "" H 4000 1900 30  0000 C CNN
	1    4000 1900
	0    1    1    0   
$EndComp
$Comp
L R R7
U 1 1 55E21472
P 4000 2500
F 0 "R7" V 4080 2500 50  0000 C CNN
F 1 "47R" V 4000 2500 50  0000 C CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 3930 2500 30  0001 C CNN
F 3 "" H 4000 2500 30  0000 C CNN
	1    4000 2500
	0    1    1    0   
$EndComp
$Comp
L C C10
U 1 1 55E2149C
P 1500 3800
F 0 "C10" H 1525 3900 50  0000 L CNN
F 1 "100nF" H 1525 3700 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 1538 3650 30  0001 C CNN
F 3 "" H 1500 3800 60  0000 C CNN
	1    1500 3800
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR013
U 1 1 55E214A8
P 2600 2400
F 0 "#PWR013" H 2600 2150 50  0001 C CNN
F 1 "GND" H 2600 2250 50  0000 C CNN
F 2 "" H 2600 2400 60  0000 C CNN
F 3 "" H 2600 2400 60  0000 C CNN
	1    2600 2400
	1    0    0    -1  
$EndComp
$Comp
L R R6
U 1 1 55E214B0
P 2250 2000
F 0 "R6" V 2330 2000 50  0000 C CNN
F 1 "1k" V 2250 2000 50  0000 C CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 2180 2000 30  0001 C CNN
F 3 "" H 2250 2000 30  0000 C CNN
	1    2250 2000
	0    1    1    0   
$EndComp
Text GLabel 5200 2100 1    60   Output ~ 0
COIL_A
$Comp
L ZENER D4
U 1 1 55E214C1
P 3050 1500
F 0 "D4" H 3050 1600 50  0000 C CNN
F 1 "BAS21" H 3050 1400 50  0000 C CNN
F 2 "w_smd_diode:sod123" H 3050 1500 60  0001 C CNN
F 3 "" H 3050 1500 60  0000 C CNN
	1    3050 1500
	-1   0    0    -1  
$EndComp
$Comp
L C C9
U 1 1 55E214CA
P 1300 3800
F 0 "C9" H 1325 3900 50  0000 L CNN
F 1 "100nF" H 1325 3700 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 1338 3650 30  0001 C CNN
F 3 "" H 1300 3800 60  0000 C CNN
	1    1300 3800
	1    0    0    -1  
$EndComp
$Comp
L C C8
U 1 1 55E214D1
P 1100 3800
F 0 "C8" H 1125 3900 50  0000 L CNN
F 1 "100nF" H 1125 3700 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 1138 3650 30  0001 C CNN
F 3 "" H 1100 3800 60  0000 C CNN
	1    1100 3800
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR014
U 1 1 55E214D8
P 1300 4000
F 0 "#PWR014" H 1300 3750 50  0001 C CNN
F 1 "GND" H 1300 3850 50  0000 C CNN
F 2 "" H 1300 4000 60  0000 C CNN
F 3 "" H 1300 4000 60  0000 C CNN
	1    1300 4000
	1    0    0    -1  
$EndComp
$Comp
L IR2104 U3
U 1 1 55E214EE
P 7850 2150
F 0 "U3" H 7850 2400 50  0000 C CNN
F 1 "IR2104" H 7850 1800 50  0000 C CNN
F 2 "w_smd_dil:so-8" H 7850 2400 60  0001 C CNN
F 3 "" H 7850 2400 60  0000 C CNN
	1    7850 2150
	1    0    0    -1  
$EndComp
$Comp
L Q_NMOS_GSD Q3
U 1 1 55E214F5
P 9250 1950
F 0 "Q3" H 9550 2000 50  0000 R CNN
F 1 "IRL7843" H 9750 1900 50  0000 R CNN
F 2 "w_smd_trans:d-pak" H 9450 2050 29  0001 C CNN
F 3 "" H 9250 1950 60  0000 C CNN
	1    9250 1950
	1    0    0    -1  
$EndComp
$Comp
L Q_NMOS_GSD Q4
U 1 1 55E214FC
P 9250 2550
F 0 "Q4" H 9550 2600 50  0000 R CNN
F 1 "IRL7843" H 9750 2500 50  0000 R CNN
F 2 "w_smd_trans:d-pak" H 9450 2650 29  0001 C CNN
F 3 "" H 9250 2550 60  0000 C CNN
	1    9250 2550
	1    0    0    -1  
$EndComp
$Comp
L C C12
U 1 1 55E21503
P 8400 1800
F 0 "C12" H 8425 1900 50  0000 L CNN
F 1 "220nF" H 8425 1700 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 8438 1650 30  0001 C CNN
F 3 "" H 8400 1800 60  0000 C CNN
	1    8400 1800
	1    0    0    -1  
$EndComp
$Comp
L R R8
U 1 1 55E2150A
P 8800 1950
F 0 "R8" V 8880 1950 50  0000 C CNN
F 1 "47R" V 8800 1950 50  0000 C CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 8730 1950 30  0001 C CNN
F 3 "" H 8800 1950 30  0000 C CNN
	1    8800 1950
	0    1    1    0   
$EndComp
$Comp
L R R16
U 1 1 55E21511
P 8800 2550
F 0 "R16" V 8880 2550 50  0000 C CNN
F 1 "47R" V 8800 2550 50  0000 C CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 8730 2550 30  0001 C CNN
F 3 "" H 8800 2550 30  0000 C CNN
	1    8800 2550
	0    1    1    0   
$EndComp
$Comp
L GND #PWR015
U 1 1 55E21540
P 7400 2450
F 0 "#PWR015" H 7400 2200 50  0001 C CNN
F 1 "GND" H 7400 2300 50  0000 C CNN
F 2 "" H 7400 2450 60  0000 C CNN
F 3 "" H 7400 2450 60  0000 C CNN
	1    7400 2450
	1    0    0    -1  
$EndComp
$Comp
L R R11
U 1 1 55E21548
P 7050 2050
F 0 "R11" V 7130 2050 50  0000 C CNN
F 1 "1k" V 7050 2050 50  0000 C CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 6980 2050 30  0001 C CNN
F 3 "" H 7050 2050 30  0000 C CNN
	1    7050 2050
	0    1    1    0   
$EndComp
Text GLabel 10000 2150 1    60   Output ~ 0
COIL_B
$Comp
L ZENER D5
U 1 1 55E21559
P 7850 1550
F 0 "D5" H 7850 1650 50  0000 C CNN
F 1 "BAS21" H 7850 1450 50  0000 C CNN
F 2 "w_smd_diode:sod123" H 7850 1550 60  0001 C CNN
F 3 "" H 7850 1550 60  0000 C CNN
	1    7850 1550
	-1   0    0    -1  
$EndComp
$Comp
L IR2104 U4
U 1 1 55E21562
P 7850 4250
F 0 "U4" H 7850 4500 50  0000 C CNN
F 1 "IR2104" H 7850 3900 50  0000 C CNN
F 2 "w_smd_dil:so-8" H 7850 4500 60  0001 C CNN
F 3 "" H 7850 4500 60  0000 C CNN
	1    7850 4250
	1    0    0    -1  
$EndComp
$Comp
L Q_NMOS_GSD Q5
U 1 1 55E21569
P 9250 4050
F 0 "Q5" H 9550 4100 50  0000 R CNN
F 1 "IRL7843" H 9750 4000 50  0000 R CNN
F 2 "w_smd_trans:d-pak" H 9450 4150 29  0001 C CNN
F 3 "" H 9250 4050 60  0000 C CNN
	1    9250 4050
	1    0    0    -1  
$EndComp
$Comp
L Q_NMOS_GSD Q6
U 1 1 55E21570
P 9250 4650
F 0 "Q6" H 9550 4700 50  0000 R CNN
F 1 "IRL7843" H 9750 4600 50  0000 R CNN
F 2 "w_smd_trans:d-pak" H 9450 4750 29  0001 C CNN
F 3 "" H 9250 4650 60  0000 C CNN
	1    9250 4650
	1    0    0    -1  
$EndComp
$Comp
L C C16
U 1 1 55E21577
P 8400 3900
F 0 "C16" H 8425 4000 50  0000 L CNN
F 1 "220nF" H 8425 3800 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 8438 3750 30  0001 C CNN
F 3 "" H 8400 3900 60  0000 C CNN
	1    8400 3900
	1    0    0    -1  
$EndComp
$Comp
L R R20
U 1 1 55E2157E
P 8800 4050
F 0 "R20" V 8880 4050 50  0000 C CNN
F 1 "47R" V 8800 4050 50  0000 C CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 8730 4050 30  0001 C CNN
F 3 "" H 8800 4050 30  0000 C CNN
	1    8800 4050
	0    1    1    0   
$EndComp
$Comp
L R R24
U 1 1 55E21585
P 8800 4650
F 0 "R24" V 8880 4650 50  0000 C CNN
F 1 "47R" V 8800 4650 50  0000 C CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 8730 4650 30  0001 C CNN
F 3 "" H 8800 4650 30  0000 C CNN
	1    8800 4650
	0    1    1    0   
$EndComp
$Comp
L GND #PWR016
U 1 1 55E215B4
P 7400 4550
F 0 "#PWR016" H 7400 4300 50  0001 C CNN
F 1 "GND" H 7400 4400 50  0000 C CNN
F 2 "" H 7400 4550 60  0000 C CNN
F 3 "" H 7400 4550 60  0000 C CNN
	1    7400 4550
	1    0    0    -1  
$EndComp
$Comp
L R R21
U 1 1 55E215BC
P 7050 4150
F 0 "R21" V 7130 4150 50  0000 C CNN
F 1 "1k" V 7050 4150 50  0000 C CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 6980 4150 30  0001 C CNN
F 3 "" H 7050 4150 30  0000 C CNN
	1    7050 4150
	0    1    1    0   
$EndComp
Text GLabel 10000 4250 1    60   Output ~ 0
COIL_C
$Comp
L ZENER D6
U 1 1 55E215CD
P 7850 3650
F 0 "D6" H 7850 3750 50  0000 C CNN
F 1 "BAS21" H 7850 3550 50  0000 C CNN
F 2 "w_smd_diode:sod123" H 7850 3650 60  0001 C CNN
F 3 "" H 7850 3650 60  0000 C CNN
	1    7850 3650
	-1   0    0    -1  
$EndComp
Text HLabel 2000 2000 0    60   Input ~ 0
PWM
Text HLabel 2000 2100 0    60   Input ~ 0
IN_A
Text HLabel 2000 2200 0    60   Input ~ 0
/SD_A
Text HLabel 6800 2050 0    60   Input ~ 0
PWM
Text HLabel 6800 2150 0    60   Input ~ 0
IN_B
Text HLabel 6800 2250 0    60   Input ~ 0
/SD_B
Text HLabel 6800 4150 0    60   Input ~ 0
PWM
Text HLabel 6800 4250 0    60   Input ~ 0
IN_C
Text HLabel 6800 4350 0    60   Input ~ 0
/SD_C
$Comp
L R R4
U 1 1 55E22A6F
P 3400 5150
F 0 "R4" V 3480 5150 50  0000 C CNN
F 1 "0R02/5W" V 3300 5150 50  0000 C CNN
F 2 "Resistors_SMD:R_2512_HandSoldering" V 3330 5150 30  0001 C CNN
F 3 "" H 3400 5150 30  0000 C CNN
	1    3400 5150
	-1   0    0    1   
$EndComp
Text HLabel 2650 4900 0    60   Output ~ 0
BatCurrent+
$Comp
L R R9
U 1 1 55E25EB2
P 1400 6550
F 0 "R9" V 1480 6550 50  0000 C CNN
F 1 "4k7" V 1400 6550 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 1330 6550 30  0001 C CNN
F 3 "" H 1400 6550 30  0000 C CNN
	1    1400 6550
	0    1    1    0   
$EndComp
$Comp
L R R12
U 1 1 55E25F9D
P 1400 6750
F 0 "R12" V 1480 6750 50  0000 C CNN
F 1 "4k7" V 1400 6750 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 1330 6750 30  0001 C CNN
F 3 "" H 1400 6750 30  0000 C CNN
	1    1400 6750
	0    1    1    0   
$EndComp
$Comp
L R R14
U 1 1 55E26013
P 1400 6950
F 0 "R14" V 1480 6950 50  0000 C CNN
F 1 "4k7" V 1400 6950 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 1330 6950 30  0001 C CNN
F 3 "" H 1400 6950 30  0000 C CNN
	1    1400 6950
	0    1    1    0   
$EndComp
$Comp
L R R17
U 1 1 55E2608C
P 1800 7200
F 0 "R17" V 1880 7200 50  0000 C CNN
F 1 "4k7" V 1800 7200 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 1730 7200 30  0001 C CNN
F 3 "" H 1800 7200 30  0000 C CNN
	1    1800 7200
	-1   0    0    1   
$EndComp
$Comp
L R R18
U 1 1 55E26348
P 2250 7200
F 0 "R18" V 2330 7200 50  0000 C CNN
F 1 "4k7" V 2250 7200 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 2180 7200 30  0001 C CNN
F 3 "" H 2250 7200 30  0000 C CNN
	1    2250 7200
	-1   0    0    1   
$EndComp
$Comp
L R R19
U 1 1 55E263BF
P 2700 7200
F 0 "R19" V 2780 7200 50  0000 C CNN
F 1 "4k7" V 2700 7200 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 2630 7200 30  0001 C CNN
F 3 "" H 2700 7200 30  0000 C CNN
	1    2700 7200
	-1   0    0    1   
$EndComp
$Comp
L C C13
U 1 1 55E2665D
P 2000 7200
F 0 "C13" H 2025 7300 50  0000 L CNN
F 1 "100nF" H 2025 7100 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 2038 7050 30  0001 C CNN
F 3 "" H 2000 7200 60  0000 C CNN
	1    2000 7200
	1    0    0    -1  
$EndComp
$Comp
L C C14
U 1 1 55E26872
P 2450 7200
F 0 "C14" H 2475 7300 50  0000 L CNN
F 1 "100nF" H 2475 7100 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 2488 7050 30  0001 C CNN
F 3 "" H 2450 7200 60  0000 C CNN
	1    2450 7200
	1    0    0    -1  
$EndComp
$Comp
L C C15
U 1 1 55E26906
P 2900 7200
F 0 "C15" H 2925 7300 50  0000 L CNN
F 1 "100nF" H 2925 7100 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 2938 7050 30  0001 C CNN
F 3 "" H 2900 7200 60  0000 C CNN
	1    2900 7200
	1    0    0    -1  
$EndComp
$Comp
L R R15
U 1 1 55E26E64
P 3300 6950
F 0 "R15" V 3380 6950 50  0000 C CNN
F 1 "4k7" V 3300 6950 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 3230 6950 30  0001 C CNN
F 3 "" H 3300 6950 30  0000 C CNN
	1    3300 6950
	0    1    1    0   
$EndComp
$Comp
L R R13
U 1 1 55E26F22
P 3300 6750
F 0 "R13" V 3380 6750 50  0000 C CNN
F 1 "4k7" V 3300 6750 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 3230 6750 30  0001 C CNN
F 3 "" H 3300 6750 30  0000 C CNN
	1    3300 6750
	0    1    1    0   
$EndComp
$Comp
L R R10
U 1 1 55E26FAF
P 3300 6550
F 0 "R10" V 3380 6550 50  0000 C CNN
F 1 "4k7" V 3300 6550 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 3230 6550 30  0001 C CNN
F 3 "" H 3300 6550 30  0000 C CNN
	1    3300 6550
	0    1    1    0   
$EndComp
$Comp
L GND #PWR017
U 1 1 55E281A6
P 2350 7500
F 0 "#PWR017" H 2350 7250 50  0001 C CNN
F 1 "GND" H 2350 7350 50  0000 C CNN
F 2 "" H 2350 7500 60  0000 C CNN
F 3 "" H 2350 7500 60  0000 C CNN
	1    2350 7500
	1    0    0    -1  
$EndComp
Text HLabel 3850 6750 2    60   Output ~ 0
BEMF_Center
Text HLabel 2050 5950 2    60   Output ~ 0
BEMF_A
Text HLabel 2500 6100 2    60   Output ~ 0
BEMF_B
Text HLabel 2950 6300 2    60   Output ~ 0
BEMF_C
Wire Wire Line
	3450 2100 3700 2100
Wire Wire Line
	3700 2100 3700 1900
Wire Wire Line
	3700 1900 3850 1900
Wire Wire Line
	3450 2300 3700 2300
Wire Wire Line
	3700 2300 3700 2500
Wire Wire Line
	3700 2500 3850 2500
Wire Wire Line
	3450 2200 5300 2200
Wire Wire Line
	4550 2100 4550 2300
Connection ~ 4550 2200
Wire Wire Line
	4150 1900 4250 1900
Wire Wire Line
	4150 2500 4250 2500
Connection ~ 3600 2200
Wire Wire Line
	3600 2200 3600 1900
Wire Wire Line
	3600 1500 3600 1600
Wire Wire Line
	3450 2000 3450 1600
Wire Wire Line
	3450 1600 3600 1600
Connection ~ 3600 1600
Wire Wire Line
	2600 1400 2600 2000
Wire Wire Line
	2600 2000 2650 2000
Connection ~ 2600 1500
Wire Wire Line
	4550 2700 4550 2800
Wire Wire Line
	2650 2300 2600 2300
Wire Wire Line
	2600 2300 2600 2400
Wire Wire Line
	2000 2100 2650 2100
Wire Wire Line
	2400 2000 2500 2000
Wire Wire Line
	2500 2000 2500 2100
Connection ~ 2500 2100
Wire Wire Line
	2650 2200 2000 2200
Wire Wire Line
	2100 2000 2000 2000
Wire Wire Line
	2600 1500 2850 1500
Wire Wire Line
	3250 1500 3600 1500
Wire Wire Line
	1100 3600 1500 3600
Wire Wire Line
	1100 3600 1100 3650
Wire Wire Line
	1500 3600 1500 3650
Connection ~ 1300 3600
Wire Wire Line
	1300 3500 1300 3650
Wire Wire Line
	1100 4000 1500 4000
Wire Wire Line
	1100 4000 1100 3950
Wire Wire Line
	1500 4000 1500 3950
Connection ~ 1300 4000
Wire Wire Line
	1300 4000 1300 3950
Wire Wire Line
	8250 2150 8500 2150
Wire Wire Line
	8500 2150 8500 1950
Wire Wire Line
	8500 1950 8650 1950
Wire Wire Line
	8250 2350 8500 2350
Wire Wire Line
	8500 2350 8500 2550
Wire Wire Line
	8500 2550 8650 2550
Wire Wire Line
	8250 2250 10100 2250
Wire Wire Line
	9350 2150 9350 2350
Connection ~ 9350 2250
Wire Wire Line
	8950 1950 9050 1950
Wire Wire Line
	8950 2550 9050 2550
Connection ~ 8400 2250
Wire Wire Line
	8400 2250 8400 1950
Wire Wire Line
	8400 1550 8400 1650
Wire Wire Line
	8250 2050 8250 1650
Wire Wire Line
	8250 1650 8400 1650
Connection ~ 8400 1650
Wire Wire Line
	7400 1450 7400 2050
Wire Wire Line
	7400 2050 7450 2050
Connection ~ 7400 1550
Wire Wire Line
	9350 2750 9350 2850
Wire Wire Line
	7450 2350 7400 2350
Wire Wire Line
	7400 2350 7400 2450
Wire Wire Line
	6800 2150 7450 2150
Wire Wire Line
	7200 2050 7300 2050
Wire Wire Line
	7300 2050 7300 2150
Connection ~ 7300 2150
Wire Wire Line
	7450 2250 6800 2250
Wire Wire Line
	6900 2050 6800 2050
Wire Wire Line
	7400 1550 7650 1550
Wire Wire Line
	8050 1550 8400 1550
Wire Wire Line
	8250 4250 8500 4250
Wire Wire Line
	8500 4250 8500 4050
Wire Wire Line
	8500 4050 8650 4050
Wire Wire Line
	8250 4450 8500 4450
Wire Wire Line
	8500 4450 8500 4650
Wire Wire Line
	8500 4650 8650 4650
Wire Wire Line
	8250 4350 10100 4350
Wire Wire Line
	9350 4250 9350 4450
Connection ~ 9350 4350
Wire Wire Line
	8950 4050 9050 4050
Wire Wire Line
	8950 4650 9050 4650
Connection ~ 8400 4350
Wire Wire Line
	8400 4350 8400 4050
Wire Wire Line
	8400 3650 8400 3750
Wire Wire Line
	8250 4150 8250 3750
Wire Wire Line
	8250 3750 8400 3750
Connection ~ 8400 3750
Wire Wire Line
	7400 3550 7400 4150
Wire Wire Line
	7400 4150 7450 4150
Connection ~ 7400 3650
Wire Wire Line
	9350 4850 9350 4950
Wire Wire Line
	7450 4450 7400 4450
Wire Wire Line
	7400 4450 7400 4550
Wire Wire Line
	6800 4250 7450 4250
Wire Wire Line
	7200 4150 7300 4150
Wire Wire Line
	7300 4150 7300 4250
Connection ~ 7300 4250
Wire Wire Line
	7450 4350 6800 4350
Wire Wire Line
	6900 4150 6800 4150
Wire Wire Line
	7400 3650 7650 3650
Wire Wire Line
	8050 3650 8400 3650
Wire Wire Line
	9350 3850 9350 3800
Wire Wire Line
	9350 1750 9350 1700
Wire Wire Line
	4550 1700 4550 1600
Wire Wire Line
	1550 6950 3150 6950
Wire Wire Line
	3150 6750 1550 6750
Wire Wire Line
	1550 6550 3150 6550
Wire Wire Line
	1800 7050 1800 6550
Connection ~ 1800 6550
Wire Wire Line
	2000 5950 2000 7050
Connection ~ 2000 6550
Wire Wire Line
	2250 7050 2250 6750
Connection ~ 2250 6750
Wire Wire Line
	2450 6100 2450 7050
Connection ~ 2450 6750
Wire Wire Line
	2700 7050 2700 6950
Connection ~ 2700 6950
Wire Wire Line
	2900 6300 2900 7050
Connection ~ 2900 6950
Wire Wire Line
	3450 6750 3850 6750
Wire Wire Line
	3600 6950 3450 6950
Wire Wire Line
	3600 6550 3600 6950
Connection ~ 3600 6750
Wire Wire Line
	3450 6550 3600 6550
Wire Wire Line
	1800 7350 1800 7450
Wire Wire Line
	1800 7450 2900 7450
Wire Wire Line
	2350 7450 2350 7500
Wire Wire Line
	2900 7450 2900 7350
Connection ~ 2350 7450
Wire Wire Line
	2000 7350 2000 7450
Connection ~ 2000 7450
Wire Wire Line
	2250 7350 2250 7450
Connection ~ 2250 7450
Wire Wire Line
	2450 7350 2450 7450
Connection ~ 2450 7450
Wire Wire Line
	2700 7350 2700 7450
Connection ~ 2700 7450
Wire Wire Line
	2000 5950 2050 5950
Wire Wire Line
	2450 6100 2500 6100
Wire Wire Line
	2900 6300 2950 6300
Text GLabel 1150 6550 0    60   Input ~ 0
COIL_A
Text GLabel 1150 6750 0    60   Input ~ 0
COIL_B
Text GLabel 1150 6950 0    60   Input ~ 0
COIL_C
Wire Wire Line
	1150 6550 1250 6550
Wire Wire Line
	1150 6750 1250 6750
Wire Wire Line
	1150 6950 1250 6950
$Comp
L R R22
U 1 1 55E2B384
P 1600 4750
F 0 "R22" V 1680 4750 50  0000 C CNN
F 1 "1k5" V 1600 4750 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 1530 4750 30  0001 C CNN
F 3 "" H 1600 4750 30  0000 C CNN
	1    1600 4750
	-1   0    0    1   
$EndComp
$Comp
L R R23
U 1 1 55E2B447
P 1600 5150
F 0 "R23" V 1680 5150 50  0000 C CNN
F 1 "470R" V 1600 5150 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 1530 5150 30  0001 C CNN
F 3 "" H 1600 5150 30  0000 C CNN
	1    1600 5150
	-1   0    0    1   
$EndComp
$Comp
L +BATT #PWR018
U 1 1 55E2BB71
P 1600 4450
F 0 "#PWR018" H 1600 4300 50  0001 C CNN
F 1 "+BATT" H 1600 4590 50  0000 C CNN
F 2 "" H 1600 4450 60  0000 C CNN
F 3 "" H 1600 4450 60  0000 C CNN
	1    1600 4450
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR019
U 1 1 55E2C4AC
P 1600 5400
F 0 "#PWR019" H 1600 5150 50  0001 C CNN
F 1 "GND" H 1600 5250 50  0000 C CNN
F 2 "" H 1600 5400 60  0000 C CNN
F 3 "" H 1600 5400 60  0000 C CNN
	1    1600 5400
	1    0    0    -1  
$EndComp
Wire Wire Line
	1600 5400 1600 5300
Text HLabel 1000 4950 0    60   Output ~ 0
V_Bat
Wire Wire Line
	10000 4250 10000 4350
Connection ~ 10000 4350
Wire Wire Line
	10000 2150 10000 2250
Connection ~ 10000 2250
Wire Wire Line
	5200 2100 5200 2200
Connection ~ 5200 2200
Text HLabel 5300 2200 2    60   Output ~ 0
Coil_A
Text HLabel 10100 2250 2    60   Output ~ 0
Coil_B
Text HLabel 10100 4350 2    60   Output ~ 0
Coil_C
$Comp
L C C17
U 1 1 55E30B53
P 1100 5150
F 0 "C17" H 1125 5250 50  0000 L CNN
F 1 "100nF" H 1125 5050 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 1138 5000 30  0001 C CNN
F 3 "" H 1100 5150 60  0000 C CNN
	1    1100 5150
	1    0    0    -1  
$EndComp
$Comp
L C C18
U 1 1 55E30F1D
P 2850 5150
F 0 "C18" H 2875 5250 50  0000 L CNN
F 1 "100nF" H 2875 5050 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 2888 5000 30  0001 C CNN
F 3 "" H 2850 5150 60  0000 C CNN
	1    2850 5150
	1    0    0    -1  
$EndComp
Wire Wire Line
	1100 5300 1100 5400
Wire Wire Line
	1100 5400 1600 5400
Text GLabel 9350 2850 3    60   Output ~ 0
FET_Drain
Text GLabel 9350 4950 3    60   Output ~ 0
FET_Drain
Text GLabel 4550 2800 3    60   Output ~ 0
FET_Drain
Text GLabel 3400 4850 1    60   Input ~ 0
FET_Drain
$Comp
L R R3
U 1 1 55E6F669
P 3150 4900
F 0 "R3" V 3230 4900 50  0000 C CNN
F 1 "680R" V 3150 4900 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 3080 4900 30  0001 C CNN
F 3 "" H 3150 4900 30  0000 C CNN
	1    3150 4900
	0    1    1    0   
$EndComp
Wire Wire Line
	3400 4850 3400 5000
Wire Wire Line
	3400 5300 3400 5450
Wire Wire Line
	3300 4900 3400 4900
Connection ~ 3400 4900
Wire Wire Line
	3000 4900 2650 4900
Wire Wire Line
	2850 5000 2850 4900
Connection ~ 2850 4900
Wire Wire Line
	2850 5300 2850 5400
Wire Wire Line
	2850 5400 3400 5400
Connection ~ 3400 5400
$Comp
L +BATT #PWR020
U 1 1 55E71CB1
P 1300 3500
F 0 "#PWR020" H 1300 3350 50  0001 C CNN
F 1 "+BATT" H 1300 3640 50  0000 C CNN
F 2 "" H 1300 3500 60  0000 C CNN
F 3 "" H 1300 3500 60  0000 C CNN
	1    1300 3500
	1    0    0    -1  
$EndComp
$Comp
L +BATT #PWR021
U 1 1 55E7214E
P 2600 1400
F 0 "#PWR021" H 2600 1250 50  0001 C CNN
F 1 "+BATT" H 2600 1540 50  0000 C CNN
F 2 "" H 2600 1400 60  0000 C CNN
F 3 "" H 2600 1400 60  0000 C CNN
	1    2600 1400
	1    0    0    -1  
$EndComp
$Comp
L +BATT #PWR022
U 1 1 55E721E0
P 4550 1600
F 0 "#PWR022" H 4550 1450 50  0001 C CNN
F 1 "+BATT" H 4550 1740 50  0000 C CNN
F 2 "" H 4550 1600 60  0000 C CNN
F 3 "" H 4550 1600 60  0000 C CNN
	1    4550 1600
	1    0    0    -1  
$EndComp
$Comp
L +BATT #PWR023
U 1 1 55E72984
P 7400 1450
F 0 "#PWR023" H 7400 1300 50  0001 C CNN
F 1 "+BATT" H 7400 1590 50  0000 C CNN
F 2 "" H 7400 1450 60  0000 C CNN
F 3 "" H 7400 1450 60  0000 C CNN
	1    7400 1450
	1    0    0    -1  
$EndComp
$Comp
L +BATT #PWR024
U 1 1 55E72DC7
P 9350 1700
F 0 "#PWR024" H 9350 1550 50  0001 C CNN
F 1 "+BATT" H 9350 1840 50  0000 C CNN
F 2 "" H 9350 1700 60  0000 C CNN
F 3 "" H 9350 1700 60  0000 C CNN
	1    9350 1700
	1    0    0    -1  
$EndComp
$Comp
L +BATT #PWR025
U 1 1 55E73237
P 7400 3550
F 0 "#PWR025" H 7400 3400 50  0001 C CNN
F 1 "+BATT" H 7400 3690 50  0000 C CNN
F 2 "" H 7400 3550 60  0000 C CNN
F 3 "" H 7400 3550 60  0000 C CNN
	1    7400 3550
	1    0    0    -1  
$EndComp
$Comp
L +BATT #PWR026
U 1 1 55E7367A
P 9350 3800
F 0 "#PWR026" H 9350 3650 50  0001 C CNN
F 1 "+BATT" H 9350 3940 50  0000 C CNN
F 2 "" H 9350 3800 60  0000 C CNN
F 3 "" H 9350 3800 60  0000 C CNN
	1    9350 3800
	1    0    0    -1  
$EndComp
$Comp
L CP C19
U 1 1 55F75B8B
P 2450 3750
F 0 "C19" H 2475 3850 50  0000 L CNN
F 1 "1000µF" H 2475 3650 50  0000 L CNN
F 2 "Capacitors_Elko_ThroughHole:Elko_vert_20x10mm_RM5" H 2488 3600 30  0001 C CNN
F 3 "" H 2450 3750 60  0000 C CNN
	1    2450 3750
	1    0    0    -1  
$EndComp
$Comp
L +BATT #PWR027
U 1 1 55F75C30
P 2450 3450
F 0 "#PWR027" H 2450 3300 50  0001 C CNN
F 1 "+BATT" H 2450 3590 50  0000 C CNN
F 2 "" H 2450 3450 60  0000 C CNN
F 3 "" H 2450 3450 60  0000 C CNN
	1    2450 3450
	1    0    0    -1  
$EndComp
Wire Wire Line
	2450 3600 2450 3450
Wire Wire Line
	2450 3900 2450 4000
$Comp
L GND #PWR028
U 1 1 55F7A203
P 2450 4000
F 0 "#PWR028" H 2450 3750 50  0001 C CNN
F 1 "GND" H 2450 3850 50  0000 C CNN
F 2 "" H 2450 4000 60  0000 C CNN
F 3 "" H 2450 4000 60  0000 C CNN
	1    2450 4000
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR029
U 1 1 55F7A37F
P 3400 5450
F 0 "#PWR029" H 3400 5200 50  0001 C CNN
F 1 "GND" H 3400 5300 50  0000 C CNN
F 2 "" H 3400 5450 60  0000 C CNN
F 3 "" H 3400 5450 60  0000 C CNN
	1    3400 5450
	1    0    0    -1  
$EndComp
Wire Wire Line
	1100 5000 1100 4950
Wire Wire Line
	1000 4950 1600 4950
Wire Wire Line
	1600 4900 1600 5000
Connection ~ 1600 4950
Connection ~ 1100 4950
Wire Wire Line
	1600 4600 1600 4450
$EndSCHEMATC
