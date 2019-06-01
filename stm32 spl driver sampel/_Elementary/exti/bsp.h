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



																 
typedef enum 
{
  LED1 = 0,
  LED2 = 1,
  LED3 = 2,
  LED4 = 3
} Led_TypeDef;


void STM_EVAL_LEDInit(Led_TypeDef Led);
void STM_EVAL_LEDOn(Led_TypeDef Led);
void STM_EVAL_LEDOff(Led_TypeDef Led);
void STM_EVAL_LEDToggle(Led_TypeDef Led);


void EXTI9_5_Config(void);




