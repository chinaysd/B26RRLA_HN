#include "system.h"


void System_Init(void)
{
	WDT_DISABLE();
	TimeOutDet_Init();
	LockRedInit();
	Cup_Init();
	Pwm_Init();
	Timer_Init();
	Uart_Init(Freq_2M,Baud_9600);
	Uart1_Init(Freq_2M,Baud_9600);
	TouchKeyInit();
	WDT_ENABLE();
	Interrupt_Handle(Interrupt_Enable);
}

void System_Handle(void)
{
    WDT_Feel();
	Key_Handle();
}



