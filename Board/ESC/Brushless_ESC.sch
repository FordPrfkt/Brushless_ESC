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
Sheet 1 3
Title "Brushless ESC"
Date "2015-09-19"
Rev "1.0"
Comp "Daniel Walter"
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Sheet
S 2700 2100 1950 1950
U 55E20B14
F0 "Controller" 60
F1 "Controller.sch" 60
F2 "PWM" O R 4650 2200 60 
F3 "V_Bat" I R 4650 3800 60 
F4 "BEMF_A" I R 4650 3450 60 
F5 "BEMF_B" I R 4650 3550 60 
F6 "BEMF_C" I R 4650 3650 60 
F7 "BEMF_Center" I R 4650 3350 60 
F8 "SS" I L 2700 2750 60 
F9 "MISO" I L 2700 2950 60 
F10 "MOSI" I L 2700 2850 60 
F11 "SCK" I L 2700 3150 60 
F12 "BatCurrent+" I R 4650 3100 60 
F13 "IN_A" O R 4650 2350 60 
F14 "IN_B" O R 4650 2600 60 
F15 "IN_C" O R 4650 2850 60 
F16 "/SD_A" O R 4650 2450 60 
F17 "/SD_B" O R 4650 2700 60 
F18 "/SD_C" O R 4650 2950 60 
F19 "PPM" I L 2700 2650 60 
F20 "Reset" I L 2700 3050 60 
F21 "T_Sense" I R 4650 3200 60 
$EndSheet
$Sheet
S 6750 2100 1700 1900
U 55E20B33
F0 "Power" 60
F1 "Power.sch" 60
F2 "PWM" I L 6750 2200 60 
F3 "IN_A" I L 6750 2350 60 
F4 "/SD_A" I L 6750 2450 60 
F5 "IN_B" I L 6750 2600 60 
F6 "/SD_B" I L 6750 2700 60 
F7 "IN_C" I L 6750 2850 60 
F8 "/SD_C" I L 6750 2950 60 
F9 "BEMF_Center" O L 6750 3350 60 
F10 "BEMF_A" O L 6750 3450 60 
F11 "BEMF_B" O L 6750 3550 60 
F12 "BEMF_C" O L 6750 3650 60 
F13 "V_Bat" O L 6750 3800 60 
F14 "Coil_A" O R 8450 2550 60 
F15 "Coil_B" O R 8450 3100 60 
F16 "Coil_C" O R 8450 3650 60 
F17 "BatCurrent+" O L 6750 3100 60 
F18 "T_Sense" O L 6750 3200 60 
$EndSheet
$Comp
L CONN_01X01 P1
U 1 1 55E32B03
P 2000 1400
F 0 "P1" H 2000 1500 50  0000 C CNN
F 1 "Battery+" V 2100 1400 50  0000 C CNN
F 2 "Wire_Pads:SolderWirePad_single_2mmDrill" H 2000 1400 60  0001 C CNN
F 3 "" H 2000 1400 60  0000 C CNN
	1    2000 1400
	-1   0    0    1   
$EndComp
$Comp
L CONN_01X01 P3
U 1 1 55E32C83
P 9250 2550
F 0 "P3" H 9250 2650 50  0000 C CNN
F 1 "Coil_A" V 9350 2550 50  0000 C CNN
F 2 "Wire_Pads:SolderWirePad_single_2mmDrill" H 9250 2550 60  0001 C CNN
F 3 "" H 9250 2550 60  0000 C CNN
	1    9250 2550
	1    0    0    1   
$EndComp
$Comp
L CONN_01X01 P5
U 1 1 55E3308D
P 9250 3100
F 0 "P5" H 9250 3200 50  0000 C CNN
F 1 "Coil_B" V 9350 3100 50  0000 C CNN
F 2 "Wire_Pads:SolderWirePad_single_2mmDrill" H 9250 3100 60  0001 C CNN
F 3 "" H 9250 3100 60  0000 C CNN
	1    9250 3100
	1    0    0    1   
$EndComp
$Comp
L CONN_01X01 P6
U 1 1 55E331C2
P 9250 3650
F 0 "P6" H 9250 3750 50  0000 C CNN
F 1 "Coil_C" V 9350 3650 50  0000 C CNN
F 2 "Wire_Pads:SolderWirePad_single_2mmDrill" H 9250 3650 60  0001 C CNN
F 3 "" H 9250 3650 60  0000 C CNN
	1    9250 3650
	1    0    0    1   
