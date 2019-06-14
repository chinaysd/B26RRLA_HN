#include "bsp_interrupt.h"


char Interrupt_Handle(char Interrupt_Status)
{
	if(Interrupt_Status > Interrupt_Enable){
    return Interrupt_Default;
	}else if(Interrupt_Status == Interrupt_Enable){
	EA = Interrupt_Open;
    return Interrupt_Open;
	}else if(Interrupt_Status == Interrupt_Disable){
	EA = Interrupt_Close;
    return Interrupt_Close;
	}
}






