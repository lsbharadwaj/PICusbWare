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
#ifndef __USB_CONSTANT_VALUE_H
#define __USB_CONSTANT_VALUE_H

/*Language Ids*/
#define USB_LANGID_Chinese_Macau_SAR                    0x1404
#define USB_LANGID_Croatian                             0x041a
#define USB_LANGID_Czech                                0x0405
#define USB_LANGID_Danish                               0x0406
#define USB_LANGID_Dutch_Netherlands                    0x0413
#define USB_LANGID_Dutch_Belgium                        0x0813
#define USB_LANGID_English_United_States                0x0409
#define USB_LANGID_English_United_Kingdom               0x0809
#define USB_LANGID_English_Australian                   0x0c09
#define USB_LANGID_English_Canadian                     0x1009
#define USB_LANGID_English_New_Zealand                  0x1409
#define USB_LANGID_English_Ireland                      0x1809
#define USB_LANGID_English_South_Africa                 0x1c09
#define USB_LANGID_English_Jamaica                      0x2009
#define USB_LANGID_English_Caribbean                    0x2409
#define USB_LANGID_English_Belize                       0x2809
#define USB_LANGID_English_Trinidad                     0x2c09
#define USB_LANGID_English_Zimbabwe                     0x3009
#define USB_LANGID_English_Philippines                  0x3409
#define USB_LANGID_Estonian                             0x0425
#define USB_LANGID_Faeroese                             0x0438
#define USB_LANGID_Farsi                                0x0429
#define USB_LANGID_Finnish                              0x040b
#define USB_LANGID_French_Standard                      0x040c
#define USB_LANGID_French_Belgian                       0x080c
#define USB_LANGID_French_Canadian                      0x0c0c
#define USB_LANGID_French_Switzerland                   0x100c
#define USB_LANGID_French_Luxembourg                    0x140c
#define USB_LANGID_French_Monaco                        0x180c
#define USB_LANGID_Georgian                             0x0437
#define USB_LANGID_German_Standard                      0x0407
#define USB_LANGID_German_Switzerland                   0x0807
#define USB_LANGID_German_Austria                       0x0c07
#define USB_LANGID_German_Luxembourg                    0x1007
#define USB_LANGID_German_Liechtenstein                 0x1407
#define USB_LANGID_Greek                                0x0408
#define USB_LANGID_Gujarati                             0x0447
#define USB_LANGID_Hebrew                               0x040d
#define USB_LANGID_Hindi                                0x0439
#define USB_LANGID_Hungarian                            0x040e
#define USB_LANGID_Icelandic                            0x040f
#define USB_LANGID_Indonesian                           0x0421
#define USB_LANGID_Italian_Standard                     0x0410
#define USB_LANGID_Italian_Switzerland                  0x0810
#define USB_LANGID_Japanese                             0x0411
#define USB_LANGID_Kannada                              0x044b
#define USB_LANGID_Kashmiri_India                       0x0860
#define USB_LANGID_Kazakh                               0x043f
#define USB_LANGID_Konkani                              0x0457
#define USB_LANGID_Korean                               0x0412
#define USB_LANGID_Korean_Johab                         0x0812
#define USB_LANGID_Latvian                              0x0426
#define USB_LANGID_Lithuanian                           0x0427
#define USB_LANGID_Lithuanian_Classic                   0x0827
#define USB_LANGID_Macedonian                           0x042f
#define USB_LANGID_Malay_Malaysian                      0x043e
#define USB_LANGID_Malay_Brunei_Darussalam              0x083e
#define USB_LANGID_Malayalam                            0x044c
#define USB_LANGID_Manipuri                             0x0458
#define USB_LANGID_Marathi                              0x044e
#define USB_LANGID_Nepali_India                         0x0861
#define USB_LANGID_Norwegian_Bokmal                     0x0414
#define USB_LANGID_Norwegian_Nynorsk                    0x0814
#define USB_LANGID_Oriya                                0x0448
#define USB_LANGID_Polish                               0x0415
#define USB_LANGID_Portuguese_Brazil                    0x0416
#define USB_LANGID_Portuguese_Standard                  0x0816
#define USB_LANGID_Punjabi                              0x0446
#define USB_LANGID_Romanian                             0x0418
#define USB_LANGID_Russian                              0x0419
#define USB_LANGID_Sanskrit                             0x044f
#define USB_LANGID_Serbian_Cyrillic                     0x0c1a
#define USB_LANGID_Serbian_Latin                        0x081a
#define USB_LANGID_Sindhi                               0x0459
#define USB_LANGID_Slovak                               0x041b
#define USB_LANGID_Slovenian                            0x0424
#define USB_LANGID_Spanish_Traditional_Sort             0x040a
#define USB_LANGID_Spanish_Mexican                      0x080a
#define USB_LANGID_Spanish_Modern_Sort                  0x0c0a
#define USB_LANGID_Spanish_Guatemala                    0x100a
#define USB_LANGID_Spanish_Costa_Rica                   0x140a
#define USB_LANGID_Spanish_Panama                       0x180a
#define USB_LANGID_Spanish_Dominican_Republic           0x1c0a
#define USB_LANGID_Spanish_Venezuela                    0x200a
#define USB_LANGID_Spanish_Colombia                     0x240a
#define USB_LANGID_Spanish_Peru                         0x280a
#define USB_LANGID_Spanish_Argentina                    0x2c0a
#define USB_LANGID_Spanish_Ecuador                      0x300a
#define USB_LANGID_Spanish_Chile                        0x340a
#define USB_LANGID_Spanish_Uruguay                      0x380a
#define USB_LANGID_Spanish_Paraguay                     0x3c0a
#define USB_LANGID_Spanish_Bolivia                      0x400a
#define USB_LANGID_Spanish_El_Salvador                  0x440a
#define USB_LANGID_Spanish_Honduras                     0x480a
#define USB_LANGID_Spanish_Nicaragua                    0x4c0a
#define USB_LANGID_Spanish_Puerto_Rico                  0x500a
#define USB_LANGID_Sutu                                 0x0430
#define USB_LANGID_Swahili_Kenya                        0x0441
#define USB_LANGID_Swedish                              0x041d
#define USB_LANGID_Swedish_Finland                      0x081d
#define USB_LANGID_Tamil                                0x0449
#define USB_LANGID_Tatar_Tatarstan                      0x0444
#define USB_LANGID_Telugu                               0x044a
#define USB_LANGID_Thai                                 0x041e
#define USB_LANGID_Turkish                              0x041f
#define USB_LANGID_Ukrainian                            0x0422
#define USB_LANGID_Urdu_Pakistan                        0x0420
#define USB_LANGID_Urdu_India                           0x0820
#define USB_LANGID_Uzbek_Latin                          0x0443
#define USB_LANGID_Uzbek_Cyrillic                       0x0843
#define USB_LANGID_Vietnamese                           0x042a
#define USB_LANGID_HID_UDD                              0x04ff
#define USB_LANGID_HID_Vendor1                          0xf0ff
#define USB_LANGID_HID_Vendor2                          0xf4ff
#define USB_LANGID_HID_Vendor3                          0xf8ff
#define USB_LANGID_HID_Vendor4                          0xfcff

/* Descriptor Types */
#define USB_DEVICE_DESCRIPTOR_TYPE                      1u
#define USB_CONFIGURATION_DESCRIPTOR_TYPE               2u
#define USB_STRING_DESCRIPTOR_TYPE                      3u
#define USB_INTERFACE_DESCRIPTOR_TYPE                   4u
#define USB_ENDPOINT_DESCRIPTOR_TYPE                    5u
#define USB_DEVICE_QUALIFIER_DESCRIPTOR_TYPE            6u
#define USB_OTHER_SPEED_CONFIGURATION_DESCRIPTOR_TYPE   7u
#define USB_INTERFACE_POWER_DESCRIPTOR_TYPE             8u
#define USB_OTG_DESCRIPTOR_TYPE                         9u
#define USB_DEBUG_DESCRIPTOR_TYPE                       10u
#define USB_INTERFACE_ASSOCIATION_DESCRIPTOR_TYPE       11u

#endif // __USB_CONSTANT_VALUE_H
