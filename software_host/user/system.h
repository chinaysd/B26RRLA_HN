#ifndef _SYSTEM_H_
#define _SYSTEM_H_

#include "sc92f836xb_c.h"
#include "bsp_lock.h"
#include "bsp_timer.h"
#include "bsp_wdt.h"
#include "bsp_interrupt.h"
#include "bsp_uart.h"
#include "TimeOut.h"
#include "bsp_key.h"
#include "bsp_cup.h"













void System_Init(void);
void System_Handle(void);


#endif



