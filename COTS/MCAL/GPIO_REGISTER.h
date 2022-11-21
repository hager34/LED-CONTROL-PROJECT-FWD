#ifndef REGISTER_GPIO_H_
#define REGISTER_GPIO_H_

#define BASE_A 0x40058000
#define BASE_B 0x40059000
#define BASE_C 0x4005A000
#define BASE_D 0x4005B000
#define BASE_E 0x4005C000
#define BASE_F 0x4005D000

#define GPIOAFSEL               0x420
#define AFSEL_R0                  0
#define AFSEL_R1                  1
#define AFSEL_R2                  2
#define AFSEL_R3                  3
#define AFSEL_R4                  4
#define AFSEL_R5                  5
#define AFSEL_R6                  6
#define AFSEL_R7                  7

#define GPIODEN                 0x51C
#define DEN_R0                    0
#define DEN_R1                    1
#define DEN_R2                    2
#define DEN_R3                    3
#define DEN_R4                    4
#define DEN_R5                    5
#define DEN_R6                    6
#define DEN_R7                    7

#define GPIOAMSEL               0x528
#define AMSEL_R0                  0
#define AMSEL_R1                  1
#define AMSEL_R2                  2
#define AMSEL_R3                  3
#define AMSEL_R4                  4
#define AMSEL_R5                  5
#define AMSEL_R6                  6
#define AMSEL_R7                  7

#define GPIODIR                 0x400
#define DIR_R0                    0
#define DIR_R1                    1
#define DIR_R2                    2
#define DIR_R3                    3
#define DIR_R4                    4
#define DIR_R5                    5
#define DIR_R6                    6
#define DIR_R7                    7

#define GPIODATA                 0x000
#define DATA_R0                    0
#define DATA_R1                    1
#define DATA_R2                    2
#define DATA_R3                    3
#define DATA_R4                    4
#define DATA_R5                    5
#define DATA_R6                    6
#define DATA_R7                    7


#endif
