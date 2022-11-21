#ifndef INTERFACE_Interupts_H_
#define INTERFACE_Interupts_H_


void IntRegister(u32 ulInterrupt, void (*pfnHandler)(void));


#endif
