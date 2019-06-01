#ifndef __DELAY_H
#define __DELAY_H

#include "stm32f10x.h"


void delay_intial(void);
void delayMs(__IO uint32_t nTime);
void TimingDelay_Decrement(void);
void SysTick_Handler(void);


#endif