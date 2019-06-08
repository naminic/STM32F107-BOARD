#include "bsp.h"
#include "stm32f10x_usart.h"
#include <stdio.h>
/******************************************************************************
                               Initial RCC
  * @brief  Configures different system clocks.
  * @param  None
  * @retval None
******************************************************************************/
void RCC_Configuration(){
  /* Setup the micro controller system. Initialize the Embedded Flash Interface,  
     initialize the PLL and update the SystemFrequency variable. */
  SystemInit();

/* Enable peripheral clocks --------------------------------------------------*/
  /* GPIOA Periph clock enable */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
  /* DAC Periph clock enable */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE);
}

/******************************************************************************
                                  Initial GPIO
  * @brief  Configure GPIO Pins.
  * @param  None
  * @retval None
******************************************************************************/
void GPIO_Configuration(void){
	 GPIO_InitTypeDef GPIO_InitStructure;

  /* Once the DAC channel is enabled, the corresponding GPIO pin is automatically 
     connected to the DAC converter. In order to avoid parasitic consumption, 
     the GPIO pin should be configured in analog */
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_4;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
}

/******************************************************************************
                                  Initial DAC
  * @brief  Configure DAC Peripheral.
  * @param  None
  * @retval None
******************************************************************************/
void DAC_Intial(void){
	DAC_InitTypeDef            DAC_InitStructure;
	 /* DAC channel1 Configuration */
  DAC_InitStructure.DAC_Trigger = DAC_Trigger_Software;
  DAC_InitStructure.DAC_WaveGeneration = DAC_WaveGeneration_None;
  DAC_InitStructure.DAC_LFSRUnmask_TriangleAmplitude = DAC_LFSRUnmask_Bits8_0;
  DAC_InitStructure.DAC_OutputBuffer = DAC_OutputBuffer_Enable;
  DAC_Init(DAC_Channel_1, &DAC_InitStructure);

  /* Enable DAC Channel1: Once the DAC channel1 is enabled, PA.04 is 
     automatically connected to the DAC converter. */
  DAC_Cmd(DAC_Channel_1, ENABLE);

}