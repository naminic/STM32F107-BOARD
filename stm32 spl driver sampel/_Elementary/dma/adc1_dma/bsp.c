#include "stm32f10x_usart.h"
#include <stdio.h>
#include "bsp.h"

 uint16_t ADCConvertedValue = 0;
/******************************************************************************
            Initial RCC
  * @brief  Configures different system clocks
  * @param  None
  * @retval None                           
******************************************************************************/
void RCC_Configuration(){
	RCC_APB2PeriphClockCmd(COM1_CLK_PORT|RCC_APB2Periph_AFIO,ENABLE);
	RCC_APB2PeriphClockCmd(COM1_CLK,ENABLE);
	
	RCC_APB2PeriphClockCmd(COM2_CLK_PORT|RCC_APB2Periph_AFIO,ENABLE);
	RCC_APB1PeriphClockCmd(COM2_CLK,ENABLE);
  
	  //Variable used to setup the GPIO pins
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1 | RCC_APB2Periph_GPIOB, ENABLE);
	  /* PCLK2 is the APB2 clock */
  /* ADCCLK = PCLK2/6 = 72/6 = 12MHz*/
  RCC_ADCCLKConfig(RCC_PCLK2_Div4);

  /* Enable ADC1 clock so that we can talk to it */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
  /* Put everything back to power-on defaults */
}
/******************************************************************************
           Initial GPIO
  * @brief  Configure GPIO Pins
  * @param  None
  * @retval None
******************************************************************************/
void GPIO_Configuration(void){
	
  GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_PinRemapConfig(COM2_Remap,ENABLE);
	GPIO_PinRemapConfig(COM1_Remap,ENABLE);
	
	GPIO_InitStruct.GPIO_Pin = COM1_TXD_PIN;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;	
	GPIO_Init(COM1_PORT,&GPIO_InitStruct); //TX1	
  
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
  GPIO_Init(GPIOB, &GPIO_InitStruct);
	GPIO_InitStruct.GPIO_Pin = COM1_RXD_PIN;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;	
	GPIO_Init(COM1_PORT,&GPIO_InitStruct); //RX1
	
	GPIO_InitStruct.GPIO_Pin = COM2_TXD_PIN;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;	
	GPIO_Init(COM2_PORT,&GPIO_InitStruct); //TX2	

	GPIO_InitStruct.GPIO_Pin = COM2_RXD_PIN;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;	
	GPIO_Init(COM2_PORT,&GPIO_InitStruct); //RX2
	//----------------------------------------------------		
}
/******************************************************************************
           Initial UART1
  * @brief  Configure UART1
  * @param  None
  * @retval None
******************************************************************************/
void Com1_Intial(void){
	USART_InitTypeDef USART_InitStructure;
  USART_InitStructure.USART_BaudRate = 9600;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(COM1,&USART_InitStructure);
	USART_Cmd(COM1,ENABLE);
}
/******************************************************************************
          Intial UART2
******************************************************************************/
void Com2_Intial(void){
	USART_InitTypeDef USART_InitStructure;
  USART_InitStructure.USART_BaudRate = 9600;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(COM2,&USART_InitStructure);
	USART_Cmd(COM2,ENABLE);
}

/******************************************************************************
           Initial ADC
  * @brief  Configure ADC
  * @param  None
  * @retval None
******************************************************************************/
void ADC1_Intial(void){
	ADC_InitTypeDef  ADC_InitStructure;
  /* Put everything back to power-on defaults */
  ADC_DeInit(ADC1);

  /* ADC1 configuration ------------------------------------------------------*/
  ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
  ADC_InitStructure.ADC_ScanConvMode = ENABLE;
  ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
  ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
  ADC_InitStructure.ADC_NbrOfChannel = 1;
  ADC_Init(ADC1, &ADC_InitStructure);

  /* ADC1 regular channel14 configuration */ 
  ADC_RegularChannelConfig(ADC1, ADC1_IN8,1 , ADC_SampleTime_55Cycles5);

  /* Enable ADC1 DMA */
  ADC_DMACmd(ADC1, ENABLE);
  
  /* Enable ADC1 */
  ADC_Cmd(ADC1, ENABLE);

  /* Enable ADC1 reset calibration register */   
  ADC_ResetCalibration(ADC1);
  /* Check the end of ADC1 reset calibration register */
  while(ADC_GetResetCalibrationStatus(ADC1));

  /* Start ADC1 calibration */
  ADC_StartCalibration(ADC1);
  /* Check the end of ADC1 calibration */
  while(ADC_GetCalibrationStatus(ADC1));
     
  /* Start ADC1 Software Conversion */ 
  ADC_SoftwareStartConvCmd(ADC1, ENABLE);	
 		

}
  /******************************************************************************
          initial DMA 
  * @brief  Configure DMA
  * @param  None
  * @retval None
******************************************************************************/
void dma_init(void)
{
	
	DMA_InitTypeDef DMA_InitStructure;
	
	RCC_AHBPeriphClockCmd(DMA_CLK, ENABLE);
	
	/* DMA1 channel1 configuration ----------------------------------------------*/
  DMA_DeInit(DMA1_Channel1);
  DMA_InitStructure.DMA_PeripheralBaseAddr = ADC1_DR_Address;
  DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)&ADCConvertedValue;
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
  DMA_InitStructure.DMA_BufferSize = 1;
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Disable;
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
  DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
  DMA_InitStructure.DMA_Priority = DMA_Priority_High;
  DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
  DMA_Init(DMA1_Channel1, &DMA_InitStructure);
  
  /* Enable DMA1 channel1 */
  DMA_Cmd(DMA1_Channel1, ENABLE);

}

