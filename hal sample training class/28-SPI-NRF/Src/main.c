
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  ** This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * COPYRIGHT(c) 2018 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f1xx_hal.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/
SPI_HandleTypeDef hspi3;
DMA_HandleTypeDef hdma_spi3_tx;

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/

#define RXBUFSIZE 64
#define uchar unsigned char
#define TX_ADR_WIDTH    5   // 5 bytes TX(RX) address width
#define RX_ADR_WIDTH    5   	// 5 uints RX address width
#define TX_PLOAD_WIDTH  16  // 20 bytes TX payload
#define RX_PLOAD_WIDTH  16  	// 16 uints TX payload
unsigned char rx_buf[TX_PLOAD_WIDTH];
unsigned char tx_buf[TX_PLOAD_WIDTH];
unsigned char flag,CurrentData;

unsigned char  TX_ADDRESS[TX_ADR_WIDTH]= {0x34,0x43,0x10,0x10,0xe7};	//????
unsigned char  RX_ADDRESS[RX_ADR_WIDTH]= {0x34,0x43,0x10,0x10,0xe7};	//????
volatile char isSend;

/****************************************************************************************/
#define READ_REGL        0x00  // Define read command to register
#define WRITE_REGL       0x20  // Define write command to register
#define RD_RX_PLOAD     0x61  // Define RX payload register address
#define WR_TX_PLOAD     0xA0  // Define TX payload register address
#define FLUSH_TX        0xE1  // Define flush TX register command
#define FLUSH_RX        0xE2  // Define flush RX register command
#define REUSE_TX_PL     0xE3  // Define reuse TX payload register command
#define NOP             0xFF  // Define No Operation, might be used to read status register


#define CONFIG          0x00  // 'Config' register address
#define EN_AA           0x01  // 'Enable Auto Acknowledgment' register address
#define EN_RXADDR       0x02  // 'Enabled RX addresses' register address
#define SETUP_AW        0x03  // 'Setup address width' register address
#define SETUP_RETR      0x04  // 'Setup Auto. Retrans' register address
#define RF_CH           0x05  // 'RF channel' register address
#define RF_SETUP        0x06  // 'RF setup' register address
#define STATUS          0x07  // 'Status' register address
#define OBSERVE_TX      0x08  // 'Observe TX' register address
#define CD              0x09  // 'Carrier Detect' register address
#define RX_ADDR_P0      0x0A  // 'RX address pipe0' register address
#define RX_ADDR_P1      0x0B  // 'RX address pipe1' register address
#define RX_ADDR_P2      0x0C  // 'RX address pipe2' register address
#define RX_ADDR_P3      0x0D  // 'RX address pipe3' register address
#define RX_ADDR_P4      0x0E  // 'RX address pipe4' register address
#define RX_ADDR_P5      0x0F  // 'RX address pipe5' register address
#define TX_ADDR         0x10  // 'TX address' register address
#define RX_PW_P0        0x11  // 'RX payload width, pipe0' register address
#define RX_PW_P1        0x12  // 'RX payload width, pipe1' register address
#define RX_PW_P2        0x13  // 'RX payload width, pipe2' register address
#define RX_PW_P3        0x14  // 'RX payload width, pipe3' register address
#define RX_PW_P4        0x15  // 'RX payload width, pipe4' register address
#define RX_PW_P5        0x16  // 'RX payload width, pipe5' register address
#define FIFO_STATUS     0x17  // 'FIFO Status Register' register address

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_DMA_Init(void);
static void MX_SPI3_Init(void);

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/

/* USER CODE END PFP */

/* USER CODE BEGIN 0 */
#define Receiver        0
#define Transmitter     !Receiver



#define Select_NRF()          HAL_GPIO_WritePin(ChipSelect_GPIO_Port , ChipSelect_Pin , GPIO_PIN_RESET)    
#define NotSelect_NRF()       HAL_GPIO_WritePin(ChipSelect_GPIO_Port , ChipSelect_Pin , GPIO_PIN_SET) 

