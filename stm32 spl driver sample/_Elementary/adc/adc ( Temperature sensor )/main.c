#include "stm32f10x_usart.h"
#include <stdio.h>
#include "bsp.h"
#include "delay.h"


uint16_t AD_value;
const uint16_t V25 = 1750;// when V25=1.41V at ref 3.3V
const uint16_t Avg_Slope = 5; //when avg_slope=4.3mV/C at ref 3.3V
uint16_t TemperatureC;

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
  Com1_Intial();  //usb to serial 
	Com2_Intial();  //COM PORT
	
	T_Adc_Init();
	
	delay_intial();
	
  printf("Naminic STM32 evaluation board\n\n\n");
	
	while(1)
	{
		AD_value=T_Get_Temp();
	  TemperatureC = (uint16_t)((V25-AD_value)/Avg_Slope+25);
		printf("\r\n ADC value: %d \r\n", AD_value);
    printf("Temperature: %d%cC\r\n", TemperatureC, 176);
		delayMs(1000);
	}
	return 0;
}

