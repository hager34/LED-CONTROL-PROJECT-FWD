
#include"BIT_MATH.h"
#include"STD_TYPES.h"
#include"systick_timer_Private.h"
#include"interupts_Interface.h"
#include"systick_timer_Interface.h"

void SysTick_init(void)
{
	//disable
   HWREG(Systick_Base+STCTRL) &= STCTRL_CLK_SRC | STCTRL_ENABLE;
   STRELOAD_OFFSET=0x00FFFFFF;
   STCURRENT_OFFSET=0;
   //enable
   HWREG(Systick_Base+STCTRL) |= STCTRL_CLK_SRC | STCTRL_ENABLE;
}
void SysTickIntHandler(void (*pHandler)(void)){                       /*call back function*/

	IntRegister(FAULT_SYSTICK, pHandler);                             /*interrupt handler*/

	HWREG(Systick_Base+STCTRL) |= STCTRL_INTEN;                       /*Enable the SysTick interrupt*/
}
void SysTickIntenable(void){


	HWREG(Systick_Base+STCTRL) |= STCTRL_INTEN;                       /*Enable the SysTick interrupt*/

}

uint32 SysTickPeriod(uint32 Period){

	ASSERT((Period > 0) && (Period <= 16777216));                    /*Check*/

    HWREG(Systick_Base+STRELOAD_OFFSET ) = Period - 1;                       /*put SysTick counter period*/

    return(HWREG(Systick_Base+STRELOAD_OFFSET ) + 1);                        /*Return the period of the SysTick counter.*/

}
uint32 SysTickGET(void){

	return(HWREG(Systick_Base+STCURRENT_OFFSET));                          /* current value of the SysTick counter*/
}
void SysTick_delay(uint32 delay)
{
	// Delay in number of bus cycle period units
	STRELOAD_OFFSET = delay - 1;

	// Clear CURRENT
	STCURRENT_OFFSET = 0;

	// Wait for COUNT flag to be set upon roll over.
	while ((Systick_Base+STCTRL & STCTRL_COUNT) == 0) {
	}

}

