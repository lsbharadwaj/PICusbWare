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
    char test[24];
    //Enable device related registers
    DeviceInit();
    //Enable USB related registers and variables (NEEDs IPEN and GIE to be enabled before0
    UsbInit();
    INTCONbits.GIE = 1;

    //--------------------------------------------//

    while(1)
        {
            printf("\nEnter your name: ");
            USBflush();
            USBgets(test,24);
            printf("\nYour name is %s \n", test);
            printf("Enter your message: ");
            USBflush();
            USBgets(test,24);
            printf("Your message - %s",test);
            USBflush();
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
