/**
  ******************************************************************************
  * @file    GPIO/IOToggle/main.c 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2015
  * @brief   Main program body.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */ 

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"

/** @addtogroup STM32F10x_StdPeriph_Examples
  * @{
  */

/** @addtogroup GPIO_IOToggle
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
GPIO_InitTypeDef GPIO_InitStructure;

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
  /*!< At this stage the microcontroller clock setting is already configured, 
       this is done through SystemInit() function which is called from startup
       file (startup_stm32f10x_xx.s) before to branch to application main.
       To reconfigure the default setting of SystemInit() function, refer to
       system_stm32f10x.c file
     */     
       
  /* GPIOC Periph clock enable */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

  /* Configure PC2 and PC3 in output pushpull mode */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3 ;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOC, &GPIO_InitStructure);

  /* To achieve GPIO toggling maximum frequency, the following  sequence is mandatory. 
     You can monitor PC.2 or PC.3 on the scope to measure the output signal. 
     If you need to fine tune this frequency, you can add more GPIO set/reset 
     cycles to minimize more the infinite loop timing.
     This code needs to be compiled with high speed optimization option.  */
  while (1)
  {
    /* Set PC2 and PC3 */
    GPIOC->BSRR = 0x0000000C;
    /* Reset PC2 and PC3 */
    GPIOC->BRR  = 0x0000000C;

   /* Set PC2 and PC3 */
   GPIOC->BSRR = 0x0000000C;
   /* Reset PC2 and PC3 */
   GPIOC->BRR  = 0x0000000C;

   /* Set PC2 and PC3 */
   GPIOC->BSRR = 0x0000000C;
   /* Reset PC2 and PC3 */
   GPIOC->BRR  = 0x0000000C;

   /* Set PC2 and PC3 */
   GPIOC->BSRR = 0x0000000C;
   /* Reset PC2 and PC3 */
   GPIOC->BRR  = 0x0000000C;

   /* Set PC2 and PC3 */
   GPIOC->BSRR = 0x0000000C;
   /* Reset PC2 and PC3 */
   GPIOC->BRR  = 0x0000000C;

   /* Set PC2 and PC3 */
   GPIOC->BSRR = 0x0000000C;
   /* Reset PC2 and PC3 */
   GPIOC->BRR  = 0x0000000C;

   /* Set PC2 and PC3 */
   GPIOC->BSRR = 0x0000000C;
   /* Reset PC2 and PC3 */
   GPIOC->BRR  = 0x0000000C;

   /* Set PC2 and PC3 */
   GPIOC->BSRR = 0x0000000C;
   /* Reset PC2 and PC3 */
   GPIOC->BRR  = 0x0000000C;

   /* Set PC2 and PC3 */
   GPIOC->BSRR = 0x0000000C;
   /* Reset PC2 and PC3 */
   GPIOC->BRR  = 0x0000000C;

   /* Set PC2 and PC3 */
   GPIOC->BSRR = 0x0000000C;
   /* Reset PC2 and PC3 */
   GPIOC->BRR  = 0x0000000C;
  }


	
}


/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
