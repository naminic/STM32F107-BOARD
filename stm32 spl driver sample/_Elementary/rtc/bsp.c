#include "bsp.h"
#include "stm32f10x_usart.h"
#include <stdio.h>

__IO uint32_t TimeDisplay = 0;

/******************************************************************************
            Initial RCC
  * @brief  Configures different system clocks
  * @param  None
  * @retval None                           
******************************************************************************/
******************************************************************************/
void RCC_Configuration(){
	RCC_APB2PeriphClockCmd(COM1_CLK_PORT|RCC_APB2Periph_AFIO,ENABLE);
	RCC_APB2PeriphClockCmd(COM1_CLK,ENABLE);
	
	//RCC_APB2PeriphClockCmd(COM2_CLK_PORT|RCC_APB2Periph_AFIO,ENABLE);
	//RCC_APB1PeriphClockCmd(COM2_CLK,ENABLE);

}
/******************************************************************************
           Initial GPIO
  * @brief  Configure GPIO Pins
  * @param  None
  * @retval None
******************************************************************************/
void GPIO_Configuration(void){
	
  GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_PinRemapConfig(COM2_Remap,ENABLE);
	GPIO_PinRemapConfig(COM1_Remap,ENABLE);
	
	GPIO_InitStruct.GPIO_Pin = COM1_TXD_PIN;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;	
	GPIO_Init(COM1_PORT,&GPIO_InitStruct); //TX1	

	GPIO_InitStruct.GPIO_Pin = COM1_RXD_PIN;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;	
	GPIO_Init(COM1_PORT,&GPIO_InitStruct); //RX1
	
//	GPIO_InitStruct.GPIO_Pin = COM2_TXD_PIN;
//	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;	
//	GPIO_Init(COM2_PORT,&GPIO_InitStruct); //TX2	

//	GPIO_InitStruct.GPIO_Pin = COM2_RXD_PIN;
//	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;	
//	GPIO_Init(COM2_PORT,&GPIO_InitStruct); //RX2
	//----------------------------------------------------		
}
/******************************************************************************
           Initial UART1
  * @brief  Configure UART1
  * @param  None
  * @retval None
******************************************************************************/
void Com1_Intial(void){
	USART_InitTypeDef USART_InitStructure;
  USART_InitStructure.USART_BaudRate = 9600;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(COM1,&USART_InitStructure);
	USART_Cmd(COM1,ENABLE);
}
/******************************************************************************
           Initial UART2
  * @brief  Configure UART2
  * @param  None
  * @retval None
******************************************************************************/
void Com2_Intial(void){
	USART_InitTypeDef USART_InitStructure;
  USART_InitStructure.USART_BaudRate = 9600;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(COM2,&USART_InitStructure);
	USART_Cmd(COM2,ENABLE);
}


/******************************************************************************
                       Interrupt RTC
  * @brief  This function handles RTC global interrupt request.
  * @param  None
  * @retval None
 ******************************************************************************/
void RTC_IRQHandler(void)
{
  if (RTC_GetITStatus(RTC_IT_SEC) != RESET)
  {
    /* Clear the RTC Second interrupt */
    RTC_ClearITPendingBit(RTC_IT_SEC);

    /* Enable time update */
    TimeDisplay = 1;

    /* Wait until last write operation on RTC registers has finished */
    RTC_WaitForLastTask();
    /* Reset RTC Counter when Time is 23:59:59 */
    if (RTC_GetCounter() == 0x00015180)
    {
      RTC_SetCounter(0x0);
      /* Wait until last write operation on RTC registers has finished */
      RTC_WaitForLastTask();
    }
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

  /* Configure one bit for preemption priority */
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);

  /* Enable the RTC Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = RTC_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}

/******************************************************************************
  * @brief  Configures the RTC.
  * @param  None
  * @retval None
  ******************************************************************************/
void RTC_Configuration(void)
{
  /* Enable PWR and BKP clocks */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);

  /* Allow access to BKP Domain */
  PWR_BackupAccessCmd(ENABLE);

  /* Reset Backup Domain */
  BKP_DeInit();

  /* Enable LSE */
  RCC_LSEConfig(RCC_LSE_ON);
  /* Wait till LSE is ready */
  while (RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET)
  {}

  /* Select LSE as RTC Clock Source */
  RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);

  /* Enable RTC Clock */
  RCC_RTCCLKCmd(ENABLE);

  /* Wait for RTC registers synchronization */
  RTC_WaitForSynchro();

  /* Wait until last write operation on RTC registers has finished */
  RTC_WaitForLastTask();

  /* Enable the RTC Second */
  RTC_ITConfig(RTC_IT_SEC, ENABLE);

  /* Wait until last write operation on RTC registers has finished */
  RTC_WaitForLastTask();

  /* Set RTC prescaler: set RTC period to 1sec */
  RTC_SetPrescaler(32767); /* RTC period = RTCCLK/RTC_PR = (32.768 KHz)/(32767+1) */

  /* Wait until last write operation on RTC registers has finished */
  RTC_WaitForLastTask();
}