$EndComp
$Comp
L CONN_01X01 P2
U 1 1 55E33584
P 2000 1800
F 0 "P2" H 2000 1900 50  0000 C CNN
F 1 "Battery-" V 2100 1800 50  0000 C CNN
F 2 "Wire_Pads:SolderWirePad_single_2mmDrill" H 2000 1800 60  0001 C CNN
F 3 "" H 2000 1800 60  0000 C CNN
	1    2000 1800
	-1   0    0    1   
$EndComp
Wire Wire Line
	2200 1800 2250 1800
Wire Wire Line
	2250 1800 2250 1900
$Comp
L +BATT #PWR01
U 1 1 55E34918
P 2300 1300
F 0 "#PWR01" H 2300 1150 50  0001 C CNN
F 1 "+BATT" H 2300 1440 50  0000 C CNN
F 2 "" H 2300 1300 60  0000 C CNN
F 3 "" H 2300 1300 60  0000 C CNN
	1    2300 1300
	1    0    0    -1  
$EndComp
Wire Wire Line
	2200 1400 2300 1400
Wire Wire Line
	2300 1400 2300 1300
Wire Wire Line
	8450 2550 9050 2550
Wire Wire Line
	8450 3100 9050 3100
Wire Wire Line
	8450 3650 9050 3650
Wire Wire Line
	4650 2200 6750 2200
Wire Wire Line
	6750 2350 4650 2350
Wire Wire Line
	4650 2450 6750 2450
Wire Wire Line
	6750 2600 4650 2600
Wire Wire Line
	4650 2700 6750 2700
Wire Wire Line
	4650 2850 6750 2850
Wire Wire Line
	6750 2950 4650 2950
Wire Wire Line
	4650 3100 6750 3100
Wire Wire Line
	4650 3350 6750 3350
Wire Wire Line
	6750 3450 4650 3450
Wire Wire Line
	4650 3550 6750 3550
Wire Wire Line
	6750 3650 4650 3650
Wire Wire Line
	4650 3800 6750 3800
$Comp
L +5V #PWR02
U 1 1 55E3DB89
P 2250 2400
F 0 "#PWR02" H 2250 2250 50  0001 C CNN
F 1 "+5V" H 2250 2540 50  0000 C CNN
F 2 "" H 2250 2400 60  0000 C CNN
F 3 "" H 2250 2400 60  0000 C CNN
	1    2250 2400
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR03
U 1 1 55E3DC85
P 2250 3300
F 0 "#PWR03" H 2250 3050 50  0001 C CNN
F 1 "GND" H 2250 3150 50  0000 C CNN
F 2 "" H 2250 3300 60  0000 C CNN
F 3 "" H 2250 3300 60  0000 C CNN
	1    2250 3300
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR04
U 1 1 55F7B3D2
P 2250 1900
F 0 "#PWR04" H 2250 1650 50  0001 C CNN
F 1 "GND" H 2250 1750 50  0000 C CNN
F 2 "" H 2250 1900 60  0000 C CNN
F 3 "" H 2250 1900 60  0000 C CNN
	1    2250 1900
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X08 P4
U 1 1 56F1C557
P 1900 2900
F 0 "P4" H 1900 3350 50  0000 C CNN
F 1 "CONN_01X08" V 2000 2900 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Angled_1x08" H 1900 2900 50  0001 C CNN
F 3 "" H 1900 2900 50  0000 C CNN
	1    1900 2900
	-1   0    0    -1  
$EndComp
Wire Wire Line
	2100 2550 2250 2550
Wire Wire Line
	2250 2550 2250 2400
Wire Wire Line
	2100 3250 2250 3250
Wire Wire Line
	2250 3250 2250 3300
Wire Wire Line
	2100 3150 2700 3150
Wire Wire Line
	2700 3050 2100 3050
Wire Wire Line
	2100 2950 2700 2950
Wire Wire Line
	2700 2850 2100 2850
Wire Wire Line
	2100 2750 2700 2750
Wire Wire Line
	2700 2650 2100 2650
Wire Wire Line
	4650 3200 6750 3200
$EndSCHEMATC
