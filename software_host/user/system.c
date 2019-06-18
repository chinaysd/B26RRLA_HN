#include "system.h"


void TK_Init(void)//触摸按键设置强推挽输出
{
	P0CON |= 0X31;
	P0PH  &= ~0X31;
	P0 = 0X31;
	P2CON |= 0XD3;
	P2PH  &= ~0XD3;
	P2 = 0XD3;
	P1CON |= 0X30;
	P1PH  &= ~0X30;
	P1 = 0X30;
}


void System_Init(void)
{
	WDT_DISABLE();
	TimeOutDet_Init();
	LockRedInit();
	Cup_Init();
	TK_Init();
	Pwm_Init();
	Timer_Init();
	Uart_Init(Freq_6M,Baud_9600);
	Uart1_Init(Freq_6M,Baud_9600);
	TouchKeyInit();
	WDT_ENABLE();
	Interrupt_Handle(Interrupt_Enable);
}

void System_Handle(void)
{
    WDT_Feel();
	Key_Handle();
}