/******************************************************************************
  * @brief  Returns the time entered by user, using Hyper terminal.
  * @param  None
  * @retval Current time RTC counter value
   ******************************************************************************/
uint32_t Time_Regulate(void)
{
  uint32_t Tmp_HH = 0xFF, Tmp_MM = 0xFF, Tmp_SS = 0xFF;

  printf("\r\n==============Time Settings=====================================");
  printf("\r\n  Please Set Hours");

  while (Tmp_HH == 0xFF)
  {
    Tmp_HH = USART_Scanf(23);
  }
  printf(":  %d", Tmp_HH);
  printf("\r\n  Please Set Minutes");
  while (Tmp_MM == 0xFF)
  {
    Tmp_MM = USART_Scanf(59);
  }
  printf(":  %d", Tmp_MM);
  printf("\r\n  Please Set Seconds");
  while (Tmp_SS == 0xFF)
  {
    Tmp_SS = USART_Scanf(59);
  }
  printf(":  %d", Tmp_SS);

  /* Return the value to store in RTC counter register */
  return((Tmp_HH*3600 + Tmp_MM*60 + Tmp_SS));
}

/******************************************************************************
  * @brief  Adjusts Time.
  * @param  None
  * @retval None
 ******************************************************************************/
void Time_Adjust(void)
{
  /* Wait until last write operation on RTC registers has finished */
  RTC_WaitForLastTask();
  /* Change the current time */
  RTC_SetCounter(Time_Regulate());
  /* Wait until last write operation on RTC registers has finished */
  RTC_WaitForLastTask();
}

/**
  * @brief  Displays the current time.
  * @param  TimeVar: RTC counter value.
  * @retval None
  */
void Time_Display(uint32_t TimeVar)
{
  uint32_t THH = 0, TMM = 0, TSS = 0;

  /* Compute  hours */
  THH = TimeVar / 3600;
  /* Compute minutes */
  TMM = (TimeVar % 3600) / 60;
  /* Compute seconds */
  TSS = (TimeVar % 3600) % 60;

  printf("Time: %0.2d:%0.2d:%0.2d\r", THH, TMM, TSS);
}

/******************************************************************************
  * @brief  Shows the current time (HH:MM:SS) on the Hyper terminal.
  * @param  None
  * @retval None
 ******************************************************************************/ 
void Time_Show(void)
{
  printf("\n\r");

  /* Infinite loop */
  while (1)
  {
    /* If 1s has paased */
    if (TimeDisplay == 1)
    {
      /* Display current time */
      Time_Display(RTC_GetCounter());
      TimeDisplay = 0;
    }
  }
}



/* ******************************************************************************
  * @brief  Gets numeric values from the hyper terminal.
  * @param  None
  * @retval None
 ******************************************************************************/
uint8_t USART_Scanf(uint32_t value)
{
  uint32_t index = 0;
  uint32_t tmp[2] = {0, 0};

  while (index < 2)
  {
    /* Loop until RXNE = 1 */
    while (USART_GetFlagStatus(COM1, USART_FLAG_RXNE) == RESET)
    {}
    tmp[index++] = (USART_ReceiveData(COM1));
    if ((tmp[index - 1] < 0x30) || (tmp[index - 1] > 0x39))
    {
      printf("\n\rPlease enter valid number between 0 and 9");
      index--;
    }
  }
  /* Calculate the Corresponding value */
  index = (tmp[1] - 0x30) + ((tmp[0] - 0x30) * 10);
  /* Checks */
  if (index > value)
  {
    printf("\n\rPlease enter valid number between 0 and %d", value);
    return 0xFF;
  }
  return index;
}


#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {}
}
#endif




