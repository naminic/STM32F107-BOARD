/**
  ******************************************************************************
  * @file    stm3210c_eval.c
  * @author  MCD Application Team
  * @version V6.1.0
  * @date    14-April-2017
  * @brief   This file provides a set of firmware functions to manage Leds, 
  *          push-button and COM ports for STM3210C_EVAL
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2016 STMicroelectronics</center></h2>
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
  
/* LINK SD Card */
#define SD_DUMMY_BYTE      0xFF    
#define SD_NO_RESPONSE_EXPECTED  0x80


extern SPI_HandleTypeDef hspi1; 

#define SD_CS_LOW()       HAL_GPIO_WritePin(SD_CS_GPIO_Port, SD_CS_Pin, GPIO_PIN_RESET)
#define SD_CS_HIGH()      HAL_GPIO_WritePin(SD_CS_GPIO_Port, SD_CS_Pin, GPIO_PIN_SET)
/**
 * @brief BUS variables
 */
#ifdef HAL_SPI_MODULE_ENABLED
uint32_t SpiTimeout = 1000;        /*<! Value of Timeout when SPI communication fails */
#endif /* HAL_SPI_MODULE_ENABLED */



/* SPIx bus function */
#ifdef HAL_SPI_MODULE_ENABLED
static void               SPIx_Write(uint8_t Value);
static uint32_t           SPIx_Read(void);
static void               SPIx_WriteReadData(const uint8_t *DataIn, uint8_t *DataOut, uint16_t DataLength);
static void               SPIx_WriteData(const uint8_t *Data, uint16_t DataLength);
static void               SPIx_ReadData(const uint8_t *Data, uint16_t DataLength);
static void               SPIx_Error(void);

/* Link functions for SD Card peripheral over SPI */
void                      SD_IO_Init(void);
void                      SD_IO_CSState(uint8_t state);
void                      SD_IO_WriteReadData(const uint8_t *DataIn, uint8_t *DataOut, uint16_t DataLength);
void                      SD_IO_WriteData(const uint8_t *Data, uint16_t DataLength);
void                      SD_IO_ReadData(const uint8_t *Data, uint16_t DataLength);
uint8_t                   SD_IO_WriteByte(uint8_t Data);
#endif /* HAL_SPI_MODULE_ENABLED */


/******************************* SPI Routines**********************************/
#ifdef HAL_SPI_MODULE_ENABLED
/**
  * @brief SPI Read 4 bytes from device
  * @retval Read data
*/
static uint32_t SPIx_Read(void)
{
  HAL_StatusTypeDef status = HAL_OK;
  uint32_t          readvalue = 0;
  uint32_t          writevalue = 0xFFFFFFFF;
  
  status = HAL_SPI_TransmitReceive(&hspi1, (uint8_t*) &writevalue, (uint8_t*) &readvalue, 1, SpiTimeout);
  
  /* Check the communication status */
  if(status != HAL_OK)
  {
    /* Execute user timeout callback */
    SPIx_Error();
  }

  return readvalue;
}

/**
  * @brief  SPI Write a byte to device
  * @param  DataIn: value to be written
  * @param  DataOut: value to be read
  * @param  DataLength: length of data
  */
static void SPIx_WriteReadData(const uint8_t *DataIn, uint8_t *DataOut, uint16_t DataLength)
{
  HAL_StatusTypeDef status = HAL_OK;

  status = HAL_SPI_TransmitReceive(&hspi1, (uint8_t*) DataIn, DataOut, DataLength, SpiTimeout);

  /* Check the communication status */
  if(status != HAL_OK)
  {
    /* Execute user timeout callback */
    SPIx_Error();
  }
}

/**
  * @brief  SPI Write Data to device
  * @param  Data: value to be written
  * @param  DataLength: length of data
  */
