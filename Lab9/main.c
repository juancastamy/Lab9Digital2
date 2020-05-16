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
#include "driverlib/uart.h"
#include "driverlib/pin_map.h"
/**
 * main.c
 */
int main(void)
{
//----------------------------------------INICIALIZACION DEL RELOJ-------------------------------------------
    SysCtlClockSet(SYSCTL_SYSDIV_5 | SYSCTL_USE_PLL |  SYSCTL_XTAL_16MHZ | SYSCTL_OSC_MAIN);
//---------------------------------------INICIALIZACION DE PERIFERICOS---------------------------------------
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
//---------------------------------------SETEO DE PINES COMO SALIDA (LEDS)----------------------------------
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3);
//---------------------------------------SE ACTIVA EL PERIFERICO DE TIMER0---------------------------------
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
//----------------------------------------INICIALIZACION DEL TIMER 0------------------------------------------
    TimerConfigure(TIMER0_BASE,TIMER_CFG_PERIODIC);
//----------------------------------------CONFIGURACION DEL TIEMPO DEL TIMER 0-------------------------------
    TimerLoadSet(TIMER0_BASE, TIMER_BOTH, 16000000 -1);
//-----------------------------------------SE ACTIVAN LAS INTERRUPCIONES DEL TIMER0------------------------------------
    IntEnable(INT_TIMER0A);
//----------------------------------------SE ACTIVA LAS INTERRUPCIONES DEL TIMER-----------------------------
    TimerIntEnable(TIMER0_BASE,TIMER_TIMA_TIMEOUT);
    //----------------------------------------ACTIVAMOS LAS INTERRUPCIONES--------------------------------------
        IntMasterEnable();
//---------------------------------------SE ENCIENDE EL TIMER 0----------------------------------------------
    TimerEnable(TIMER0_BASE, TIMER_BOTH);

    while(1){
    }
}
void Timer0IntHandler(void){
    TimerIntClear(TIMER0_BASE,TIMER_TIMA_TIMEOUT);
    if(GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_2)){
        GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3,0x00);
    }
    else{
        GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_2,GPIO_PIN_2);
    }
}
