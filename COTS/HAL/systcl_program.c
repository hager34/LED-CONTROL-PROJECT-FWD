#include"sysctl_interface.h"
#include"STD_TYPES.h"
#include"REGISTER_TYPES.h"
#include"BIT_MATH.h"
#include "sysctl_Register.h"



void SYSCTLClockEnable(void)
{
	SET_BIT(SYSCTL_RCGCGPIO,RCGCGPIO_R0);

}
void SysCtlSet(uint32 ui32Config)
{
    uint32 ui32Delay, ui32RCC, ui32RCC2;

    //
    // Get the current value of the RCC and RCC2 registers.
    //
    ui32RCC = HWREG(SYSCTL_RCC);
    ui32RCC2 = HWREG(SYSCTL_RCC2);

    //
    // Bypass the PLL and system clock dividers for now.
    //
    ui32RCC |= SYSCTL_RCC_BYPASS;
    ui32RCC &= ~(SYSCTL_RCC_USESYSDIV);
    ui32RCC2 |= SYSCTL_RCC2_BYPASS2;

    //
    // Write the new RCC value.
    //
    HWREG(SYSCTL_RCC) = ui32RCC;
    HWREG(SYSCTL_RCC2) = ui32RCC2;

    //
    // See if the oscillator needs to be enabled.
    //
    if((ui32RCC & SYSCTL_RCC_MOSCDIS) && !(ui32Config & SYSCTL_MAIN_OSC_DIS))
    {
        //
        // Make sure that the required oscillators are enabled.  For now, the
        // previously enabled oscillators must be enabled along with the newly
        // requested oscillators.
        //
        ui32RCC &= (~SYSCTL_RCC_MOSCDIS | (ui32Config & SYSCTL_MAIN_OSC_DIS));

        //
        // Clear the MOSC power up raw interrupt status to be sure it is not
        // set when waiting below.
        //
        HWREG(SYSCTL_MISC) = SYSCTL_MISC_MOSCPUPMIS;

        //
        // Write the new RCC value.
        //
        HWREG(SYSCTL_RCC) = ui32RCC;

        //
        // Timeout using the legacy delay value.
        //
        ui32Delay = 524288;

        while((HWREG(SYSCTL_RIS) & SYSCTL_RIS_MOSCPUPRIS) == 0)
        {
            ui32Delay--;

            if(ui32Delay == 0)
            {
                break;
            }
        }

        //
        // If the main oscillator failed to start up then do not switch to
        // it and return.
        //
        if(ui32Delay == 0)
        {
            return;
        }

    }

    //
    // Set the new crystal value and oscillator source.  Because the OSCSRC2
    // field in RCC2 overlaps the XTAL field in RCC, the OSCSRC field has a
    // special encoding within ui32Config to avoid the overlap.
    //
    ui32RCC &= ~(SYSCTL_RCC_XTAL_M | SYSCTL_RCC_OSCSRC_M);
    ui32RCC |= ui32Config & (SYSCTL_RCC_XTAL_M | SYSCTL_RCC_OSCSRC_M);
    ui32RCC2 &= ~(SYSCTL_RCC2_USERCC2 | SYSCTL_RCC2_OSCSRC2_M);
    ui32RCC2 |= ui32Config & (SYSCTL_RCC2_USERCC2 | SYSCTL_RCC_OSCSRC_M);
    ui32RCC2 |= (ui32Config & 0x00000008) << 3;

    //
    // Write the new RCC value.
    //
    HWREG(SYSCTL_RCC) = ui32RCC;
    HWREG(SYSCTL_RCC2) = ui32RCC2;

    //
    // Set the PLL configuration.
    //
    ui32RCC &= ~SYSCTL_RCC_PWRDN;
    ui32RCC |= ui32Config & SYSCTL_RCC_PWRDN;
    ui32RCC2 &= ~SYSCTL_RCC2_PWRDN2;
    ui32RCC2 |= ui32Config & SYSCTL_RCC2_PWRDN2;

    //
    // Clear the PLL lock interrupt.
    //
    HWREG(SYSCTL_MISC) = SYSCTL_MISC_PLLLMIS;

    //
    // Write the new RCC value.
    //
    if(ui32RCC2 & SYSCTL_RCC2_USERCC2)
    {
        HWREG(SYSCTL_RCC2) = ui32RCC2;
        HWREG(SYSCTL_RCC) = ui32RCC;
    }
    else
    {
        HWREG(SYSCTL_RCC) = ui32RCC;
        HWREG(SYSCTL_RCC2) = ui32RCC2;
    }

    //
    // Set the requested system divider and disable the appropriate
    // oscillators.  This value is not written immediately.
    //
    ui32RCC &= ~(SYSCTL_RCC_SYSDIV_M | SYSCTL_RCC_USESYSDIV |
                 SYSCTL_RCC_MOSCDIS);
    ui32RCC |= ui32Config & (SYSCTL_RCC_SYSDIV_M | SYSCTL_RCC_USESYSDIV |
                             SYSCTL_RCC_MOSCDIS);
    ui32RCC2 &= ~(SYSCTL_RCC2_SYSDIV2_M);
    ui32RCC2 |= ui32Config & SYSCTL_RCC2_SYSDIV2_M;
    if(ui32Config & SYSCTL_RCC2_DIV400)
    {
        ui32RCC |= SYSCTL_RCC_USESYSDIV;
        ui32RCC2 &= ~(SYSCTL_RCC_USESYSDIV);
        ui32RCC2 |= ui32Config & (SYSCTL_RCC2_DIV400 | SYSCTL_RCC2_SYSDIV2LSB);
    }
    else
    {
        ui32RCC2 &= ~(SYSCTL_RCC2_DIV400);
    }

    //
    // See if the PLL output is being used to clock the system.
    //
    if(!(ui32Config & SYSCTL_RCC_BYPASS))
    {
        //
        // Wait until the PLL has locked.
        //
        for(ui32Delay = 32768; ui32Delay > 0; ui32Delay--)
        {
            if((HWREG(SYSCTL_PLLSTAT) & SYSCTL_PLLSTAT_LOCK))
            {
                break;
            }
        }

        //
        // Enable use of the PLL.
        //
        ui32RCC &= ~(SYSCTL_RCC_BYPASS);
        ui32RCC2 &= ~(SYSCTL_RCC2_BYPASS2);
    }

    //
    // Write the final RCC value.
    //
    HWREG(SYSCTL_RCC) = ui32RCC;
    HWREG(SYSCTL_RCC2) = ui32RCC2;

    //
    // Delay for a little bit so that the system divider takes effect.
    //
    SysCtlDelay(16);
}