static void SPIx_WriteData(const uint8_t *Data, uint16_t DataLength)
{
  HAL_StatusTypeDef status = HAL_OK;

  status = HAL_SPI_Transmit(&hspi1, (uint8_t*) Data, DataLength, SpiTimeout);

  /* Check the communication status */
  if(status != HAL_OK)
  {
    /* Execute user timeout callback */
    SPIx_Error();
  }
}

/**
  * @brief  SPI Read Data from device
  * @param  Data: value to be read
  * @param  DataLength: length of data
  */
static void SPIx_ReadData(const uint8_t *Data, uint16_t DataLength)
{
  HAL_StatusTypeDef status = HAL_OK;

  status = HAL_SPI_Receive(&hspi1, (uint8_t*) Data, DataLength, SpiTimeout);

  /* Check the communication status */
  if(status != HAL_OK)
  {
    /* Execute user timeout callback */
    SPIx_Error();
  }
}

/**
  * @brief  SPI Write a byte to device.
  * @param  Value: value to be written
  */
static void SPIx_Write(uint8_t Value)
{
  HAL_StatusTypeDef status = HAL_OK;
  uint8_t data;

  status = HAL_SPI_TransmitReceive(&hspi1, (uint8_t*) &Value, &data, 1, SpiTimeout);
    
  /* Check the communication status */
  if(status != HAL_OK)
  {
    /* Execute user timeout callback */
    SPIx_Error();
  }
}

/**
  * @brief  SPI error treatment function
  * @retval None
  */
static void SPIx_Error (void)
{
  /* De-initialize the SPI communication BUS */
  HAL_SPI_DeInit(&hspi1);

}
#endif /* HAL_SPI_MODULE_ENABLED */



/******************************** LINK SD Card ********************************/

/**
  * @brief  Initializes the SD Card and put it into StandBy State (Ready for 
  *         data transfer).
  */
void SD_IO_Init(void)
{
  uint8_t counter;
  /*------------Put SD in SPI mode--------------*/
  
  /* SD chip select high */
  SD_CS_HIGH();
  
  /* Send dummy byte 0xFF, 10 times with CS high */
  /* Rise CS and MOSI for 80 clocks cycles */
  for (counter = 0; counter <= 9; counter++)
  {
    /* Send dummy byte 0xFF */
    SD_IO_WriteByte(SD_DUMMY_BYTE);
  }
}

/**
  * @brief  Set the SD_CS pin.
  * @param  pin value.
  * @retval None
  */
void SD_IO_CSState(uint8_t val)
{
  if(val == 1) 
  {
    SD_CS_HIGH();
}
  else
  {
    SD_CS_LOW();
  }
}

/**
  * @brief Write a byte on the SD.
  * @param  DataIn: value to be written
  * @param  DataOut: value to be read
  * @param  DataLength: length of data
  */
void SD_IO_WriteReadData(const uint8_t *DataIn, uint8_t *DataOut, uint16_t DataLength)
{
  /* Send the byte */
  SPIx_WriteReadData(DataIn, DataOut, DataLength);
}

/**
  * @brief  Write a byte on the SD.
  * @param  Data: value to be written
  * @param  DataLength: length of data
  */
void SD_IO_WriteData(const uint8_t *Data, uint16_t DataLength)
{
  /* Send the byte */
  SPIx_WriteData(Data, DataLength);
}

/**
  * @brief  Read a byte from the SD.
  * @param  Data: value to be read
  * @param  DataLength: length of data
  */
void SD_IO_ReadData(const uint8_t *Data, uint16_t DataLength)
{
  /* Send the byte */
  SPIx_ReadData(Data, DataLength);
}

/**
  * @brief  Writes a byte on the SD.
  * @param  Data: byte to send.
  */
uint8_t SD_IO_WriteByte(uint8_t Data)
{
  uint8_t tmp;
  /* Send the byte */
  SPIx_WriteReadData(&Data,&tmp,1);
  return tmp;
}



/**
  * @}
  */ 

/**
  * @}
  */

/**
  * @}
  */    
  
/**
  * @}
  */    
  
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
