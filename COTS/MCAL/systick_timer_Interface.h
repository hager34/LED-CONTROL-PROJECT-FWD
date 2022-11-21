#ifndef INTERFACE_SYSTICK_H_
#define INTERFACE_SYSTICK_H_


void SysTick_init(void);
void SysTickIntHandler(void (*pfnHandler)(void));
uint32 SysTickPeriod(uint32 Period);
uint32 SysTickGET(void);
void SysTick_delay(uint32 delay);



#endif
