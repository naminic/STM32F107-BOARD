#include "stm32f10x_it.h"
#include "bsp.h"

/******************************************************************************/
/*            STM32F10x Peripherals Interrupt Handlers                        */
/******************************************************************************/

/**
  * @brief  This function handles ADC1 and ADC2 global interrupts requests.
  * @param  None
  * @retval None
  */

void ADC1_2_IRQHandler(void)

{
  /* Toggle LED1 */
  STM_EVAL_LEDOn(LED1);
  STM_EVAL_LEDOff(LED1);
  /* Clear ADC1 AWD pending interrupt bit */
  ADC_ClearITPendingBit(ADC1, ADC_IT_AWD);
}

