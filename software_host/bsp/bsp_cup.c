#include "bsp_cup.h"

MOTRO_PARA_T Motro_Para_t;

void Cup_Init(void)
{
	P0CON |= 0X06;
	P0PH  &= ~0X06;
	P0 &= ~0X06;
}

void CupProcessHandle(void)
{
	if(Motro_Para_t.up_flag)
	{
	   Motro_Para_t.motro_count0 ++;
	   if(Motro_Para_t.motro_count0 > CupTimeCnts)
	   {
	      Motro_Para_t.motro_count0 = CupClear0;
		  Motro_Para_t.up_flag = CupClear0;
		  Motro_Para_t.down_flag = CupSet1;
		  P0 &= 0Xf9;
	   }
	}
	if(Motro_Para_t.down_flag)
	{
	   Motro_Para_t.motro_count1 ++;
	   if(Motro_Para_t.motro_count1 > CupTimeCnts)
	   {
	     Motro_Para_t.motro_count1 = CupClear0;
		 Motro_Para_t.up_flag = CupSet1;
		 Motro_Para_t.down_flag = CupClear0;
		 P0 &= 0Xf9;
	   }
	}
}

void CupHandle(void)
{
	if(Motro_Para_t.MOTRO_FLAG == CupFalse)
	{
	  Motro_Para_t.MOTRO_FLAG = CupTrue;
	  P0 &= 0Xf9;
	  P0 |= 1 << 1;
	  Motro_Para_t.motro_count0 = CupClear0;
	  Motro_Para_t.motro_count1 = CupClear0;
	  Motro_Para_t.up_flag = CupSet1;
	  Motro_Para_t.down_flag = CupClear0;
	}
	else
	{
	  Motro_Para_t.MOTRO_FLAG = CupFalse;
	  P0 &= 0Xf9;
	  P0 |= 1 << 2;
	  Motro_Para_t.motro_count0 = CupClear0;
	  Motro_Para_t.motro_count1 = CupClear0;
	  Motro_Para_t.up_flag = CupClear0;
	  Motro_Para_t.down_flag = CupSet1;
	}
}








