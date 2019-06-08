
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


#define RTCClockOutput_Enable  /* RTC Clock/64 is output on tamper pin(PC.13) */

void Com1_Intial(void);
void Com2_Intial(void);
void RCC_Configuration(void);
void GPIO_Configuration(void);

void RTC_Configuration(void);
void NVIC_Configuration(void);
uint32_t Time_Regulate(void);
void Time_Adjust(void);
void Time_Show(void);
void Time_Display(uint32_t TimeVar);
uint8_t USART_Scanf(uint32_t value);


