#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include"GPIO_INTERFACE.h"

uint32 setPinDir(uint32 base , uint8 pin , uint8 dir){
	u32 Local_u8ErrorState = STD_TYPES_OK;
    if(base == BASE_A || base == BASE_B|| base == BASE_C||
       base == BASE_D || base == BASE_E|| base == BASE_F){
    	if(pin > MAX_PORT_PINS){
    		Local_u8ErrorState = STD_TYPES_OK;
    	}else{
    		if(dir == INPUT){
              HW_WRITE_BIT(base+GPIODIR,pin,dir);
    		}else if(dir == OUTPUT){
    	      HW_WRITE_BIT(base+GPIODIR,pin,dir);
    		}else{
    			Local_u8ErrorState = STD_TYPES_NOK;
    		}
    	}
    }else {
    	Local_u8ErrorState = STD_TYPES_NOK;
    }
    return Local_u8ErrorState ;
}

uint32 writePin(uint32 base , uint8 pin , uint8 val){
	u32 Local_u8ErrorState = STD_TYPES_OK;
    if(base == BASE_A || base == BASE_B|| base == BASE_C||
       base == BASE_D || base == BASE_E|| base == BASE_F){
    	if(pin > MAX_PORT_PINS){
    		Local_u8ErrorState = STD_TYPES_OK;
    	}else{
    		if(val == INPUT){
              WRITE_BIT(base+GPIODIR+GPIO_DATA_HW_MASK,pin,val);
    		}else if(val == OUTPUT){
    	      HW_WRITE_BIT(base+GPIODATA+GPIO_DATA_HW_MASK,pin,val);
    		}else{
    			Local_u8ErrorState = STD_TYPES_NOK;
    		}
    	}
    }else {
    	Local_u8ErrorState = STD_TYPES_NOK;
    }
    return Local_u8ErrorState ;
}

uint32 readPin(uint32 base , uint8 pin , uint32 *Data){
	u32 Local_u8ErrorState = STD_TYPES_OK;
    if(base == BASE_A || base == BASE_B|| base == BASE_C||
       base == BASE_D || base == BASE_E|| base == BASE_F){
    	if(pin > MAX_PORT_PINS){
    		Local_u8ErrorState = STD_TYPES_OK;
    	    	}else{
    	    		*Data = HW_READ_BIT(base+GPIODATA+GPIO_DATA_HW_MASK,pin);
    	    	}
    	    }else {
    	    	Local_u8ErrorState = STD_TYPES_NOK;
    	    }
    	    return Local_u8ErrorState ;
}

uint32 setPortDir(uint32 base , uint8 dirVal){
	u32 Local_u8ErrorState = STD_TYPES_OK;
	    if(base == BASE_A || base == BASE_B|| base == BASE_C||
	       base == BASE_D || base == BASE_E|| base == BASE_F){
	    	HW_WRITE_REG_32BIT(base+GPIODIR ,dirVal);
	    }else {
	     	Local_u8ErrorState = STD_TYPES_NOK;
	    }
	    return  Local_u8ErrorState ;
	}

uint32 writePort(uint32 base , uint8 val){
	u32 Local_u8ErrorState = STD_TYPES_OK;
	    if(base == BASE_A || base == BASE_B|| base == BASE_C||
	       base == BASE_D || base == BASE_E|| base == BASE_F){
	    	HW_WRITE_REG_32BIT(base+GPIODATA+GPIO_DATA_HW_MASK,val);
	    }else {
	    	Local_u8ErrorState = STD_TYPES_NOK;
	    }
	    return Local_u8ErrorState ;
	}

uint32 writePort(uint32 base , uint8 val){
	u32 Local_u8ErrorState = STD_TYPES_OK;
	    if(base == BASE_A || base == BASE_B|| base == BASE_C||
	       base == BASE_D || base == BASE_E|| base == BASE_F){
	    	HW_WRITE_REG_32BIT(base+GPIODATA+GPIO_DATA_HW_MASK,val);
	    }else {
	    	Local_u8ErrorState = STD_TYPES_NOK;
	    }
	    return Local_u8ErrorState ;
	}

uint32 readPort(uint32 base , uint32 *data){
	u32 Local_u8ErrorState = STD_TYPES_OK;
	    if(base == BASE_A || base == BASE_B|| base == BASE_C||
	       base == BASE_D || base == BASE_E|| base == BASE_F){
	    	*data = READ_REG(base+GPIODATA+GPIO_DATA_HW_MASK);
	    }else {
	    	Local_u8ErrorState = STD_TYPES_NOK;
	    }
	    return Local_u8ErrorState ;
	}
uint32 pinAlternateFunctionSel(uint32 base , uint8 pin , uint8 val){
	u32 Local_u8ErrorState = STD_TYPES_OK;
	    if(base == BASE_A || base == BASE_B|| base == BASE_C||
	       base == BASE_D || base == BASE_E|| base == BASE_F){
	    	if(pin > MAX_PORT_PINS){
	    		Local_u8ErrorState = STD_TYPES_NOK;
	    	}else{
	    		if(val == TRUE || val == FALSE){
	    		HW_WRITE_BIT(base+GPIOAFSEL,pin,val);
	    		}else{
	    			Local_u8ErrorState = STD_TYPES_NOK;
	    		}
	    	}

	    }else {
	    	Local_u8ErrorState = STD_TYPES_NOK;
	    }
	    return Local_u8ErrorState;
	}
uint32 portDigitalEnable(uint32 base , uint8 val){
	u32 Local_u8ErrorState = STD_TYPES_OK;
			    if(base == BASE_A || base == BASE_B|| base == BASE_C||
			       base == BASE_D || base == BASE_E|| base == BASE_F){
			    		HW_WRITE_REG_32BIT(base+GPIODEN,val);
			    }else {
			    	Local_u8ErrorState = STD_TYPES_NOK;
			    }
			    return  Local_u8ErrorState;
}

uint32 pinDigitalEnable(uint32 base , uint8 pin , uint8 val){
	u32 Local_u8ErrorState = STD_TYPES_OK;
			    if(base == BASE_A || base == BASE_B|| base == BASE_C||
			       base == BASE_D || base == BASE_E|| base == BASE_F){
			    	if(pin > MAX_PORT_PINS){
			    		Local_u8ErrorState = STD_TYPES_NOK;
			    	}else{
			    		if(val == TRUE || val == FALSE){
			    		HW_WRITE_BIT(base+GPIODEN,pin,val);
			    		}else{
			    			Local_u8ErrorState = STD_TYPES_NOK;
			    }
			    	}
			    }else {
			    	Local_u8ErrorState = STD_TYPES_NOK;
			    }
			    return Local_u8ErrorState;
}
