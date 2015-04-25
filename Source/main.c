#include <main.h>
void DeviceInit()
{
    //--Enable PORT A leds by disabling adc
    ADCON1 = 0xff;
    TRISA = 0x00;
    LATA = 0xFF;

    //Enable Interrupt Priority and Global Interrupt
    RCONbits.IPEN = 1;

}
void main()
{
    char i = 0;
    //Enable device related registers
    DeviceInit();
    //Enable USB related registers and variables (NEEDs IPEN and GIE to be enabled before0
    UsbInit();
    INTCONbits.GIE = 1;

     //--------------------------------------------//
while(1)
    {
    LATA ^= 0xFF;
//    delay10ktcy(255);
//    if(BDTable[2].BDin.UOWN == 0)
//    {
//        for (i = 0 ; i< 9 ; i++)
//            EP2inDataHolder[i] = i + 97;
//        EP[2].InBytesCopied = 0;
//        EP[2].InBytesTotal =  9;
//        EP[2].inTranPending = 1;
//        inTranHandler(2);
//    }
    delay10ktcy(200);
    }
    //--------------------------------------------//


}

void ISRH() __interrupt(1)
{
    if(PIR2bits.USBIF == 1)
    {
        UsbInterrupHandler();
        PIR2bits.USBIF = 0;
    }
}
void ISRL() __interrupt(2)
{
    return;
}