uint32 SysCtlClockGet(void)
{
    uint32 ui32RCC, ui32RCC2, ui32PLL, ui32Clk, ui32Max;
    uint32 ui32PLL1;


    //
    // Read RCC and RCC2.
    //
    ui32RCC = HWREG(SYSCTL_RCC);
    ui32RCC2 = HWREG(SYSCTL_RCC2);

    //
    // Get the base clock rate.
    //
    switch((ui32RCC2 & SYSCTL_RCC2_USERCC2) ?
           (ui32RCC2 & SYSCTL_RCC2_OSCSRC2_M) :
           (ui32RCC & SYSCTL_RCC_OSCSRC_M))
    {
        //
        // The main oscillator is the clock source.  Determine its rate from
        // the crystal setting field.
        //
        case SYSCTL_RCC_OSCSRC_MAIN:
        {
            ui32Clk = g_pui32Xtals[(ui32RCC & SYSCTL_RCC_XTAL_M) >>
								   XTAL];
            break;
        }

        //
        // The internal oscillator is the source clock.
        //
        case SYSCTL_RCC_OSCSRC_INT:
        {
            //
            // The internal oscillator on all devices is 16 MHz.
            //
            ui32Clk = 16000000;
            break;
        }

        //
        // The internal oscillator divided by four is the source clock.
        //
        case SYSCTL_RCC_OSCSRC_INT4:
        {
            //
            // The internal oscillator on all devices is 16 MHz.
            //
            ui32Clk = 16000000 / 4;
            break;
        }

        //
        // The internal 30-KHz oscillator is the source clock.
        //
        case SYSCTL_RCC_OSCSRC_30:
        {
            //
            // The internal 30-KHz oscillator has an accuracy of +/- 30%.
            //
            ui32Clk = 30000;
            break;
        }

        //
        // The 32.768-KHz clock from the hibernate module is the source clock.
        //
        case SYSCTL_RCC2_OSCSRC2_32:
        {
            ui32Clk = 32768;
            break;
        }

        //
        // An unknown setting, so return a zero clock (that is, an unknown
        // clock rate).
        //
        default:
        {
            return(0);
        }
    }

    //
    // Default the maximum frequency to the maximum 32-bit unsigned value.
    //
    ui32Max = 0xffffffff;

    //
    // See if the PLL is being used.
    //
    if(((ui32RCC2 & SYSCTL_RCC2_USERCC2) &&
        !(ui32RCC2 & SYSCTL_RCC2_BYPASS2)) ||
       (!(ui32RCC2 & SYSCTL_RCC2_USERCC2) && !(ui32RCC & SYSCTL_RCC_BYPASS)))
    {
        //
        // Read the two PLL frequency registers.  The formula for a
        // TM4C123 device is "(xtal * m) / ((q + 1) * (n + 1))".
        //
        ui32PLL = HWREG(SYSCTL_PLLFREQ0);
        ui32PLL1 = HWREG(SYSCTL_PLLFREQ1);

        //
        // Divide the input clock by the dividers.
        //
        ui32Clk /= ((((ui32PLL1 & SYSCTL_PLLFREQ1_Q_M) >>
        		SYSCTL_PLLFREQ1_P) + 1) *
                    (((ui32PLL1 & SYSCTL_PLLFREQ1_N_M) >>
                    		SYSCTL_PLLFREQ1_N) + 1) * 2);

        //
        // Multiply the clock by the multiplier, which is split into an
        // integer part and a fractional part.
        //
        ui32Clk = ((ui32Clk * ((ui32PLL & SYSCTL_PLLFREQ0_MINT_M) >>
                               SYSCTL_PLLFREQ0_MINT_S)) +
                   ((ui32Clk * ((ui32PLL & SYSCTL_PLLFREQ0_MFRAC_M) >>
                                SYSCTL_PLLFREQ0_MFRAC_S)) >> 10));

        //
        // Force the system divider to be enabled.  It is always used when
        // using the PLL, but in some cases it does not read as being enabled.
        //
        ui32RCC |= SYSCTL_RCC_USESYSDIV;

        //
        // Calculate the maximum system frequency.
        //
        switch(HWREG(SYSCTL_DC1) & SYSCTL_DC1_MINSYSDIV_M)
        {
            case SYSCTL_DC1_MINSYSDIV_80:
            {
                ui32Max = 80000000;
                break;
            }
            case SYSCTL_DC1_MINSYSDIV_66:
            {
                ui32Max = 66666666;
                break;
            }
            case SYSCTL_DC1_MINSYSDIV_50:
            {
                ui32Max = 50000000;
                break;
            }
            case SYSCTL_DC1_MINSYSDIV_40:
            {
                ui32Max = 40000000;
                break;
            }
            case SYSCTL_DC1_MINSYSDIV_25:
            {
                ui32Max = 25000000;
                break;
            }
            case SYSCTL_DC1_MINSYSDIV_20:
            {
                ui32Max = 20000000;
                break;
            }
            default:
            {
                break;
            }
        }
    }

    //
    // See if the system divider is being used.
    //
    if(ui32RCC & SYSCTL_RCC_USESYSDIV)
    {
        //
        // Adjust the clock rate by the system clock divider.
        //
        if(ui32RCC2 & SYSCTL_RCC2_USERCC2)
        {
            if((ui32RCC2 & SYSCTL_RCC2_DIV400) &&
               (((ui32RCC2 & SYSCTL_RCC2_USERCC2) &&
                 !(ui32RCC2 & SYSCTL_RCC2_BYPASS2)) ||
                (!(ui32RCC2 & SYSCTL_RCC2_USERCC2) &&
                 !(ui32RCC & SYSCTL_RCC_BYPASS))))

            {
                ui32Clk = ((ui32Clk * 2) / (((ui32RCC2 &
                                              (SYSCTL_RCC2_SYSDIV2_M |
                                               SYSCTL_RCC2_SYSDIV2LSB)) >>
                                             (SYSDIV - 1)) +
                                            1));
            }
            else
            {
                ui32Clk /= (((ui32RCC2 & SYSCTL_RCC2_SYSDIV2_M) >>
                             SYSCTL_RCC2_SYSDIV2_S) + 1);
            }
        }
        else
        {
            ui32Clk /= (((ui32RCC & SYSCTL_RCC_SYSDIV_M) >>
            		SYSDIV) + 1);
        }
    }

    //
    // Limit the maximum clock to the maximum clock frequency.
    //
    if(ui32Max < ui32Clk)
    {
        ui32Clk = ui32Max;
    }

    //
    // Return the computed clock rate.
    //
    return(ui32Clk);
}

