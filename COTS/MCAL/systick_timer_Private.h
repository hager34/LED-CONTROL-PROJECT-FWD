#ifndef systick_timer_private_H_
#define systick_timer_private_H_

#define Systick_Base    0xE000E000

#define STCTRL            0x010
#define STCTRL_ENABLE       16
#define STCTRL_INTEN        1
#define STCTRL_CLK_SRC      2
#define STCTRL_COUNT        3

#define STRELOAD_OFFSET     0x014
#define STRELOAD    (*((volatile u32*)sysctl_base+  0x014))
#define STCURRENT   (*((volatile u32*)sysctl_base+  0x018))
#define STCURRENT_OFFSET      0x018

#define FAULT_SYSTICK       15          // System Tick

#endif
