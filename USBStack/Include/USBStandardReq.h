#ifndef __USB_STANDARD_REQ_H
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
#define __USB_STANDARD_REQ_H

#include <USBGlobalExtern.h>
#include <pic16/pic18f4550.h>
#include <USBCore.h>
#include <USBConstantValues.h>
//Standard Request IDs
#define GET_STATUS  0X00
#define SET_ADDRESS 0X05
#define GET_DESCRIPTOR 0x06
#define SET_DESCRIPTOR 0X09

//Standard Request handlers
void setDescriptor();
void getDescriptor();
void setAddress();

#endif // __USB_STANDARD_REQ_H
