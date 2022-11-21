#ifndef __INTERFACE_GPIO_H__
#define __INTERFACE_GPIO_H__

#include "STD_TYPES.h"
#include "GPIO_REGISTER.h"

#ifndef INPUT
#define INPUT 0
#endif

#ifndef OUTPUT
#define OUTPUT 1
#endif

#ifndef LOW
#define LOW 0
#endif

#ifndef HIGH
#define HIGH 1
#endif

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

#define MAX_PORT_PINS         8
#define GPIO_DATA_HW_MASK     0x3FC
#define GPIO_UNLOCK_PORT      0x4C4F434B
#define GPIO_LOCK_PORT        0xFFFFFFFF
#define MAX_ANALOG_PINS       3
#define MAX_ANALOG_REG_VAL    16
#define GPIO_PORTCONTROL_MASK 0xF
#define PORT_CONTROL_STEP     4




uint32 setPinDir(uint32 base , uint8 pin , uint8 dir);
uint32 writePin(uint32 base , uint8 pin , uint8 val);
uint32 readPin(uint32 base , uint8 pin , uint32 *data);
uint32 setPortDir(uint32 base , uint8 dirVal);
uint32 writePort(uint32 base , uint8 val);
uint32 readPort(uint32 base , uint32 *data);
uint32 pinAlternateFunctionSel(uint32 base , uint8 pin , uint8 val);
uint32 portAlternateFunctionSel(uint32 base , uint8 val);
uint32 portDigitalEnable(uint32 base , uint8 val);
uint32 pinDigitalEnable(uint32 base , uint8 pin , uint8 val);
uint32 pinAnalogModeSelect(uint32 base , uint8 pin , uint8 val);
uint32 portAnalogModeSelect(uint32 base , uint8 val);





#endif
