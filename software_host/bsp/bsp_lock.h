#ifndef _BSP_LOCK_H_
#define _BSP_LOCK_H_

#include "sc92f836xb_c.h"
#include "bsp_key.h"


typedef struct
{
	unsigned char LockTempFlag;
	unsigned char LockTempCnts;
	unsigned int  u16TimeLock;
	char LockFlag;
}
LOCK_PARA_t;

#define LockTime      3000
#define LockTrue      1
#define LockFalse     0


#define LockRedPort   P2
#define LockRedPin    P25
#define LockRedSet(x) ((x)?(LockRedPin=1):(LockRedPin=0))




void LockRedInit(void);
void LockHandle(void);


#endif



