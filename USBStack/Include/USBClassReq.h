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
#ifndef __USB_CLASS_REQ_H
#define __USB_CLASS_REQ_H

//Includes
#include <pic16/pic18f4550.h>
#include <USBGlobalExtern.h>
#include <USBCore.h>

//Class Specific Request IDs
#define SET_CONTROL_LINE_STATE 0x22
#define SET_LINE_CODING 0x20

void SetControlLineState();
void SetLineCoding();
#endif //__USB_CLASS_REQ_H
