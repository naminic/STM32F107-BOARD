
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
                            ADC 
******************************************************************************/

#define ADC1_IN8				8
#define ADC_CLK         RCC_APB2Periph_ADC1
#define ADC_GPIO				GPIO_Pin_0
#define ADC_GPIO_RCC		RCC_APB2Periph_GPIOB
#define ADC_PORT        GPIOB
/******************************************************************************
               SERIAL TO USB AND COMPORT
******************************************************************************/

#define COM1             USART1
#define COM1_CLK				 RCC_APB2Periph_USART1
#define COM1_TXD_PIN		 GPIO_Pin_6
#define COM1_RXD_PIN     GPIO_Pin_7
#define COM1_CLK_PORT	   RCC_APB2Periph_GPIOB

#define COM1_PORT        GPIOB
#define COM1_Remap       GPIO_Remap_USART1
//---------------------------------------------------------
#define COM2             USART2
#define COM2_CLK				 RCC_APB1Periph_USART2
#define COM2_TXD_PIN		 GPIO_Pin_5
#define COM2_RXD_PIN     GPIO_Pin_6
#define COM2_CLK_PORT	   RCC_APB2Periph_GPIOD

#define COM2_PORT        GPIOD
#define COM2_Remap       GPIO_Remap_USART2




void T_Adc_Init(void);
u16 T_Get_Adc(u8 ch) ;
u16 T_Get_Temp(void);
u16 T_Get_Adc_Average(u8 ch,u8 times);


void Com1_Intial(void);
void Com2_Intial(void);
void ADC1_Intial(void);
unsigned int getVal(void);
void RCC_Configuration(void);
void GPIO_Configuration(void);



