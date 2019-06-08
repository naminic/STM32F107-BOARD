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