#define NRF24L01_CE_LOW()     HAL_GPIO_WritePin(CE_GPIO_Port , CE_Pin , GPIO_PIN_RESET)	
#define NRF24L01_CE_HIGH()    HAL_GPIO_WritePin(CE_GPIO_Port , CE_Pin , GPIO_PIN_SET)	

unsigned char SPI1_NRF_SendByte(unsigned char byte)
{ 
    unsigned char Rec_data = 0;
    HAL_SPI_TransmitReceive(&hspi3,&byte,&Rec_data,1,1000);
    return Rec_data;
}


uint8_t SPI_RW_Reg(uint8_t reg, char value)		
{
    unsigned int Data = 0;
    Select_NRF();			    			
    Data=SPI1_NRF_SendByte(reg);		
    SPI1_NRF_SendByte(value);				
    NotSelect_NRF(); 						
    return(Data);						
}

unsigned char SPI_Read(unsigned char reg)
{
  unsigned char Data;
  Select_NRF();						
  SPI1_NRF_SendByte(reg);			
  Data=SPI1_NRF_SendByte(0);			
  NotSelect_NRF(); 					
  return (Data);
}

unsigned char SPI_Write_Buf(unsigned char reg, unsigned char *pBuf, unsigned char bytes)
{
	unsigned char status,byte_ctr;
  	Select_NRF();
  	status=SPI1_NRF_SendByte(reg);	
  	for(byte_ctr=0; byte_ctr<bytes; byte_ctr++)
    {
		SPI1_NRF_SendByte(*pBuf++);  	
	}	
  	NotSelect_NRF();
  	return(status);          		
}


unsigned char SPI_Read_Buf(unsigned char reg, unsigned char *pBuf, unsigned char bytes)
{
    unsigned char status,i;

    Select_NRF();              			
    status=SPI1_NRF_SendByte(reg);	   	
    for(i=0; i<bytes; i++)
    {  		
      pBuf[i]=SPI1_NRF_SendByte(0);  		
    }	
    NotSelect_NRF();
    return(status);          		
}

void Init_24L01(void)
{	
  unsigned char Channel=0x20;
  unsigned char data=0;

  SPI_RW_Reg(WRITE_REGL + CONFIG,0x19);
  SPI_Read(READ_REGL + CONFIG);
  SPI_RW_Reg(WRITE_REGL + EN_AA,0x00);
  SPI_RW_Reg(WRITE_REGL + EN_RXADDR,0x01);
  SPI_RW_Reg(WRITE_REGL + SETUP_AW,0x03);
  SPI_RW_Reg(WRITE_REGL + SETUP_RETR,0x00);
  SPI_RW_Reg(WRITE_REGL + RF_CH,Channel);
  SPI_RW_Reg(WRITE_REGL + RF_SETUP,0x07);
  SPI_RW_Reg(WRITE_REGL + STATUS,0x70);
  SPI_Write_Buf(WRITE_REGL + RX_ADDR_P0, TX_ADDRESS, TX_ADR_WIDTH); // Use the same address on the RX device as the TX device
  SPI_Write_Buf(WRITE_REGL + TX_ADDR, TX_ADDRESS, TX_ADR_WIDTH);    // Writes TX_Address to nRF24L01	
  SPI_RW_Reg(WRITE_REGL + RX_PW_P0,0x04);

  Select_NRF();
  SPI1_NRF_SendByte(0xE2);
  NotSelect_NRF();
  Select_NRF();
  SPI1_NRF_SendByte(0xE1);
  NotSelect_NRF();
	//-------------------------Read a register for test
   unsigned char redReg;
	 redReg=SPI_RW_Reg(READ_REGL + STATUS,0);
}

