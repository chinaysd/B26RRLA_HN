#include "bsp_key.h"


extern LOCK_PARA_t Lock_Para_t;

char TX0SendData,TX1SendData;
unsigned long int MyKeyValue,KEYTempVALUE;
TIMEOUT_PARA TimeOut_Para[2];

extern char count_level;

char FootLedTempCnts,FoolLedFlag;

void RevDataFootLedOpen(void)
{
	if(count_level == 15){
      KEYTempVALUE = NON_VALUE;
	  TX0SendData = LedOpenData;	//往下发的指令
	  TX1SendData = ExtiLedOpenData;
	  FoolLedFlag = 1;
      count_level = 100;
	}
}

void RevDataFootLedClose(void)
{
	if(count_level == 100){
       KEYTempVALUE = NON_VALUE;
	   TX0SendData = LedCloseData;	//往下发的指令
	   TX1SendData = ExtiLedCloseData;
	   FoolLedFlag = 1;
	   count_level = 15;
	}
}

void KeyDataOnLineSend(void)
{
	if(TimeOutDet_Check(&TimeOut_Para[0]))
	{
		TimeOut_Record(&TimeOut_Para[0],OneLineTime);
		Uart0_ProtocolSend(0xfa,0xfb,TX0SendData);	
		Uart1_ProtocolSendData(0xfa,0xfb,TX1SendData);
	}
}

void Key_Handle(void)
{
	if(SOCAPI_TouchKeyStatus&0x80) 
	{
		SOCAPI_TouchKeyStatus &= 0x7f;
		MyKeyValue = TouchKeyScan();
		switch (MyKeyValue)
		{
			case TK1_VALUE:
				if((KEYTempVALUE != TK1_VALUE)&&(Lock_Para_t.LockFlag)){
                  KEYTempVALUE = TK1_VALUE;
				  FoolLedFlag = 1;
				  ++ FootLedTempCnts;
				  if(FootLedTempCnts & 0x01){
				  	if(15 == count_level){
                       TX0SendData = LedOpenData;
					   TX1SendData = ExtiLedOpenData;
					   count_level = 100;
					}
				  }
				  else{
				  	if(100 == count_level){
                       TX0SendData = LedCloseData;
					   TX1SendData = ExtiLedCloseData;
					   count_level = 15;
					}
				  }
				}
				
				break;
			case TK2_VALUE:
				if((KEYTempVALUE != TK2_VALUE)&&(Lock_Para_t.LockFlag)){
                  KEYTempVALUE = TK2_VALUE;
				  CupHandle();
				}
				break;
			case TK3_VALUE:
				if((KEYTempVALUE != TK3_VALUE)&&(Lock_Para_t.LockFlag)){
				  KEYTempVALUE = TK3_VALUE;
				  TX0SendData = HeadUpData;
				  FoolLedFlag = 0;
				}
				break;
			case TK4_VALUE:
				if((KEYTempVALUE != TK4_VALUE)&&(Lock_Para_t.LockFlag)){
				  KEYTempVALUE = TK4_VALUE;
				  TX0SendData = HomeData;
				  FoolLedFlag = 0;
				}
				break;
			case TK5_VALUE:
				if(KEYTempVALUE != TK5_VALUE){
				  KEYTempVALUE = TK5_VALUE;
				  //TX0SendData = 0x10;
				}
				break;
			case TK6_VALUE:
				if((KEYTempVALUE != TK6_VALUE)&&(Lock_Para_t.LockFlag)){
				  KEYTempVALUE = TK6_VALUE;
				  TX0SendData = OpenData;
				  FoolLedFlag = 0;
				}
				break;
			case TK7_VALUE:
				if((KEYTempVALUE != TK7_VALUE)&&(Lock_Para_t.LockFlag)){
				  KEYTempVALUE = TK7_VALUE;
				  TX0SendData = CloseData;
				  FoolLedFlag = 0;
				}
				break;
			case TK8_VALUE:
				if((KEYTempVALUE != TK8_VALUE)&&(Lock_Para_t.LockFlag)){
				  KEYTempVALUE = TK8_VALUE;
				  TX0SendData = HeadDownData;
				  FoolLedFlag = 0;
				}
				break;
				#if 0
			case 0X0100:
				break;
			case 0X0200:
				break;
				#endif
			default:
				if(KEYTempVALUE != NON_VALUE){
				  KEYTempVALUE = NON_VALUE;
				  if(!FoolLedFlag){
                     TX0SendData = NoData;
				  }
				}
				break;
		}
		TouchKeyRestart();// 启动下一轮转换
	}
	if(KEYTempVALUE == NON_VALUE){
       RevDataHandle();
	}
	KeyDataOnLineSend();
}






