#include "bsp.h"
#include "stm32f10x_usart.h"
#include <stdio.h>
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
           Initial UART2
  * @brief  Configure UART2
  * @param  None
  * @retval None
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
  GPIO_InitTypeDef GPIO_InitStructure; 	
	
  //Variable used to setup the GPIO pins
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1 | RCC_APB2Periph_GPIOC, ENABLE);
	
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
  GPIO_Init(GPIOC, &GPIO_InitStructure);
	
  /* PCLK2 is the APB2 clock */
  /* ADCCLK = PCLK2/6 = 72/6 = 12MHz*/
  RCC_ADCCLKConfig(RCC_PCLK2_Div6);

  /* Enable ADC1 clock so that we can talk to it */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
  /* Put everything back to power-on defaults */
  ADC_DeInit(ADC1);

  /* ADC1 Configuration ------------------------------------------------------*/
  /* ADC1 and ADC2 operate independently */
  ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
  /* Disable the scan conversion so we do one at a time */
  ADC_InitStructure.ADC_ScanConvMode = DISABLE;
  /* Don't do continuous conversions - do them on demand */
  ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
  /* Start conversion by software, not an external trigger */
  ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
  /* Conversions are 12 bit - put them in the lower 12 bits of the result */
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
  /* Say how many channels would be used by the sequencer */
  ADC_InitStructure.ADC_NbrOfChannel = 1;

  /* Now do the setup */
  ADC_Init(ADC1, &ADC_InitStructure);
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

}

  /******************************************************************************
           Get ADC value
  * @brief  This function Converts to Digital and get the value
  * @param  None
  * @retval None
******************************************************************************/
unsigned int getTemp(void)
{	
  unsigned int temp,val;
	ADC_RegularChannelConfig(ADC1, ADC1_IN10, 1, ADC_SampleTime_1Cycles5);
  // Start the conversion
  ADC_SoftwareStartConvCmd(ADC1, ENABLE);
  // Wait until conversion completion
  while(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET);
  // Get the conversion value
	val=ADC_GetConversionValue(ADC1);
	temp=(0.01/3.33)*4095;
	temp=(val/temp)/2;
	temp=temp-2;
  return temp;
}