#include <stdint.h>
#include <stdbool.h>
#include "inc/tm4c123gh6pm.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_ints.h"
#include "driverlib/sysctl.h"
#include "driverlib/interrupt.h"
#include "driverlib/gpio.h"
#include "driverlib/timer.h"
/**
 * main.c
 */
int main(void)
{
    uint8_t BOTON;
    SysCtlClockSet(SYSCTL_SYSDIV_5 | SYSCTL_USE_PLL |  SYSCTL_XTAL_16MHZ | SYSCTL_OSC_MAIN);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3);
    GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, GPIO_PIN_4);
    GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_4, GPIO_STRENGTH_8MA, GPIO_PIN_TYPE_STD_WPU);

    while(1){
        if(GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_4)==0)
        {
            BOTON=1;
        }
        if(BOTON==1)
        {
//-----------------------VERDE ENCENDIDO-------------------------------
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2, 0X00);
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, GPIO_PIN_3);
            SysCtlDelay(20000000);
//-------------------------PARPADEO DE VERDE---------------------------
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2, 0X00);
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, 0X00);
            SysCtlDelay(10000000);
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2, 0X00);
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, GPIO_PIN_3);
            SysCtlDelay(10000000);
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2, 0X00);
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, 0X00);
            SysCtlDelay(10000000);
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2, 0X00);
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, GPIO_PIN_3);
            SysCtlDelay(10000000);
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2, 0X00);
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, 0X00);
            SysCtlDelay(10000000);
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2, 0X00);
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, GPIO_PIN_3);
            SysCtlDelay(10000000);
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2, 0X00);
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, 0X00);
            SysCtlDelay(10000000);
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2, 0X00);
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, GPIO_PIN_3);
            SysCtlDelay(10000000);
//-----------------------------AMARILLO------------------------------------------------
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1 , GPIO_PIN_1);
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, GPIO_PIN_3);
            SysCtlDelay(20000000);
//---------------------------------ROJO--------------------------------------------------
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, GPIO_PIN_1);
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2 | GPIO_PIN_3, 0x00);
            SysCtlDelay(20000000);
            GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1 |GPIO_PIN_2 | GPIO_PIN_3, 0x00);
            BOTON=0;
        }
    }
}
