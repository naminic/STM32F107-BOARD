/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "bsp.h"

/* Private functions ---------------------------------------------------------*/
/**
  * @brief   Main program
  * @param  None
  * @retval None
  */
int main(void)
{
  /* System clocks configuration ---------------------------------------------*/
  RCC_Configuration();

  /* NVIC configuration ------------------------------------------------------*/
  NVIC_Configuration();

  /* GPIO configuration ------------------------------------------------------*/
  GPIO_Configuration();

  /* Configure LED GPIO Pin ------------------------------------------------- */
  STM_EVAL_LEDInit(LED1);
  
	/* Configure ADC  ------------------------------------------------- */
  ADC_AnalogWatchdog_Intial();

  while (1)
  {
  }
}
