#include "bsp_wdt.h"




void WDT_ENABLE(void)
{
	WDTCON |= 0x10;
}

void WDT_Feel(void)
{
	WDTCON |= 0x10;
}

void WDT_DISABLE(void)
{
	WDTCON &= 0x40;
}




