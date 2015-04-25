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
#ifndef __USB_DEFINE_VALUES_H
#define __USB_DEFINE_VALUES_H

#define MAX_ENDPOINT_CNT 3              //Maximum number of endpoints used excluding 0 count In AND Out as seperate
#define MAX_ENDPOINT_CNT_BTH_DIR 5      //Maximum number of endpoints used excluding 0 count In AND Out as seperate
#define CDC_NOTICE_BUFFER_SIZE 16u
#define CDC_BUFFER_SIZE 8u
#define USB_EP0_BUFFER_SIZE 0x08   //8,16,32,64
#define USB_CONFIG_DESC_TOT_LENGTH (9+9+5+4+5+5+7+9+7+7)

#define EP0_MAX_IN_DATA_HOLDER_SIZE USB_CONFIG_DESC_TOT_LENGTH
#define EP0_MAX_OUT_DATA_HOLDER_SIZE 24
#define EP1_MAX_IN_DATA_HOLDER_SIZE 10
#define EP2_MAX_IN_DATA_HOLDER_SIZE 24
#define EP2_MAX_OUT_DATA_HOLDER_SIZE 24
#define MAX_EP_TRANSFER_SIZE (USB_EP0_BUFFER_SIZE + USB_EP0_BUFFER_SIZE + CDC_NOTICE_BUFFER_SIZE + CDC_BUFFER_SIZE + CDC_BUFFER_SIZE)

#endif // __USB_DEFINE_VALUES_H
