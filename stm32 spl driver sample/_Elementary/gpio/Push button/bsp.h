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

/******************************************************************************
                      KEY  
******************************************************************************/

#define KEY1_PIN                         GPIO_Pin_6          /* PC.6*/
#define KEY1_GPIO_PORT                   GPIOC
#define KEY1_GPIO_CLK          					 RCC_APB2Periph_GPIOC
  
#define KEY2_PIN                         GPIO_Pin_7            /* PC.7*/
#define KEY2_GPIO_PORT                   GPIOC
#define KEY2_GPIO_CLK   							   RCC_APB2Periph_GPIOC


#define KEY3_PIN                        GPIO_Pin_8            /* PC.8*/
#define KEY3_GPIO_PORT                  GPIOC
#define KEY3_GPIO_CLK   							  RCC_APB2Periph_GPIOC


#define KEY4_PIN                        GPIO_Pin_9            /* PC.9*/
#define KEY4_GPIO_PORT                  GPIOC
#define KEY4_GPIO_CLK   					  		RCC_APB2Periph_GPIOC


