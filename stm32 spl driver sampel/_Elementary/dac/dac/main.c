#include "stm32f10x_usart.h"
#include "bsp.h"
#include "delay.h"

int main(void)
{
	/*********************** Intial the clock and perpherals **********************/
  RCC_Configuration();
  GPIO_Configuration();
	delay_intial();
	
	DAC_Intial();
	
	 /* Set DAC Channel1 DHR12L register */
  DAC_SetChannel1Data(DAC_Align_12b_L, 0x4D90);
	
	while(1)
	{
		 /* Start DAC Channel1 conversion by software */
    //DAC_SoftwareTriggerCmd(DAC_Channel_1, ENABLE);
		//delayMs(400);
	}
	return 0;

}
