#include "stm32f10x.h"
#include "bsp.h"

/**
  * @brief   Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
  /* System Clocks Configuration */
  RCC_Configuration();   

  /* Once the DAC channel is enabled, the corresponding GPIO pin is automatically 
     connected to the DAC converter. In order to avoid parasitic consumption, 
     the GPIO pin should be configured in analog */
  GPIO_Configuration();
  DAC_Configuration();
  TIM_Configuration();
	DMA_Configuration();

  /* Enable DAC Channel1: Once the DAC channel1 is enabled, PA.04 is 
     automatically connected to the DAC converter. */
  DAC_Cmd(DAC_Channel_1, ENABLE);

  /* Enable DMA for DAC Channel2 */
  DAC_DMACmd(DAC_Channel_2, ENABLE);

  /* TIM2 enable counter */
  TIM_Cmd(TIM2, ENABLE);

  while (1)
  {
  }
}
