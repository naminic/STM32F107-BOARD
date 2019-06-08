/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h"
#include "bsp.h"
#include "delay.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/


/******************************************************************************/
/*            STM32F10x Peripherals Interrupt Handlers                        */
/******************************************************************************/


/**
  * @brief  This function handles External lines 9 to 5 interrupt request.
  * @param  None
  * @retval None
  */
void EXTI9_5_IRQHandler(void)
{

  if(EXTI_GetITStatus(EXTI_Line6) != RESET)
  {
		
    /* Toggle LED2 */
     STM_EVAL_LEDToggle(LED1);
     STM_EVAL_LEDToggle(LED2);
		 STM_EVAL_LEDToggle(LED3);
		 STM_EVAL_LEDToggle(LED4);
    /* Clear the  EXTI line 9 pending bit */
    EXTI_ClearITPendingBit(EXTI_Line6);
  }

}

/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/

