#include "bsp_pwm.h"

char count_level,count_100us_time;



void Pwm_Init(void)
{
   P0CON |= 0X01;
   P0PH  &= ~0X01;
   count_level = 15;
}

void ErrorPwmProcessHandle(void)
{
	 #if 1
     count_100us_time++;
	 if(count_100us_time > 100)
	 {
	   count_100us_time = 0;
	 }
	 if(count_100us_time >= count_level)
	 {
	   PWM_SET(0);
	 }
	 else
	 {
	   PWM_SET(1);
	 }
	 #endif
}


void PwmHandle(void)
{
	if(count_level == 15){
      count_level = 100;
	}else if(count_level == 100){
      count_level = 15;
	}
}

