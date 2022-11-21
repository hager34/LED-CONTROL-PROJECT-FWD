#ifndef STD_TYPES_H
#define STD_TYPES_H

typedef unsigned char       u8;
typedef signed char         s8;
typedef unsigned short int u16;
typedef signed short int   s16;
typedef unsigned long int  u32;
typedef signed long int    s32;
typedef float              f32;
typedef double             f64;
typedef unsigned int    uint32;
typedef unsigned char   uint8;
typedef unsigned short  uint16;
#define STD_TYPES_OK          1
#define STD_TYPES_NOK         0

#define STD_TYPES_NULL        ((void*)0)

#ifndef TRUE
#define TRUE     (1U)
#endif

#ifndef FALSE
#define FALSE    (0U)
#endif
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

#ifndef NULL
#define NULL ((void*) 0U)
#endif

typedef enum
{
	STATUS_FAIL	= 0,
	STATUS_SUCCESS
}tStatus;

typedef unsigned char tBoolean;

#ifndef true
#define true 1
#endif

#ifndef false
#define false 0
#endif

#ifndef bool
#define true        1
#define false       0
#endif






#endif

