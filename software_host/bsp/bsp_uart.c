#include "bsp_uart.h"

bit UartSendFlag = 0; //�����жϱ�־λ
bit UartReceiveFlag = 0; //�����жϱ�־λ
bit Uart1SendFlag;
bit Uart1ReceiveFlag;

static unsigned int RevMyDataValue;

void Uart_Init(char Freq,unsigned int baud)
{
	P1CON &= 0xF3;   //TX/RX����Ϊ���������
	P1PH  |= 0x0C;
	
	SCON  |= 0X50;   //����ͨ�ŷ�ʽΪģʽһ���������
	TMCON |= 0X02;
	TMOD  |= 0X20;
	PCON  |= 0X80;	//SMOD=1
	TH1 = (Freq*1000000/baud)>>8;	  //������ΪT1�����ʱ�䣻
	TL1 = Freq*1000000/baud;
	TR1 = 0;
	ET1 = 0;	
	EUART = 1;     //����Uart0�ж�
}

void Uart1_Init(char Uart1_Freq,unsigned int Uart1_Baud)
{
	P2CON &= 0xFC;   //TX/RX����Ϊ���������
	P2PH  |= 0x03;
	OTCON = 0xC0;    //���нӿ�SSIѡ��Uart1ͨ��
	SSCON0 = 0x50;   //����ͨ�ŷ�ʽΪģʽһ���������
	SSCON1 = Uart1_Freq*1000000/Uart1_Baud;   //�����ʵ�λ����
	SSCON2 = (Uart1_Freq*1000000/Uart1_Baud)>>8;   //�����ʸ�λ����
	IE1 = 0x01;      //����SSI�ж�
}


/***********************************����0������***************************************************/
static void UART0_TX_byte(unsigned char Test1Data)
{
   SBUF = Test1Data;
   while(!UartSendFlag);
   UartSendFlag = 0;
}

static unsigned char Uart0_SendData(UART0_PROTOCOL_TX *p)
{
	static unsigned char i;
	for(i = 0; i < UART0_BUF_SIZE;i ++)
	{
		UART0_TX_byte(p->Uart0_Buf[i]);
	}
	return 0;
}

unsigned char Uart0_ProtocolSend(unsigned char addr1,unsigned char id1,unsigned int uart0data)
{
	UART0_PROTOCOL_TX Uart0_buf;
	memset(&Uart0_buf,0,sizeof(Uart0_buf));
	Uart0_buf.Uart0_Format.ADDR1 = addr1;
	Uart0_buf.Uart0_Format.ID1      = id1; 
	Uart0_buf.Uart0_Format.DATA1  = UART0_Hight(uart0data);
	Uart0_buf.Uart0_Format.DATA2  = UART0_Low(uart0data);
	Uart0_buf.Uart0_Format.CHECKSUM1 = (unsigned char)(Uart0_buf.Uart0_Format.ADDR1+Uart0_buf.Uart0_Format.ID1+Uart0_buf.Uart0_Format.DATA1+Uart0_buf.Uart0_Format.DATA2);
	Uart0_buf.Uart0_Format.STOP1 = 0x0d;
	Uart0_buf.Uart0_Format.STOP2 = 0x0a;
	return Uart0_SendData(&Uart0_buf);
}
/***********************************����0������***************************************************/

/***********************************����1������***************************************************/

static void Uart1_SendByte(char SendByte)
{
	SSDAT = SendByte;
	while(!Uart1SendFlag);
	Uart1SendFlag = 0;
}

static char Uart1_SendData(UART1_PROTOCOL_TX *p)
{
	static char i;
	for(i = 0; i < UART1_BUF_SIZE; i ++)
	{
		Uart1_SendByte(p->Uart1_Buf[i]);
	}
	return 0;
}

