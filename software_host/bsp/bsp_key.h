#ifndef _BSP_KEY_H_
#define _BSP_KEY_H_

#include "sc92f836xb_c.h"
#include "SensorMethod.h"
#include "TimeOut.h"
#include "bsp_uart.h"
#include "bsp_pwm.h"
#include "bsp_cup.h"
#include "bsp_lock.h"


#define    OneLineTime     100     //50ms


#define NON_VALUE      0X00000000
#define TK1_VALUE      0X00000008
#define TK2_VALUE      0X00000010
#define TK3_VALUE      0X00000020
#define TK4_VALUE      0X00001000
#define TK5_VALUE      0X00004000
#define TK6_VALUE      0X00008000
#define TK7_VALUE      0X00040000
#define TK8_VALUE      0X00080000



#define       NoData              0x00
#define       OpenData            0x01
#define       CloseData           0x02
#define       HeadUpData          0x03
#define       HeadDownData        0x04
#define       LumbarOpenData      0x05
#define       LumbarCloseData     0x06
#define       TableOpenData       0x07       
#define       TableCloseData      0x08
#define       HomeData            0x09

#define       LedOpenData         0x11
#define       LedCloseData        0x22

#define       ExtiLedOpenData       0x0033
#define       ExtiLedCloseData       0x0044










void Key_Handle(void);

void RevDataFootLedOpen(void);
void RevDataFootLedClose(void);


#endif

