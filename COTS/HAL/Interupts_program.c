

#define  NUM_INTERRUPTS                          155

static __attribute__((section("Viable")))
void (*p_RVectors[NUM_INTERRUPTS])(void) __attribute__((aligned(1024)));
#include"interupts_private.h"


void IntRegister(u32 Interrupt, void (*pfnHandler)(void))
{
    unsigned long Id;


    // Check the arguments.

    ASSERT(Interrupt < NUM_INTERRUPTS);


    // Make sure that the RAM vector table is correctly aligned.

    ASSERT(((unsigned long)p_RVectors & 0x000003ff) == 0);


    // See if the RAM vector table has been initialized.
        if(HWREG(Base+VTABLE) != (unsigned long)p_RVectors)
    {

        // Copy the vector table from the beginning of FLASH to the RAM vector table.

        for(Id = 0; Id< NUM_INTERRUPTS; Id++)
        {
        	p_RVectors[Id] = (void (*)(void))HWREG(Id * 4);
        }


        // Point NVIC at the RAM vector table.

        HWREG(NVIC_VTABLE) = (unsigned long)p_RVectors;
    }


    /*interrupt handler Save */

    p_RVectors[Interrupt] = pfnHandler;
}