unsigned char Uart1_ProtocolSendData(unsigned char TX1_ADDR,unsigned char TX1_ID,unsigned int TX1_DATA)
{
	UART1_PROTOCOL_TX Uart1_buf;
	memset(&Uart1_buf,0,sizeof(Uart1_buf));
	Uart1_buf.Uart1_Format.UART1_ADDR = TX1_ADDR;
	Uart1_buf.Uart1_Format.UART1_ID = TX1_ID;
	Uart1_buf.Uart1_Format.UART1_DATA1 = UART1_Hight(TX1_DATA);
	Uart1_buf.Uart1_Format.UART1_DATA2 = UART1_Low(TX1_DATA);
	Uart1_buf.Uart1_Format.UART1_CHECKSUM = (unsigned char)(Uart1_buf.Uart1_Format.UART1_ADDR+Uart1_buf.Uart1_Format.UART1_ID+Uart1_buf.Uart1_Format.UART1_DATA1+Uart1_buf.Uart1_Format.UART1_DATA2);
	Uart1_buf.Uart1_Format.UART1_STOP1 = 0x0d;
	Uart1_buf.Uart1_Format.UART1_STOP2 = 0x0a;
	return Uart1_SendData(&Uart1_buf);
}
/***********************************����1������***************************************************/

/***********************************����1���մ�����***************************************************/
unsigned char Rev_Num,Rev_Sum,Rev_Data,Rev_String[UART1_REVBUF_SIZE];

static char IfRevSuccess(void)
{
	if(Rev_Num & 0x80)
	{
		Rev_Num = 0x00;
		return 1;
	}
	else
	{
		return 0;
	}
}

static char Rev_Byte(void)
{
	static char RevTempByte;
	while(!Uart1ReceiveFlag);
	Uart1ReceiveFlag = 0;
	RevTempByte = SSDAT;
	return RevTempByte;
}

static void RevProcessHandle(void)
{
	Rev_Data = Rev_Byte();
	if((Rev_Num & 0x80) == 0x00)
	{
		if(Rev_Num == 0x40)
		{
			if(Rev_Data == 0x0a)
			{
				Rev_Num = 0x80;
			}
			else
			{
				Rev_Num = 0x00;
			}
		}
		else
		{
           if(Rev_Data == 0x0d)
           {
              Rev_Num = 0x40;
		   }
		   else
		   {
		   	  Rev_String[Rev_Num] = Rev_Data;
			  Rev_Num ++;
			  if(Rev_String[0] != 0xfa)
			  {
			  	Rev_Num = 0;
			  }
			  #if 1
			  if(Rev_Num > UART1_REVBUF_SIZE)
			  {
			  	Rev_Num = 0;
			  }
			  #endif
		   }
		}
	}
}

void RevDataHandle(void)
{
	if(IfRevSuccess())
	{
		RevMyDataValue = (unsigned int)Get32Bit(Rev_String[2],Rev_String[3]);
		memset(&Rev_String,0,sizeof(Rev_String));
		switch (RevMyDataValue)
		{
			case ExtiLedOpenData:
				RevDataFootLedOpen();
				break;
			case ExtiLedCloseData:
				RevDataFootLedClose();
				break;
			default:
				
				break;
		}
	}
}
/***********************************����1���մ�����***************************************************/




/*****************************************************
*�������ƣ�void UartInt(void) interrupt 4
*�������ܣ�Uart0�жϺ���
*��ڲ�����void
*���ڲ�����void
*****************************************************/
void UartInt(void) interrupt 4
{
	if(TI)
	{
		TI = 0;	
		UartSendFlag = 1;		
	}
	if(RI)
	{
		RI = 0;	
		UartReceiveFlag = 1;
	}	
}

/******************************************************************************
*����:PETER
*����:190308
*����:����1�жϴ�����
*����:��
*******************************************************************************/
void Uart1_Int() interrupt 7   //Uart1�жϺ���
{
	if(SSCON0&0x02)    //���ͱ�־λ�ж�
	{
		SSCON0 &= 0xFD;
		Uart1SendFlag = 1;
	}
	if((SSCON0&0x01))  //���ձ�־λ�ж�
	{
		SSCON0 &= 0xFE;
		Uart1ReceiveFlag = 1;
		RevProcessHandle();
	}
}






