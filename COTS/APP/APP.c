/*
 * APP.c
 *
 *  Created on: Nov 14, 2022
 *      Author: Hager Elksas
 */

#include"STD_TYPES.h"
#include"BIT_MATH.h"

#include"GPIO_INTERFACE.h"
#include"sysctl_interface.h"
#include"systick_timer_interface.h"
#include"Interupts_Interface.h"

static uint32 TIME;

void SysTick_IntHandler(void);
#define LED_PIN               31
int main (void)
{
	SYSCTLClockEnable();
	SysCtlSet(SYSCTL_SYSDIV_1 | SYSCTL_USE_OSC | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);
    uint32 clock;
	clock=SysCtlClockGet();
	SysTickIntHandler(SysTick_IntHandler);

    SysTickPeriod(SysCtlClockGet());
   // SysTickIntenable();
    SysTick_init();
    SysTick_delay(16);

    setPinDir(BASE_F , LED_PIN , OUTPUT);
    pinDigitalEnable(BASE_F , LED_PIN , HIGH);

while(1)
{
	/*do nothing*/
}

}


void SysTick_IntHandler(void)
    {
	u32 GPIOA_LED_DATA= writePin( BASE_F, LED_PIN, HIGH);
	GPIOA_LED_DATA=GPIOA_LED_DATA^(1<<0);                    //toggle led every time systick_inHandler call
       TIME++;
    }
