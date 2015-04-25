/**@file main.h
*@brief This header shall set all the device configuration bits as well as includes the header files needed for main.c
*@author Bharad
*/
#ifndef __MAIN_H
#define __MAIN_H

#include <USBCore.h>
#include <pic16/pic18f4550.h>
#include <pic16/delay.h>

#include <USBGlobalExtern.h>
//------------Set the Configuration bits here -------------------------------//
/* Disable Xinst, Set the PLLDIV and USBDIV for proper clock speed for USB. Enable the VReg for USB
* Set the Clock source with HSPLL, Enable Power On Timer, and disable Stack OverFlow Reset*/
#pragma config XINST = OFF, PLLDIV = 5, WDT = OFF, USBDIV = 2, CPUDIV=OSC1_PLL2
#pragma config FOSC = HSPLL_HS, PWRT = ON, VREGEN=ON, STVREN = OFF

//--------------------------------------------------------------------------//

#endif // __MAIN_H
