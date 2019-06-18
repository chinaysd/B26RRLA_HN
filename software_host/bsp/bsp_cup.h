#ifndef _BSP_CUP_H_
#define _BSP_CUP_H_

#include "sc92f836xb_c.h"


#define CupFalse       0
#define CupTrue        1

#define CupClear0      0
#define CupSet1        1

#define CupTimeCnts    800

typedef struct
{
	char MOTRO_FLAG;
	unsigned int motro_count0;
    unsigned int motro_count1;
	char up_flag;
	char down_flag;
}
MOTRO_PARA_T;











void Cup_Init(void);
void CupHandle(void);
void CupProcessHandle(void);

#endif

