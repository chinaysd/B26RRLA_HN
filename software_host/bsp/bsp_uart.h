

#ifndef _BSP_UART_H_
#define _BSP_UART_H_

#include "sc92f836xb_c.h"
#include "string.h"
#include "bsp_key.h"

#define  Freq_6M           6
#define  Baud_9600         9600

/***************************串口0变量的定义*********************************/
#define UART0_BUF_SIZE     7
#define UART0_Hight(x)       ((x>>8)&0xff)
#define UART0_Low(x)         ((x)&0xff)

typedef struct
{
	unsigned char ADDR1;
	unsigned char ID1;
	unsigned char DATA1;
	unsigned char DATA2;
	unsigned char CHECKSUM1;
	unsigned char STOP1;
	unsigned char STOP2;
}
UART0_FORMAT_TX;

typedef union
{
	unsigned char Uart0_Buf[UART0_BUF_SIZE];
	UART0_FORMAT_TX Uart0_Format;
}
UART0_PROTOCOL_TX;
/***************************串口0变量的定义*********************************/

/***************************串口1变量的定义*********************************/

#define UART1_BUF_SIZE       7
#define UART1_Hight(x)       (((x)>>8)&0xff)
#define UART1_Low(x)         ((x)&0xff)


typedef struct
{
	unsigned char UART1_ADDR;
	unsigned char UART1_ID;
	unsigned char UART1_DATA1;
	unsigned char UART1_DATA2;
	unsigned char UART1_CHECKSUM;
	unsigned char UART1_STOP1;
	unsigned char UART1_STOP2;
}
UART1_FORMAT_TX;

typedef union
{
    unsigned char Uart1_Buf[UART1_BUF_SIZE];
    UART1_FORMAT_TX Uart1_Format;
}
UART1_PROTOCOL_TX;


/***************************串口1变量的定义*********************************/
#define UART1_REVBUF_SIZE       7
#define Get32Bit(x,y)          (((x<<8)|y)&0xffff)



void Uart_Init(char Freq,unsigned int baud);
void Uart1_Init(char Uart1_Freq,unsigned int Uart1_Baud);
unsigned char Uart0_ProtocolSend(unsigned char addr1,unsigned char id1,unsigned int uart0data);
unsigned char Uart1_ProtocolSendData(unsigned char TX1_ADDR,unsigned char TX1_ID,unsigned int TX1_DATA);


void RevDataHandle(void);


#endif

