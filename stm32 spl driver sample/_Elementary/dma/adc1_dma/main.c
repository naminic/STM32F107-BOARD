#include <stdio.h>
#include "delay.h"
#include "bsp.h"
extern  uint16_t ADCConvertedValue ;

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
	RCC_Configuration();
	GPIO_Configuration();
	Com1_Intial();
	Com2_Intial();
	dma_init();
	ADC1_Intial();
	delay_intial();
	printf("Naminic STM32 evaluation board\n\n\n");
while(1)
{
  printf("adc1 value = %d\n\r",ADCConvertedValue);
	delayMs(200);
}
 return 0;

}
