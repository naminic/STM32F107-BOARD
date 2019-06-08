#include "bsp.h"
#include "stm32f10x_usart.h"
#include "stm32f10x.h"
#include <stdio.h>
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define DAC_DHR12RD_Address      0x40007420

/* Init Structure definition */
DAC_InitTypeDef            DAC_InitStructure;
DMA_InitTypeDef            DMA_InitStructure;
TIM_TimeBaseInitTypeDef    TIM_TimeBaseStructure;

#define SINE_POINT 128
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
const uint16_t Sine12bit[SINE_POINT] = {
0x800,0x864,0x8c8,0x92c,0x98f,0x9f1,0xa52,0xab1,
0xb0f,0xb6b,0xbc5,0xc1c,0xc71,0xcc3,0xd12,0xd5f,
0xda7,0xded,0xe2e,0xe6c,0xea6,0xedc,0xf0d,0xf3a,
0xf63,0xf87,0xfa7,0xfc2,0xfd8,0xfe9,0xff5,0xffd,
0xfff,0xffd,0xff5,0xfe9,0xfd8,0xfc2,0xfa7,0xf87,
0xf63,0xf3a,0xf0d,0xedc,0xea6,0xe6c,0xe2e,0xded,
0xda7,0xd5f,0xd12,0xcc3,0xc71,0xc1c,0xbc5,0xb6b,
0xb0f,0xab1,0xa52,0x9f1,0x98f,0x92c,0x8c8,0x864,
0x800,0x79b,0x737,0x6d3,0x670,0x60e,0x5ad,0x54e,
0x4f0,0x494,0x43a,0x3e3,0x38e,0x33c,0x2ed,0x2a0,
0x258,0x212,0x1d1,0x193,0x159,0x123,0xf2,0xc5,
0x9c,0x78,0x58,0x3d,0x27,0x16,0xa,0x2,
0x0,0x2,0xa,0x16,0x27,0x3d,0x58,0x78,
0x9c,0xc5,0xf2,0x123,0x159,0x193,0x1d1,0x212,
0x258,0x2a0,0x2ed,0x33c,0x38e,0x3e3,0x43a,0x494,
0x4f0,0x54e,0x5ad,0x60e,0x670,0x6d3,0x737,0x79b};

uint32_t DualSine12bit[128];
uint8_t Idx = 0;
/******************************************************************************
            Initial RCC
  * @brief  Configures different system clocks
  * @param  None
  * @retval None                           
******************************************************************************/
void RCC_Configuration(void)
{   
  /* Setup the micro controller system. Initialize the Embedded Flash Interface,  
     initialize the PLL and update the SystemFrequency variable. */
  SystemInit();

/* Enable peripheral clocks --------------------------------------------------*/
  /* DMA clock enable */
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA2, ENABLE);
  /* GPIOA Peripheral clock enable */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
  /* DAC Peripheral clock enable */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE);
  /* TIM2 Peripheral clock enable */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
}

/******************************************************************************
           Initial GPIO
  * @brief  Configure GPIO Pins
  * @param  None
  * @retval None
******************************************************************************/

void GPIO_Configuration(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  /* Once the DAC channel is enabled, the corresponding GPIO pin is automatically 
     connected to the DAC converter. In order to avoid parasitic consumption, 
     the GPIO pin should be configured in analog */
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_4 | GPIO_Pin_5;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
}
	 /* DMA2 channel4 configuration */
void DMA_Configuration(void){

	 /* DMA2 channel4 configuration */
  DMA_DeInit(DMA2_Channel4);
  DMA_InitStructure.DMA_PeripheralBaseAddr = DAC_DHR12RD_Address;
  DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)&DualSine12bit;
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;
  DMA_InitStructure.DMA_BufferSize = SINE_POINT;
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Word;
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Word;
  DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
  DMA_InitStructure.DMA_Priority = DMA_Priority_High;
  DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
  DMA_Init(DMA2_Channel4, &DMA_InitStructure);

  /* Enable DMA2 Channel4 */
  DMA_Cmd(DMA2_Channel4, ENABLE);
}

	 /* DAC channel1 Configuration */
void DAC_Configuration(void){
	 /* DAC channel1 Configuration */
  DAC_InitStructure.DAC_Trigger = DAC_Trigger_T2_TRGO;
  DAC_InitStructure.DAC_WaveGeneration = DAC_WaveGeneration_None;
  DAC_InitStructure.DAC_OutputBuffer = DAC_OutputBuffer_Disable;
  DAC_Init(DAC_Channel_1, &DAC_InitStructure);

  /* DAC channel2 Configuration */
  DAC_Init(DAC_Channel_2, &DAC_InitStructure);

  /* Fill Sine32bit table */
  for (Idx = 0; Idx < SINE_POINT; Idx++)
  {
    DualSine12bit[Idx] = (Sine12bit[Idx] << 16) + (Sine12bit[Idx]);
  }
	
}
/******************************************************************************
           Initial TIM2
  * @brief  Configure TIM2
  * @param  None
  * @retval None
******************************************************************************/
void TIM_Configuration(void){
	
	  /* TIM2 Configuration */
  /* Time base configuration */
  TIM_TimeBaseStructInit(&TIM_TimeBaseStructure); 
  TIM_TimeBaseStructure.TIM_Period = 11249;          
  TIM_TimeBaseStructure.TIM_Prescaler = 0x0;       
  TIM_TimeBaseStructure.TIM_ClockDivision = 0x0;    
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  
  TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

  /* TIM2 TRGO selection */
  TIM_SelectOutputTrigger(TIM2, TIM_TRGOSource_Update);
}

/*******************************************************************************
  * @brief  Inserts a delay time.
  * @param  nCount: specifies the delay time length.
  * @retval None
  ******************************************************************************/
void Delay(__IO uint32_t nCount)
{
  for(; nCount != 0; nCount--);
}

