#include "stm32f10x_gpio.h"

/******************************************************************************
                      LED 
******************************************************************************/
#define LEDn                             4

#define LED1_PIN                         GPIO_Pin_2           /* PC.2*/
#define LED1_GPIO_PORT                   GPIOC
#define LED1_GPIO_CLK          					 RCC_APB2Periph_GPIOC
  
#define LED2_PIN                         GPIO_Pin_3            /* PC.3*/
#define LED2_GPIO_PORT                   GPIOC
#define LED2_GPIO_CLK										 RCC_APB2Periph_GPIOC


#define LED3_PIN                         GPIO_Pin_4            /* PC.4*/
#define LED3_GPIO_PORT                   GPIOC
#define LED3_GPIO_CLK  									 RCC_APB2Periph_GPIOC


#define LED4_PIN                         GPIO_Pin_5            /* PC.5*/
#define LED4_GPIO_PORT                   GPIOC
#define LED4_GPIO_CLK										 RCC_APB2Periph_GPIOC

void DAC_Intial(void);
void RCC_Configuration(void);
void GPIO_Configuration(void);