void send(uchar *Buffdata,uchar Length)
{
    HAL_Delay(3000);
    isSend = 1;
    NRF24L01_CE_LOW();
    SPI_RW_Reg(WRITE_REGL + CONFIG,0x1e);
    SPI_RW_Reg(FLUSH_TX,0);
    SPI_Write_Buf(WR_TX_PLOAD, Buffdata ,Length); 			// Writes data to TX payload
    NRF24L01_CE_HIGH();
    HAL_Delay(50);
    NRF24L01_CE_LOW();
    SPI_RW_Reg(WRITE_REGL + STATUS,0x70);
}


void Set_RF_RX_Mode(uchar DataLength)
{
    SPI_RW_Reg(WRITE_REGL + RX_PW_P0,DataLength);
    SPI_RW_Reg(WRITE_REGL + CONFIG,0x1f);
    SPI_RW_Reg(FLUSH_RX,0);
    NRF24L01_CE_HIGH();
}

char  RecNRF(uchar *Buffdata)
{
    if (isSend)
    {
        Set_RF_RX_Mode(32);
        HAL_Delay(50);
        isSend = 0;
    }
      CurrentData=SPI_Read(STATUS);		         // read register STATUS's value
      if(CurrentData == 0x40)				// if receive data ready (RX_DR) interrupt
      {
        memset(Buffdata,0,32);
        SPI_Read_Buf(RD_RX_PLOAD,Buffdata,32);		// read receive payload from RX_FIFO buffer
       SPI_RW_Reg(WRITE_REGL+STATUS,0X70);
        SPI_RW_Reg(FLUSH_RX,0);
        Set_RF_RX_Mode(32);

        return 1;
      }

      return 0;
}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  *
  * @retval None
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
    unsigned char recbuff[32];
    int i;	
    char state; 
    unsigned char sendBuff[32]="1234567890.0987654321";    
  /* USER CODE END 1 */

  /* MCU Configuration----------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_SPI3_Init();
  /* USER CODE BEGIN 2 */
    Init_24L01();
    
    #if (Receiver == 1)
        Set_RF_RX_Mode(32);
   
    #endif
    
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
  /* USER CODE END WHILE */

  /* USER CODE BEGIN 3 */
    #if (Receiver == 1)
        state  = RecNRF(recbuff);
        if( state== 1)
        {
            i++;
            state = 0;
        }      
        #else
        send(sendBuff,32); 
        HAL_Delay(2000);
      #endif
  }
  /* USER CODE END 3 */

}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV5;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.Prediv1Source = RCC_PREDIV1_SOURCE_PLL2;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  RCC_OscInitStruct.PLL2.PLL2State = RCC_PLL2_ON;
  RCC_OscInitStruct.PLL2.PLL2MUL = RCC_PLL2_MUL8;
  RCC_OscInitStruct.PLL2.HSEPrediv2Value = RCC_HSE_PREDIV2_DIV5;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Configure the Systick interrupt time 
    */
  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

    /**Configure the Systick 
    */
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

    /**Configure the Systick interrupt time 
    */
  __HAL_RCC_PLLI2S_ENABLE();

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

/* SPI3 init function */
static void MX_SPI3_Init(void)
{

  /* SPI3 parameter configuration*/
  hspi3.Instance = SPI3;
  hspi3.Init.Mode = SPI_MODE_MASTER;
  hspi3.Init.Direction = SPI_DIRECTION_2LINES;
  hspi3.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi3.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi3.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi3.Init.NSS = SPI_NSS_SOFT;
  hspi3.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
  hspi3.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi3.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi3.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi3.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi3) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}

/** Configure pins as 
        * Analog 
        * Input 
        * Output
        * EVENT_OUT
        * EXTI
*/
static void MX_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct;

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, CE_Pin|ChipSelect_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : IRQ_Config_Pin */
  GPIO_InitStruct.Pin = IRQ_Config_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(IRQ_Config_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : CE_Pin ChipSelect_Pin */
  GPIO_InitStruct.Pin = CE_Pin|ChipSelect_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  file: The file name as string.
  * @param  line: The line in file as a number.
  * @retval None
  */
void _Error_Handler(char *file, int line)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  while(1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
