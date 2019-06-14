#ifndef _BSP_INTERRUPT_H_
#define _BSP_INTERRUPT_H_

#include "sc92f836xb_c.h"


#define Interrupt_Enable     1
#define Interrupt_Disable    0

#define Interrupt_Open       1
#define Interrupt_Close      0
#define Interrupt_Default    2



char Interrupt_Handle(char Interrupt_Status);




#endif
