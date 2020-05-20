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
uint32_t Status;
uint8_t LED;
uint8_t BLUE=0;
uint8_t RED=0;
uint8_t GREEN=0;

void UART0IntHandler(void){
    UARTIntClear(UART0_BASE,UARTIntStatus(UART0_BASE, true)); //clear the asserted interrupts
    LED = UARTCharGet(UART0_BASE);
    if(LED=='b' && BLUE==0){
        BLUE=1;
        RED=0;
        GREEN=0;
    }
    else if(LED=='b' && BLUE==1){
        BLUE=0;
        RED=0;
        GREEN=0;
    }
    else if(LED=='r' && RED==0){
        RED=1;
        BLUE=0;
        GREEN=0;
    }
    else if(LED=='r' && RED==1){
        RED=0;
        BLUE=0;
        GREEN=0;
    }
    else if(LED=='g' && GREEN==0){
        GREEN=1;
        RED=0;
        BLUE=0;
    }
    else if(LED=='g' && GREEN==1){
        GREEN=0;
        RED=0;
        BLUE=0;
    }
}

void Timer0IntHandler(void){
    TimerIntClear(TIMER0_BASE,TIMER_TIMA_TIMEOUT);
    if(Status==1){
        GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3,0x00);
        Status= 0;
    }
    else{
        Status=1;
        if(RED){
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, GPIO_PIN_1);
        }
        if(GREEN){
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, GPIO_PIN_3);
        }
        if(BLUE){
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, GPIO_PIN_2);
        }
    }
}



int main(void)
{
//----------------------------------------INICIALIZACION DEL RELOJ-------------------------------------------
    SysCtlClockSet(SYSCTL_SYSDIV_5 | SYSCTL_USE_PLL |  SYSCTL_XTAL_16MHZ | SYSCTL_OSC_MAIN);
//---------------------------------------INICIALIZACION DE PERIFERICOS---------------------------------------
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
//---------------------------------------SETEO DE PINES COMO SALIDA (LEDS)----------------------------------
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3);
//---------------------------------------SE ACTIVA EL PERIFERICO DE TIMER0---------------------------------
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
//----------------------------------------INICIALIZACION DEL TIMER 0------------------------------------------
    TimerConfigure(TIMER0_BASE,TIMER_CFG_PERIODIC);
//----------------------------------------CONFIGURACION DEL TIEMPO DEL TIMER 0-------------------------------
    TimerLoadSet(TIMER0_BASE, TIMER_A, (SysCtlClockGet()/2) -1);
//----------------------------------------SE ACTIVA LAS INTERRUPCIONES DEL TIMER-----------------------------
    TimerIntEnable(TIMER0_BASE,TIMER_TIMA_TIMEOUT);
//-----------------------------------------SE ACTIVAN LAS INTERRUPCIONES DEL TIMER0------------------------------------
    IntEnable(INT_TIMER0A);
//----------------------------------------ACTIVAMOS LAS INTERRUPCIONES--------------------------------------
    IntMasterEnable();
//---------------------------------------SE ENCIENDE EL TIMER 0----------------------------------------------
    TimerEnable(TIMER0_BASE, TIMER_A);
//---------------------------------------SE INICIALIZAN UART0----------------------------------
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
//---------------------------------------SETEAMOS LOS PINES DEL PUERTO A PARA COMUNICACION SERIAL--------------------
    GPIOPinTypeUART(GPIO_PORTA_BASE,GPIO_PIN_0|GPIO_PIN_1);
//----------------------------------------CONFIGURACION DE RELOJ UART---------------------------------
    UARTConfigSetExpClk(UART0_BASE,SysCtlClockGet(),115200,
    (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));
//-----------------------------------------SE INICIALIZAN LAS INTERRUPCIONES DEL UART 0---------------------------
    UARTIntEnable(UART0_BASE, UART_INT_RX | UART_INT_RT);
    IntEnable(INT_UART0);
//----------------------------------------ESPECIFICAMOS LOS CRACTERES QUE VAN A ENTRAR POR EL UART)-------------------
    UARTCharPut(UART0_BASE, 'E');
    UARTCharPut(UART0_BASE, 'N');
    UARTCharPut(UART0_BASE, 'T');
    UARTCharPut(UART0_BASE, 'E');
    UARTCharPut(UART0_BASE, 'R');
    UARTCharPut(UART0_BASE, ' ');
    UARTCharPut(UART0_BASE, 'L');
    UARTCharPut(UART0_BASE, 'E');
    UARTCharPut(UART0_BASE, 'T');
    UARTCharPut(UART0_BASE, 'T');
    UARTCharPut(UART0_BASE, 'E');
    UARTCharPut(UART0_BASE, 'R');
    while(1){

    }
}


