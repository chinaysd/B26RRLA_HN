#ifndef _BSP_PWM_H_
#define _BSP_PWM_H_

#include "sc92f836xb_c.h"


#define  Pwm_Port    P0
#define  Pwm_Pin     P00
#define  PWM_SET(X)  ((X)?(Pwm_Pin=1):(Pwm_Pin=0))






void Pwm_Init(void);
void ErrorPwmProcessHandle(void);


#endif


