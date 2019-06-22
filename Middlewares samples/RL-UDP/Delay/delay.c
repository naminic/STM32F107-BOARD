#include "delay.h"

/*********************************************************************
* @brief
* @param[in]
* @return
*********************************************************************/
void delayMs(unsigned int MiliSec)
{
	unsigned int i = 0;
	unsigned int j = 0;
	for(i = 0 ; i <= 10000 ; i++)
		for(j = 0 ; j <= MiliSec ; j++);
}
