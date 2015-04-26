/*
//    This file belongs to PICusbWare
//    A free USB firmware for PIC18f4550 to be compiled with SDCC
//
//    Copyright (C) 2015  L.S.Bharadwaj (lsbharadwaj[at]gmail.com)
//
//    This program is free software; you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation; either version 2 of the License, or
//    (at your option) any later version.
//
//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License along
//    with this program; if not, write to the Free Software Foundation, Inc.,
//    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
//  ================================================================================
*/
/** @file USBCore.h
* @brief This file contains the variables and the functions used by the stack alone and will not be needed
* to be shared with the users
*/
#ifndef __USB_CORE_H
#define __USB_CORE_H

#include <pic16/pic18f4550.h>
#include <pic16/delay.h>

///This function initializes the USB for Full speed operation. Call this before using the stack
void UsbInit();
void UsbInterrupHandler();
char outTranHandler(char EPno);
char inTranHandler(char EPno);
void configureEp(char ind);
void EPstall(char EpNo);
void ControlTransferHandler();
char outTranHandler(char EPno);
char inTranHandler(char EPno);
void USBflush();
void USBgets(char* buf, char maxDataSize);
#endif // __USB_CORE_H
