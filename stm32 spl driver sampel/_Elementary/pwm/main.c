#include "stm32f10x.h"
#include "bsp.h"


int main(void)
{
  RCC_Configuration();
  GPIO_Configuration();	
  PWM_Intial();
	
  while (1)
  {		
		
	}
			
}
