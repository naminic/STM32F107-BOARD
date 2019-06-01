#include "stm32f10x_gpio.h"
#include "bsp.h"
#include "delay.h"

GPIO_InitTypeDef GPIO_InitStructure;

void setAllLed(void);
void resetAllLed(void);

int main(void)
{
	
	delay_intial();
	
	/************************************************** Configure the clock and GPIO ***************************************** */
	/* ALL LED Port Periph clock enable */
  RCC_APB2PeriphClockCmd(LED1_GPIO_CLK | LED2_GPIO_CLK | LED3_GPIO_CLK | LED4_GPIO_CLK, ENABLE);

  /* Configure LED1 in output pushpull mode */
  GPIO_InitStructure.GPIO_Pin = LED1_PIN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(LED1_GPIO_PORT, &GPIO_InitStructure);
	
	 /* Configure LED2 in output pushpull mode */
  GPIO_InitStructure.GPIO_Pin = LED2_PIN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(LED2_GPIO_PORT, &GPIO_InitStructure);

	 /* Configure LED3 in output pushpull mode */
  GPIO_InitStructure.GPIO_Pin = LED3_PIN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(LED3_GPIO_PORT, &GPIO_InitStructure);
	
		 /* Configure LED4 in output pushpull mode */
  GPIO_InitStructure.GPIO_Pin = LED4_PIN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(LED4_GPIO_PORT, &GPIO_InitStructure);
		/************************************************** Start to toggle leds ***************************************** */
	GPIO_SetBits(LED1_GPIO_PORT,LED1_PIN);
	delayMs(200);	
	GPIO_SetBits(LED2_GPIO_PORT,LED2_PIN);
	delayMs(200);	
	GPIO_SetBits(LED3_GPIO_PORT,LED3_PIN);
	delayMs(200);	
	GPIO_SetBits(LED4_GPIO_PORT,LED4_PIN);
	delayMs(200);	
	
	resetAllLed();
	delayMs(200);	
	
	GPIO_SetBits(LED4_GPIO_PORT,LED4_PIN);
	delayMs(200);			
	GPIO_SetBits(LED3_GPIO_PORT,LED3_PIN);
	delayMs(200);	
	GPIO_SetBits(LED2_GPIO_PORT,LED2_PIN);
	delayMs(200);	
	GPIO_SetBits(LED1_GPIO_PORT,LED1_PIN);
	delayMs(200);	
	while(1)
	{	
		setAllLed();	
	   delayMs(200);	
		resetAllLed();
	   delayMs(200);	
	}	

	return 0;	
}

/**
  * @brief  This function sets and resets all leds.
  * @param  None
  * @retval None
  */
void setAllLed(void)
{
	GPIO_SetBits(LED1_GPIO_PORT,LED1_PIN);
	GPIO_SetBits(LED2_GPIO_PORT,LED2_PIN);
	GPIO_SetBits(LED3_GPIO_PORT,LED3_PIN);
	GPIO_SetBits(LED4_GPIO_PORT,LED4_PIN);
}

void resetAllLed(void)
{
	GPIO_ResetBits(LED1_GPIO_PORT,LED1_PIN);
	GPIO_ResetBits(LED2_GPIO_PORT,LED2_PIN);
	GPIO_ResetBits(LED3_GPIO_PORT,LED3_PIN);
	GPIO_ResetBits(LED4_GPIO_PORT,LED4_PIN);
}