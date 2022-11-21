#ifndef __INTERFACE_SYSCTL_H__
#define __INTERFACE_SYSCTL_H__

#include"sysctl_Register.h"

void SYSCTLClockEnable(void);
void SysCtlSet(uint32 ui32Config);
uint32 SysCtlClockGet(void);



#endif
