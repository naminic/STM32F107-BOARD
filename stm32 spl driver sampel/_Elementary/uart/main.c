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
	 uint16_t i;   //counter variable to send 
	/*********************** Intial the clock and perpherals **********************/
  RCC_Configuration();
  GPIO_Configuration();
  Com1_Intial();  //usb to serial 
  Com2_Intial();  //COM PORT
  
  delay_intial();
	
  printf("Naminic STM32 evaluation board\n");
	
	while(1)
	{
		i++;
		printf("The Number is :%d\r\n",i);
    delayMs(500);
	}
	return 0;
}





