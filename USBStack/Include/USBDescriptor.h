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
#ifndef __USB_DESCRIPTOR_H
#define __USB_DESCRIPTOR_H

#include <USBTypedef.h>
#include <USBGlobalExtern.h>
#include <USBConstantValues.h>
#include <USBTransferCompHandlers.h>
#include <USBdefineValues.h>
/*Macros */

#define HIGHB(x) ((x)>>8)
#define LOWB(x) ((x) & 0xFF)


#define USB_iManufacturer 1u
#define USB_iProduct 2u
#define USB_iSerialNum 3u

#define USB_NUM_CONFIGURATIONS          1u
#define USB_NUM_INTERFACES              2u
#define USB_NUM_ENDPOINTS               3u


#define USB_VID (0x4d8)
#define USB_PID (0x000a)  // Microchip CDC
#define USB_DEV 0x0002

__code const char DDesc[] =
{
    0x12,                                           // bLength
    USB_DEVICE_DESCRIPTOR_TYPE,                         // bDescriptorType
    0x10,
    0x01,                                             // bcdDevice
    0x02,                                           // bDeviceClass
    0x00,                                           // bDeviceSubClass
    0x00,                                           // bDeviceProtocol
    USB_EP0_BUFFER_SIZE,                            // bMaxPacketSize
    0xd8,
    0x04,                                        // idVendor
    0xd8,
    0x04,                                        // idProduct (high byte)
    0x00,
    0x01,                                        // bcdDevice (low byte)
    USB_iManufacturer,                                           // iManufacturer
    USB_iProduct,                                           // iProduct
    USB_iSerialNum,                                           // iSerialNumber (none)
    0x01                                            // bNumConfigurations
};

__code const unsigned char cdc_config_descriptor[] = {
        0x09,                                           // bLength
        USB_CONFIGURATION_DESCRIPTOR_TYPE,              // bDescriptorType
        LOWB(USB_CONFIG_DESC_TOT_LENGTH),               // wTotalLength (low byte)
        HIGHB(USB_CONFIG_DESC_TOT_LENGTH),              // wTotalLength (high byte)
        USB_NUM_INTERFACES,                             // bNumInterfaces
        0x01,                                           // bConfigurationValue
        0x00,                                           // iConfiguration (0=none)
        0x80,                                           // bmAttributes (0x80 = bus powered)
        0xFA,                                           // bMaxPower (in 2 mA units, 50=100 mA)
                                                        //Interface0 descriptor starts here
        0x09,                                           // bLength (Interface0 descriptor starts here)
        USB_INTERFACE_DESCRIPTOR_TYPE,                  // bDescriptorType
        0x00,                                           // bInterfaceNumber
        0x00,                                           // bAlternateSetting
        0x01,                                           // bNumEndpoints (excluding EP0)
        0x02,                                           // bInterfaceClass 0x02=com interface
        0x02,                                           // bInterfaceSubClass 0x02=ACM
        0x01,                                           // bInterfaceProtocol 0x01=AT modem
        0x00,                                           // iInterface (none)
              // CDC header descriptor
        0x05,                                           // bFunctionLength
        0x24,                                           // bDescriptorType
        0x00,                                           // bDescriptorSubtype (CDC header descriptor)
        0x10,                                           // bcdCDC (low byte)
        0x01,                                           // bcdCDC (high byte)
              // CDC abstract control management descriptor
        0x04,                                           // bFunctionLength
        0x24,                                           // bDescriptorType
        0x02,                                           // bDescriptorSubtype (CDC abstract control management descriptor)
        0x00,                                           // bmCapabilities
              // CDC union descriptor
        0x05,                                           // bFunctionLength
        0x24,                                           // bDescriptorType
        0x06,                                           // bDescriptorSubtype (CDC union descriptor)
        0x00,                                           // bControlInterface
        0x01,                                           // bSubordinateInterface0
              // Call management descriptor
        0x05,                                           // bFunctionLength
        0x24,                                           // bDescriptorType
        0x01,                                           // bDescriptorSubtype (Call management descriptor)
        0x00,                                           // bmCapabilities
        0x00,                                           // bInterfaceNum
             // CDC Endpoint 1 IN descriptor (INTERRUPT, Not used)
        0x07,                                           // bLength (Endpoint1 descriptor)
        USB_ENDPOINT_DESCRIPTOR_TYPE,                   // bDescriptorType
        0x81,                                           // bEndpointAddress
        0x03,                                           // bmAttributes (0x03=intr)
        LOWB(CDC_NOTICE_BUFFER_SIZE),                   // wMaxPacketSize (low byte)
        HIGHB(CDC_NOTICE_BUFFER_SIZE),                  // wMaxPacketSize (high byte)
        0x240,                                           // bInterval
                //Interface1 descriptor
        0x09,                                           // bLength (Interface1 descriptor)
        USB_INTERFACE_DESCRIPTOR_TYPE,                  // bDescriptorType
        0x01,                                           // bInterfaceNumber
        0x00,                                           // bAlternateSetting
        0x02,                                           // bNumEndpoints
        0x0A,                                           // datainterface type
        0x00,                                           // bInterfaceSubClass
        0x00,                                           // bInterfaceProtocol (0x00=no protocol, 0xFE=functional unit, 0xFF=vendor specific)
        0x00,                                           // iInterface
             // CDC Endpoint 2 OUT descriptor (BULK)
        0x07,                                           // bLength (Enpoint2 descriptor)
        USB_ENDPOINT_DESCRIPTOR_TYPE,                   // bDescriptorType
        0x02,                                           // bEndpointAddress
        0x02,                                           // bmAttributes (0x02=bulk)
        LOWB(CDC_BUFFER_SIZE),                          // wMaxPacketSize (low byte)
        HIGHB(CDC_BUFFER_SIZE),                         // wMaxPacketSize (high byte)
        0x00,                                           // bInterval
             // CDC Endpoint 2 IN descriptor (BULK)
        0x07,                                           // bLength
        USB_ENDPOINT_DESCRIPTOR_TYPE,                   // bDescriptorType
        0x82,                                           // bEndpointAddress
        0x02,                                           // bmAttributes (0x02=bulk)
        LOWB(CDC_BUFFER_SIZE),                          // wMaxPacketSize (low byte)
        HIGHB(CDC_BUFFER_SIZE),                         // wMaxPacketSize (high byte)
        0x00                                            // bInterval
};

