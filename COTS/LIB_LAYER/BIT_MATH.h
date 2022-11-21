#ifndef BIT_MATH_H
#define BIT_MATH_H

#define SET_BIT(REG,BIT_NUM)     (REG=REG|(1<<BIT_NUM))
#define CLR_BIT(REG,BIT_NUM)     (REG=REG&(~(1<<BIT_NUM)))
#define TOG_BIT(REG,BIT_NUM)     (REG=REG^(1<<BIT_NUM))
#define GET_BIT(REG,BIT_NUM)     ((REG>>BIT_NUM)&1)


#define HWREG(x)                                                              \
        (*((volatile unsigned long *)(x)))
#define HWREGH(x)                                                             \
        (*((volatile unsigned short *)(x)))
#define HWREGB(x)                                                             \
        (*((volatile unsigned char *)(x)))
#define HWREGBITW(x, b)                                                       \
        HWREG(((unsigned long)(x) & 0xF0000000) | 0x02000000 |                \
              (((unsigned long)(x) & 0x000FFFFF) << 5) | ((b) << 2))
#define HWREGBITH(x, b)                                                       \
        HWREGH(((unsigned long)(x) & 0xF0000000) | 0x02000000 |               \
               (((unsigned long)(x) & 0x000FFFFF) << 5) | ((b) << 2))
#define HWREGBITB(x, b)                                                       \
        HWREGB(((unsigned long)(x) & 0xF0000000) | 0x02000000 |               \
               (((unsigned long)(x) & 0x000FFFFF) << 5) | ((b) << 2))


#define READ_REG(address) (*(volatile uint32*)(address))

#define WRITE_REG(address,value) ((*(volatile uint32*)(address)) = value )

#define SET_BIT(addr,bit) \
	(READ_REG(addr) |=(1<<bit))

#define RESET_BIT(addr,bit) \
	(READ_REG(addr) &=~(1<<bit))

#define WRITE_REG_MASK(add , value , mask) WRITE_REG(add,\
    (READ_REG(add) & ~mask)|(value & mask))

static inline void WRITE_BIT(uint32 reg, uint8 pin , uint8 val);

static inline uint32 READ_BIT(uint32 reg,uint32 pin);
static inline uint32 READ_PORT(uint32 reg,uint32 pin);

static inline void WRITE_BIT(uint32 reg, uint8 pin , uint8 val){
	if(val == HIGH){
	READ_REG(reg) |= (1<<pin);
	}else if(val == LOW){
		READ_REGT(reg) &= ~(1<<pin);
	}
}

static inline uint8 READ_BIT(uint32 reg,uint8 pin){

	return ((READ_REG(reg)&(1<<pin))>>pin);
}

static inline uint8 READ_PORT(uint32 reg){

	return READ_REG(reg);
}

#endif
