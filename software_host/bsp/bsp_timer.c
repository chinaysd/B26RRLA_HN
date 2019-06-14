#include "bsp_timer.h"
#include "system.h"


void Timer_Init(void)
{
	TMCON = 0X07;    //------111 ;Timer0��Tiemr1��Tiemr2ѡ��ʱ��Fsys
	
	//T0����
	TMOD |= 0x01;                 //0000 0001;Timer0���ù�����ʽ1
	TL0 = (65536 - 1000)%256;    //���ʱ�䣺ʱ��ΪFsys����24000*��1/Fsys��=2ms;
	TH0 = (65536 - 1000)/256;
	TR0 = 0;
	ET0 = 1;//��ʱ��0����
	TR0 = 1;//�򿪶�ʱ��0
	//T1����
	TMOD |= 0x20;            //0010 0000;Timer1���ù�����ʽ2
	TL1 = 256 - 240;   //���ʱ�䣺ʱ��ΪFsys����240*��1/Fsys��=20us;
	TH1 = 256 - 240;
	TR1 = 0;
	ET1 = 1;//��ʱ��1����
	TR1 = 1;//�򿪶�ʱ��1
	//T2����
	T2MOD = 0x00;
	T2CON = 0x00;	 //����Ϊ16λ���ؼĴ���
	RCAP2H = (65536-400)/256;     //���ʱ�䣺ʱ��ΪFsys����48000*��1/Fsys��=4ms;
	RCAP2L = (65536-400)%256;
	TR2 = 0;
	ET2 = 1;//��ʱ��2����
	TR2 = 1;//�򿪶�ʱ��2
}

/**************************************************
*�������ƣ�void timer0/1/2() interrupt 1/3/5
*�������ܣ���ʱ���жϲ�������
*��ڲ�����void
*���ڲ�����void
**************************************************/
void timer0() interrupt 1        //250us
{
	//static char Cnts;
    TL0 = (65536 - 1000)%256;
	TH0 = (65536 - 1000)/256;
	TimeOutDet_DecHandle();
	CupProcessHandle();
    LockHandle();
	#if 0
	++ Cnts;
	if(Cnts & 0x01)
	{
		LockRedSet(1);
	}
	else
	{
		LockRedSet(0);
	}
	#endif
}

void timer1() interrupt 3
{
	
}

void Timer2Int(void) interrupt 5       //400US
{	
	TF2 = 0;   //�������
	ErrorPwmProcessHandle();
}

