__code const unsigned char cdc_str_descs[] = {
        /* 0 */                  4, USB_STRING_DESCRIPTOR_TYPE, LOWB(USB_LANGID_English_United_States), HIGHB(USB_LANGID_English_United_States),
        /* USB_iManufacturer */ 26, USB_STRING_DESCRIPTOR_TYPE, 'G',0,'e',0,'e',0,'k',0,' ',0,'E',0,'d',0,'i',0,'t',0,'i',0,'o',0,'n',0,
        /* USB_iProduct */      18, USB_STRING_DESCRIPTOR_TYPE, 'C',0,'D',0,'C',0,' ',0,'T',0,'e',0,'s',0,'t',0,
        /* USB_iSerialNum */    18, USB_STRING_DESCRIPTOR_TYPE, '0',0,'0',0,'0',0,'0',0,'0',0,'0',0,'0',0,'1',0
};




EPConfig EPConfigurationData[MAX_ENDPOINT_CNT_BTH_DIR] =
{
   {.EPno = 0,.Dir = 0, .isPacket = 1, .DTSExpected = 0, .UOWNinit = 1, .Buffer = EP0outDataHolder,.TranCompHandler = ControlTransferHandler,.EPSize = USB_EP0_BUFFER_SIZE, .BufferSize = EP0_MAX_OUT_DATA_HOLDER_SIZE},
   {.EPno = 0,.Dir = 1, .isPacket = 1, .DTSExpected = 1, .UOWNinit = 0, .Buffer = EP0inDataHolder,.TranCompHandler = ControlTransferHandler,.EPSize = USB_EP0_BUFFER_SIZE, .BufferSize = EP0_MAX_IN_DATA_HOLDER_SIZE},
   {.EPno = 1,.Dir = 1, .isPacket = 0, .DTSExpected = 0, .UOWNinit = 1, .Buffer = EP1inDataHolder,.TranCompHandler = skip, .EPSize = CDC_NOTICE_BUFFER_SIZE, .BufferSize = EP1_MAX_IN_DATA_HOLDER_SIZE},
   {.EPno = 2,.Dir = 0, .isPacket = 0, .DTSExpected = 0, .UOWNinit = 1, .Buffer = EP2outDataHolder ,.TranCompHandler = ReadComData,.EPSize = CDC_BUFFER_SIZE, .BufferSize = EP2_MAX_OUT_DATA_HOLDER_SIZE},
   {.EPno = 2,.Dir = 1, .isPacket = 0, .DTSExpected = 0, .UOWNinit = 1, .Buffer = EP2inDataHolder ,.TranCompHandler = WriteComData,.EPSize = CDC_BUFFER_SIZE, .BufferSize = EP2_MAX_IN_DATA_HOLDER_SIZE}
};
#endif // __USB_DESCRIPTOR_H
