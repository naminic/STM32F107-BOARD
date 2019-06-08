#include "stm32f10x_usart.h"
#include <stdio.h>
#include "bsp.h"
#include "delay.h"

//printf init
struct __FILE { int handle;} ;

FILE __stdout;
FILE __stdin;
FILE __stderr;

int fputc(int ch, FILE *f)  
{
	while(!USART_GetFlagStatus(COM1,USART_FLAG_TXE));	 
														 
	USART_SendData(COM1,ch);	

	while(!USART_GetFlagStatus(COM2,USART_FLAG_TXE));	 
														 
	USART_SendData(COM2,ch);	
	   
	return ch;	
}
  

int main(void)
{
	/*********************** Intial the clock and perpherals **********************/
  RCC_Configuration();
  GPIO_Configuration();
  Com1_Intial();  //usb to serial 
	Com2_Intial();  //COM PORT (Rs232)
	
	ADC1_Intial();
	
	delay_intial();
	
  printf("Naminic STM32 evaluation board\n\n\n");
	while(1)
	{
		printf("adc get val = %d\n\r",getVal());
		delayMs(400);
	}
	return 0;
	
	
}


