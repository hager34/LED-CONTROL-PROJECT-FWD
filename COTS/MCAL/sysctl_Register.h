#ifndef __REGISTER_SYSCTL_H__
#define __REGISTER_SYSCTL_H__


#define sysctl_base               0x400FE000
#define SYSCTL_RCGCGPIO          (*((volatile u32*)sysctl_base+0x608))
#define SYSCTL_RCGCGPIO_offset    0x608
/*bit_number for each port*/
#define RCGCGPIO_R0               0
#define RCGCGPIO_R1               1
#define RCGCGPIO_R2               2
#define RCGCGPIO_R3               3
#define RCGCGPIO_R4               4
#define RCGCGPIO_R5               5

#define SYSCTL_RCC               (*((volatile u32 *)sysctl_base+0x060))
#define SYSCTL_RCC_offset         0x060
#define SYSDIV                   23
#define OSCSRC                   4
#define BYPASS                   11
#define XTAL                     6
#define USESYSDIV                22

#define SYSCTL_RCC2             (*((volatile u32 *)sysctl_base+0x070))
#define SYSCTL_RCC2_offset       0x070
#define USERCC2                  31
#define OSCSRC2                  4
#define BYPASS2                  11

#define SYSCTL_DC1               (*((volatile u32*)sysctl_base+0x010))
#define SYSCTL_DC1_offset        0x010
#define DC1_PLL                  4
#define MINSYSDIV                12

#define SYSCTL_PLLFREQ0          0x400FE160
#define SYSCTL_PLLFREQ1          0x400FE164
#define SYSCTL_PLLFREQ1_P         8
#define SYSCTL_RCC_SYSDIV_M      0x07800000
#define SYSCTL_RCC_OSCSRC_M      0x00000030
#define SYSCTL_RCC2_OSCSRC2_M    0x00000070
#define SYSCTL_RCC_OSCSRC_INT    0x00000010
#define SYSCTL_RCC2_USERCC2      0x80000000
#define SYSCTL_RCC_OSCSRC_MAIN   0x00000000
#define SYSCTL_RCC_XTAL_M        0x000007C0
#define SYSCTL_RCC_OSCSRC_INT4   0x00000020
#define SYSCTL_RCC_OSCSRC_30     0x00000030
#define SYSCTL_RCC2_OSCSRC2_32   0x00000070
#define SYSCTL_RCC2_BYPASS2      0x00000800
#define SYSCTL_RCC_BYPASS        0x00000800
#define SYSCTL_PLLFREQ1_Q_M      0x00001F00
#define SYSCTL_PLLFREQ1_N_M      0x0000001F
#define SYSCTL_PLLFREQ1_N         0
#define SYSCTL_PLLFREQ0_MINT_M   0x000003FF
#define SYSCTL_PLLFREQ0_MINT_S    0
#define SYSCTL_PLLFREQ0_MFRAC_M  0x000FFC00
#define SYSCTL_PLLFREQ0_MFRAC_S   10
#define SYSCTL_RCC_USESYSDIV     0x00400000
#define SYSCTL_DC1_MINSYSDIV_M   0x0000F000
#define SYSCTL_DC1_MINSYSDIV_80  0x00001000
#define SYSCTL_DC1_MINSYSDIV_66  0x00002000
#define SYSCTL_DC1_MINSYSDIV_50  0x00003000
#define SYSCTL_DC1_MINSYSDIV_40  0x00004000
#define SYSCTL_DC1_MINSYSDIV_25  0x00007000
#define SYSCTL_DC1_MINSYSDIV_20  0x00009000
#define SYSCTL_RCC2_DIV400       0x40000000
#define SYSCTL_RCC2_SYSDIV2_M    0x1F800000
#define SYSCTL_RCC2_SYSDIV2LSB   0x00400000
#define SYSCTL_RCC2_SYSDIV2_S     23
#define SYSCTL_XTAL_16MHZ        0x00000540
#define SYSCTL_RCC_MOSCDIS       0x00000001
#define SYSCTL_MAIN_OSC_DIS      0x00000001
#define SYSCTL_MISC              0x400FE058
#define SYSCTL_MISC_MOSCPUPMIS   0x00000100
#define SYSCTL_RIS               0x400FE050
#define SYSCTL_RIS_MOSCPUPRIS    0x00000100
#define SYSCTL_RCC_PWRDN         0x00002000
#define SYSCTL_RCC2_PWRDN2       0x00002000
#define SYSCTL_MISC_PLLLMIS      0x00000040
#define SYSCTL_PLLSTAT_LOCK      0x00000001
#define SYSCTL_PLLSTAT           0x400FE168
#define SYSCTL_SYSDIV_1          0x07800000
#define SYSCTL_USE_OSC           0x00003800
#define SYSCTL_OSC_MAIN          0x00000000


#define SYSCTL_RCGCADC           (*((volatile u32 *)sysctl_base+0x638))
#define RCGCADC_R0               0
#define RCGCADC_R1               1

#define TIMER_INITIAL_COUNT      0xFFFFA23Fu
#define TIMER_1MS_COUNT            0x5DC0u     /* 1ms set the count to 0x5DC0*/s
#define TIMER_OVERFLOW           0xFFFFFFFFu

static const uint32 g_pui32Xtals[] =
{
    1000000,
    1843200,
    2000000,
    2457600,
    3579545,
    3686400,
    4000000,
    4096000,
    4915200,
    5000000,
    5120000,
    6000000,
    6144000,
    7372800,
    8000000,
    8192000,
    10000000,
    12000000,
    12288000,
    13560000,
    14318180,
    16000000,
    16384000,
    18000000,
    20000000,
    24000000,
    25000000
};


#endif
