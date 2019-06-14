#include "bsp_lock.h"

LOCK_PARA_t Lock_Para_t;

extern unsigned long int MyKeyValue;


void LockRedInit(void)
{
	P2CON |= 0X20;
	P2PH  &= ~0X20;
	LockRedSet(0);
	Lock_Para_t.LockFlag = LockTrue;
}

void LockHandle(void)
{
	 if(TK5_VALUE == MyKeyValue)
	 {
	 	if(!Lock_Para_t.LockTempFlag)
	 	{
			Lock_Para_t.LockTempFlag = LockTrue;
			++ Lock_Para_t.LockTempCnts;
		}
		if(Lock_Para_t.LockTempCnts & 0x01)
		{
		   if(Lock_Para_t.u16TimeLock < LockTime)
		   {
		      Lock_Para_t.u16TimeLock++;
		   }
		   else
		   {
		      Lock_Para_t.u16TimeLock = LockFalse;
			  LockRedSet(1);
			  Lock_Para_t.LockFlag = LockFalse;
		   }
		}
		else
		{
		   if(Lock_Para_t.u16TimeLock < LockTime)
		   {
		      Lock_Para_t.u16TimeLock++;
		   }
		   else
		   {
		      Lock_Para_t.u16TimeLock = LockFalse;
			  LockRedSet(0);
			  Lock_Para_t.LockFlag = LockTrue;
		   }
		}
	 }
	 else
	 {
	 	Lock_Para_t.LockTempFlag = LockFalse;
		Lock_Para_t.u16TimeLock = LockFalse ;
	 }
}











