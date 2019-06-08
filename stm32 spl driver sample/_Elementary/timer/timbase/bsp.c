#include "stm32f10x_usart.h"
#include "bsp.h"

TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
TIM_OCInitTypeDef  TIM_OCInitStructure;
__IO uint16_t CCR1_Val = 50;
__IO uint16_t CCR2_Val = 27309;
__IO uint16_t CCR3_Val = 13654;
__IO uint16_t CCR4_Val = 6826;
uint16_t PrescalerValue = 0;

uint16_t capture = 0;	

/******************************************************************************
                               Initial RCC
  * @brief  Configures different system clocks.
  * @param  None
  * @retval None
******************************************************************************/
void RCC_Configuration(){
 
	/* PCLK1 = HCLK/4 */
  RCC_PCLK1Config(RCC_HCLK_Div4);

  /* TIM2 clock enable */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

  /* GPIOC clock enable */
  RCC_APB2PeriphClockCmd(LED1_GPIO_CLK, ENABLE);	
}

/******************************************************************************
                                  Initial GPIO
  * @brief  Configure GPIO Pins.
  * @param  None
  * @retval None
******************************************************************************/
void GPIO_Configuration(void){
  GPIO_InitTypeDef GPIO_InitStructure;

  /* GPIOC Configuration:Pin6, 7, 8 and 9 as alternate function push-pull */
  GPIO_InitStructure.GPIO_Pin = LED1_PIN | LED2_PIN | LED3_PIN | LED4_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

  GPIO_Init(GPIOC, &GPIO_InitStructure);
}

/******************************************************************************
                                    Initial TIM2
  * @brief  This function handles TIM2 global interrupt request.
  * @param  None
  * @retval None                            
******************************************************************************/
void TIM2_IRQHandler(void)
{
  if (TIM_GetITStatus(TIM2, TIM_IT_CC1) != RESET)
  {
    TIM_ClearITPendingBit(TIM2, TIM_IT_CC1);

    /* Pin PC.06 toggling with frequency = 73.24 Hz */
    GPIO_WriteBit(GPIOC, LED1_PIN, (BitAction)(1 - GPIO_ReadOutputDataBit(GPIOC, LED1_PIN)));
    capture = TIM_GetCapture1(TIM2);
    TIM_SetCompare1(TIM2, capture + CCR1_Val);
  }
  else if (TIM_GetITStatus(TIM2, TIM_IT_CC2) != RESET)
  {
    TIM_ClearITPendingBit(TIM2, TIM_IT_CC2);

    /* Pin PC.07 toggling with frequency = 109.8 Hz */
    GPIO_WriteBit(GPIOC, LED2_PIN, (BitAction)(1 - GPIO_ReadOutputDataBit(GPIOC, LED2_PIN)));
    capture = TIM_GetCapture2(TIM2);
    TIM_SetCompare2(TIM2, capture + CCR2_Val);
  }
  else if (TIM_GetITStatus(TIM2, TIM_IT_CC3) != RESET)
  {
    TIM_ClearITPendingBit(TIM2, TIM_IT_CC3);

    /* Pin PC.08 toggling with frequency = 219.7 Hz */
    GPIO_WriteBit(GPIOC, LED3_PIN, (BitAction)(1 - GPIO_ReadOutputDataBit(GPIOC, LED3_PIN)));
    capture = TIM_GetCapture3(TIM2);
    TIM_SetCompare3(TIM2, capture + CCR3_Val);
  }
  else
  {
    TIM_ClearITPendingBit(TIM2, TIM_IT_CC4);

    /* Pin PC.09 toggling with frequency = 439.4 Hz */
    GPIO_WriteBit(GPIOC, LED4_PIN, (BitAction)(1 - GPIO_ReadOutputDataBit(GPIOC, LED4_PIN)));
    capture = TIM_GetCapture4(TIM2);
    TIM_SetCompare4(TIM2, capture + CCR4_Val);
  }
}

/******************************************************************************
  * @brief  This function configures the nested vectored interrupt controller.
  * @param  None
  * @retval None                         
******************************************************************************/
void NVIC_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;

  /* Enable the TIM2 global Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;

  NVIC_Init(&NVIC_InitStructure);
}
/******************************************************************************
    TIM2 Configuration: Output Compare Timing Mode:
    TIM2 counter clock at 6 MHz
    CC1 update rate = TIM2 counter clock / CCR1_Val = 146.48 Hz
    CC2 update rate = TIM2 counter clock / CCR2_Val = 219.7 Hz
    CC3 update rate = TIM2 counter clock / CCR3_Val = 439.4 Hz
    CC4 update rate = TIM2 counter clock / CCR4_Val = 878.9 Hz                      
******************************************************************************/
void Timer_Intial(void){
	
  /* Compute the prescaler value */
  PrescalerValue = (uint16_t) (SystemCoreClock / 12000000) - 1;

  /* Time base configuration */
  TIM_TimeBaseStructure.TIM_Period = 65535;
  TIM_TimeBaseStructure.TIM_Prescaler = 719;
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;

  TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

  /* Prescaler configuration */
  //TIM_PrescalerConfig(TIM2, PrescalerValue, TIM_PSCReloadMode_Immediate);

  /* Output Compare Timing Mode configuration: Channel1 */
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_Timing;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = CCR1_Val;
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;

  TIM_OC1Init(TIM2, &TIM_OCInitStructure);

  TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Disable);

  /* Output Compare Timing Mode configuration: Channel2 */
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = CCR2_Val;

  TIM_OC2Init(TIM2, &TIM_OCInitStructure);

  TIM_OC2PreloadConfig(TIM2, TIM_OCPreload_Disable);

  /* Output Compare Timing Mode configuration: Channel3 */
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = CCR3_Val;

  TIM_OC3Init(TIM2, &TIM_OCInitStructure);

  TIM_OC3PreloadConfig(TIM2, TIM_OCPreload_Disable);

  /* Output Compare Timing Mode configuration: Channel4 */
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = CCR4_Val;

  TIM_OC4Init(TIM2, &TIM_OCInitStructure);

  TIM_OC4PreloadConfig(TIM2, TIM_OCPreload_Disable);

  /* TIM IT enable */
  TIM_ITConfig(TIM2, TIM_IT_CC1 | TIM_IT_CC2 | TIM_IT_CC3 | TIM_IT_CC4, ENABLE);

  /* TIM2 enable counter */
  TIM_Cmd(TIM2, ENABLE);


}
