/**
  ******************************************************************************
  * @file    SPI/M25P64_FLASH/spi_flash.c
  * @author  MCD Application Team
  * @version V3.1.2
  * @date    09/28/2009
  * @brief   This file provides a set of functions needed to manage the
  *          communication between SPI peripheral and SPI M25P64 FLASH.
  ******************************************************************************
  * @copy
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2009 STMicroelectronics</center></h2>
  */

/* Includes ------------------------------------------------------------------*/
#include "spi_flash.h"

// Constants
//Look-up table for these sizes ->  512k, 1M, 2M, 4M, 8M, 16M, 32M, 64M
const unsigned char DF_pagebits[]  ={  9,  9,  9,  9,  9,  10,  10,  11};	//index of internal page address bits

// Globals
unsigned char PageBits;

#define DUMMY_BYTE    0xff
uint8_t SPI_FLASH_ReadByte(void);
uint8_t SPI_FLASH_SendByte(uint8_t byte);



/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/*******************************************************************************
  * @brief  Initializes the peripherals used by the SPI FLASH driver.
  * @param  None
  * @retval None
  ******************************************************************************/
void SPI_FLASH_Init(void)
{
  SPI_InitTypeDef  SPI_InitStructure;
  GPIO_InitTypeDef GPIO_InitStructure;

  /* Enable SPI and GPIO clocks */
  RCC_APB2PeriphClockCmd( SPI_FLASH_GPIO_CLK | SPI_FLASH_CS_GPIO_CLK, ENABLE);
  RCC_APB1PeriphClockCmd(SPI_FLASH_CLK,ENABLE);
  GPIO_PinRemapConfig(GPIO_Remap_SPI3, ENABLE);

  /* Configure SPI pins: SCK, MISO and MOSI */
  GPIO_InitStructure.GPIO_Pin = SPI_FLASH_PIN_SCK | SPI_FLASH_PIN_MISO | SPI_FLASH_PIN_MOSI;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(SPI_FLASH_GPIO, &GPIO_InitStructure);

  /* Configure I/O for Flash Chip select */
  GPIO_InitStructure.GPIO_Pin = SPI_FLASH_CS;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(SPI_FLASH_CS_GPIO, &GPIO_InitStructure);

  /* Deselect the FLASH: Chip Select high */
  SPI_FLASH_CS_HIGH();

  /* SPI configuration */
  SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
  SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
  SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
  SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;
  SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
  SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
  SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_4;
  SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
  SPI_InitStructure.SPI_CRCPolynomial = 7;
  SPI_Init(SPI_FLASH, &SPI_InitStructure);

  /* Enable the SPI  */
  SPI_Cmd(SPI_FLASH, ENABLE);
}




/**
  * @brief  Sends a byte through the SPI interface and return the byte received
  *   from the SPI bus.
  * @param  byte: byte to send.
  * @retval The value of the received byte.
  */
uint8_t SPI_FLASH_SendByte(uint8_t byte)
{

  uint8_t RxData = 0;
  /* Loop while DR register in not empty */
  //while (SPI_I2S_GetFlagStatus(SPI_FLASH, SPI_I2S_FLAG_TXE) == RESET);

  /* Send byte through the SPI1 peripheral */
  SPI_I2S_SendData(SPI_FLASH, byte);

  /* Wait to receive a byte */
  while (SPI_I2S_GetFlagStatus(SPI_FLASH, SPI_I2S_FLAG_RXNE) == RESET);

  /* Return the byte read from the SPI bus */
  RxData=SPI_I2S_ReceiveData(SPI_FLASH);

  return (uint8_t)RxData;
}

/**
  * @brief  Reads a byte from the SPI Flash.
  * @note   This function must be used only if the Start_Read_Sequence function
  *   has been previously called.
  * @param  None
  * @retval Byte Read from the SPI Flash.
  */
uint8_t SPI_FLASH_ReadByte(void)
{
  return (SPI_FLASH_SendByte(DUMMY_BYTE));
}

unsigned char DF_SPI_RW (unsigned char output)
{
        return SPI_FLASH_SendByte(output);
}	

/*****************************************************************************
*
*	Function name : Read_DF_status
*
*	Returns :		One status byte. Consult Dataflash datasheet for further
*					decoding info
*
*	Parameters :	None
*
*	Purpose :		Status info concerning the Dataflash is busy or not.
*					Status info concerning compare between buffer and flash page
*					Status info concerning size of actual device
*
******************************************************************************/
unsigned char Read_DF_status (void)
{
	unsigned char result,index_copy;
	
  DF_CS_inactive;							//make sure to toggle CS signal in order
	DF_CS_active;							//to reset dataflash command decoder
	result = DF_SPI_RW(StatusReg);			//send status register read op-code
	result = DF_SPI_RW(0xff);				//dummy write to get result
	
	index_copy = ((result & 0x38) >> 3);	//get the size info from status register
	PageBits   = DF_pagebits[index_copy];	//get number of internal page address bits from look-up table
	DF_CS_inactive;							//make sure to toggle CS signal in order
	return result;							//return the read status register value
}


/*****************************************************************************
*	Function name : Page_To_Buffer
*
*	Returns :		None
*
*	Parameters :	BufferNo	->	Decides usage of either buffer 1 or 2
*					PageAdr		->	Address of page to be transferred to buffer
*
*	Purpose :		Transfers a page from flash to data flash SRAM buffer				
******************************************************************************/
void Page_To_Buffer (unsigned int PageAdr, unsigned char BufferNo)
{
	DF_CS_inactive;							//make sure to toggle CS signal in order
	DF_CS_active;												//to reset dataflash command decoder
	
	if (1 == BufferNo)											//transfer flash page to buffer 1
	{
		DF_SPI_RW(FlashToBuf1Transfer);							//transfer to buffer 1 op-code
		DF_SPI_RW((unsigned char)(PageAdr >> (16 - PageBits)));	//upper part of page address
		DF_SPI_RW((unsigned char)(PageAdr << (PageBits - 8)));	//lower part of page address
		DF_SPI_RW(0x00);										//don't cares
	}
	else	
	if (2 == BufferNo)											//transfer flash page to buffer 2
	{
		DF_SPI_RW(FlashToBuf2Transfer);							//transfer to buffer 2 op-code
		DF_SPI_RW((unsigned char)(PageAdr >> (16 - PageBits)));	//upper part of page address
		DF_SPI_RW((unsigned char)(PageAdr << (PageBits - 8)));	//lower part of page address
		DF_SPI_RW(0x00);										//don't cares
	}
	
	DF_CS_inactive;												//initiate the transfer
	DF_CS_active;
	
	while(!(Read_DF_status() & 0x80));							//monitor the status register, wait until busy-flag is high
	
	DF_CS_inactive;												//make sure to toggle CS signal in order
}



/*****************************************************************************
*	Function name : Buffer_Read_Byte
*
*	Returns :		One read byte (any value)
*
*	Parameters :	BufferNo	->	Decides usage of either buffer 1 or 2
*					IntPageAdr	->	Internal page address
*
*	Purpose :		Reads one byte from one of the data flash
*					internal SRAM buffers
******************************************************************************/
unsigned char Buffer_Read_Byte (unsigned char BufferNo, unsigned int IntPageAdr)
{
	unsigned char data;
  DF_CS_inactive;							//make sure to toggle CS signal in order	
	DF_CS_active;								//to reset data flash command decoder
	
	if (1 == BufferNo)							//read byte from buffer 1
	{
		DF_SPI_RW(Buf1Read);					//buffer 1 read op-code
		DF_SPI_RW(0x00);						//don't cares
		DF_SPI_RW((unsigned char)(IntPageAdr>>8));//upper part of internal buffer address
		DF_SPI_RW((unsigned char)(IntPageAdr));	//lower part of internal buffer address
		DF_SPI_RW(0x00);						//don't cares
		data = DF_SPI_RW(0x00);					//read byte
	}
	else
	if (2 == BufferNo)							//read byte from buffer 2
	{
		DF_SPI_RW(Buf2Read);					//buffer 2 read op-code
		DF_SPI_RW(0x00);						//don't cares
		DF_SPI_RW((unsigned char)(IntPageAdr>>8));//upper part of internal buffer address
		DF_SPI_RW((unsigned char)(IntPageAdr));	//lower part of internal buffer address
		DF_SPI_RW(0x00);						//don't cares
		data = DF_SPI_RW(0x00);					//read byte
	}
	
	DF_CS_inactive;								//make sure to toggle CS signal in order
	return data;								//return the read data byte
}



/*****************************************************************************
*
*	Function name : Buffer_Read_Str
*
*	Returns :		None
*
*	Parameters :	BufferNo	->	Decides usage of either buffer 1 or 2
*					IntPageAdr	->	Internal page address
*					No_of_bytes	->	Number of bytes to be read
*					*BufferPtr	->	address of buffer to be used for read bytes
*
*	Purpose :		Reads one or more bytes from one of the dataflash
*					internal SRAM buffers, and puts read bytes into
*					buffer pointed to by *BufferPtr
*
******************************************************************************/
void Buffer_Read_Str (unsigned char BufferNo, unsigned int IntPageAdr, unsigned int No_of_bytes, unsigned char *BufferPtr)
{
	unsigned int i;
  DF_CS_inactive;							//make sure to toggle CS signal in order
	DF_CS_active;								//to reset dataflash command decoder
	if (1 == BufferNo)							//read byte(s) from buffer 1
	{
		DF_SPI_RW(Buf1Read);					//buffer 1 read op-code
		DF_SPI_RW(0x00);						//don't cares
		DF_SPI_RW((unsigned char)(IntPageAdr>>8));//upper part of internal buffer address
		DF_SPI_RW((unsigned char)(IntPageAdr));	//lower part of internal buffer address
		DF_SPI_RW(0x00);						//don't cares
		for( i=0; i<No_of_bytes; i++)
		{
			*(BufferPtr) = DF_SPI_RW(0x00);		//read byte and put it in AVR buffer pointed to by *BufferPtr
			BufferPtr++;						//point to next element in AVR buffer
		}
	}
	else
	if (2 == BufferNo)							//read byte(s) from buffer 2
	{
		DF_SPI_RW(Buf2Read);					//buffer 2 read op-code
		DF_SPI_RW(0x00);						//don't cares
		DF_SPI_RW((unsigned char)(IntPageAdr>>8));//upper part of internal buffer address
		DF_SPI_RW((unsigned char)(IntPageAdr));	//lower part of internal buffer address
		DF_SPI_RW(0x00);						//don't cares
		for( i=0; i<No_of_bytes; i++)
		{
			*(BufferPtr) = DF_SPI_RW(0x00);		//read byte and put it in AVR buffer pointed to by *BufferPtr
			BufferPtr++;						//point to next element in AVR buffer
		}
	}
	DF_CS_inactive;								//make sure to toggle CS signal in order
}
//NB : Sjekk at (IntAdr + No_of_bytes) < buffer size, hvis ikke blir det bare ball..



/*****************************************************************************
*
*	Function name : Buffer_Write_Enable
*
*	Returns :		None
*
*	Parameters :	IntPageAdr	->	Internal page address to start writing from
*					BufferAdr	->	Decides usage of either buffer 1 or 2
*					
*	Purpose :		Enables continous write functionality to one of the dataflash buffers
*					buffers. NOTE : User must ensure that CS goes high to terminate
*					this mode before accessing other dataflash functionalities
*
******************************************************************************/
void Buffer_Write_Enable (unsigned char BufferNo, unsigned int IntPageAdr)
{
  DF_CS_inactive;							//make sure to toggle CS signal in order	
	DF_CS_active;								//to reset dataflash command decoder
	
	if (1 == BufferNo)							//write enable to buffer 1
	{
		DF_SPI_RW(Buf1Write);					//buffer 1 write op-code
		DF_SPI_RW(0x00);						//don't cares
		DF_SPI_RW((unsigned char)(IntPageAdr>>8));//upper part of internal buffer address
		DF_SPI_RW((unsigned char)(IntPageAdr));	//lower part of internal buffer address
	}
	else
	if (2 == BufferNo)							//write enable to buffer 2
	{
		DF_SPI_RW(Buf2Write);					//buffer 2 write op-code
		DF_SPI_RW(0x00);						//don't cares
		DF_SPI_RW((unsigned char)(IntPageAdr>>8));//upper part of internal buffer address
		DF_SPI_RW((unsigned char)(IntPageAdr));	//lower part of internal buffer address
	}
	
	DF_CS_inactive;								//make sure to toggle CS signal in order
}



/*****************************************************************************
*
*	Function name : Buffer_Write_Byte
*
*	Returns :		None
*
*	Parameters :	IntPageAdr	->	Internal page address to write byte to
*					BufferAdr	->	Decides usage of either buffer 1 or 2
*					Data		->	Data byte to be written
*
*	Purpose :		Writes one byte to one of the dataflash
*					internal SRAM buffers
*
******************************************************************************/
void Buffer_Write_Byte (unsigned char BufferNo, unsigned int IntPageAdr, unsigned char Data)
{
	
  DF_CS_inactive;							//make sure to toggle CS signal in order	
	DF_CS_active;								//to reset dataflash command decoder
	
	if (1 == BufferNo)							//write byte to buffer 1
	{
		DF_SPI_RW(Buf1Write);					//buffer 1 write op-code
		DF_SPI_RW(0x00);						//don't cares
		DF_SPI_RW((unsigned char)(IntPageAdr>>8));//upper part of internal buffer address
		DF_SPI_RW((unsigned char)(IntPageAdr));	//lower part of internal buffer address
		DF_SPI_RW(Data);						//write data byte
	}
	else
	if (2 == BufferNo)							//write byte to buffer 2
	{
		DF_SPI_RW(Buf2Write);					//buffer 2 write op-code
		DF_SPI_RW(0x00);						//don't cares
		DF_SPI_RW((unsigned char)(IntPageAdr>>8));//upper part of internal buffer address
		DF_SPI_RW((unsigned char)(IntPageAdr));	//lower part of internal buffer address
		DF_SPI_RW(Data);						//write data byte
	}		
	DF_CS_inactive;								//make sure to toggle CS signal in order
}


/*****************************************************************************
*
*	Function name : Buffer_Write_Str
*
*	Returns :		None
*
*	Parameters :	BufferNo	->	Decides usage of either buffer 1 or 2
*					IntPageAdr	->	Internal page address
*					No_of_bytes	->	Number of bytes to be written
*					*BufferPtr	->	address of buffer to be used for copy of bytes
*									from AVR buffer to dataflash buffer 1 (or 2)
*
*	Purpose :		Copies one or more bytes to one of the dataflash
*					internal SRAM buffers from AVR SRAM buffer
*					pointed to by *BufferPtr
*
******************************************************************************/
void Buffer_Write_Str (unsigned char BufferNo, unsigned int IntPageAdr, unsigned int No_of_bytes, unsigned char *BufferPtr)
{
	unsigned int i;
  DF_CS_inactive;							//make sure to toggle CS signal in order
	DF_CS_active;								//to reset dataflash command decoder
	
	if (1 == BufferNo)							//write byte(s) to buffer 1
	{
		DF_SPI_RW(Buf1Write);					//buffer 1 write op-code
		DF_SPI_RW(0x00);						//don't cares
		DF_SPI_RW((unsigned char)(IntPageAdr>>8));//upper part of internal buffer address
		DF_SPI_RW((unsigned char)(IntPageAdr));	//lower part of internal buffer address
		for( i=0; i<No_of_bytes; i++)
		{
			DF_SPI_RW(*(BufferPtr));			//write byte pointed at by *BufferPtr to dataflash buffer 1 location
			BufferPtr++;						//point to next element in AVR buffer
		}
	}
	else
	if (2 == BufferNo)							//write byte(s) to buffer 2
	{
		DF_SPI_RW(Buf2Write);					//buffer 2 write op-code
		DF_SPI_RW(0x00);						//don't cares
		DF_SPI_RW((unsigned char)(IntPageAdr>>8));//upper part of internal buffer address
		DF_SPI_RW((unsigned char)(IntPageAdr));	//lower part of internal buffer address
		for( i=0; i<No_of_bytes; i++)
		{
			DF_SPI_RW(*(BufferPtr));			//write byte pointed at by *BufferPtr to dataflash buffer 2 location
			BufferPtr++;						//point to next element in AVR buffer
		}
	}
	DF_CS_inactive;								//make sure to toggle CS signal in order
}
//NB : Monitorer busy-flag i status-reg.
//NB : Sjekk at (IntAdr + No_of_bytes) < buffersize, hvis ikke blir det bare ball..



/*****************************************************************************
*
*	Function name : Buffer_To_Page
*
*	Returns :		None
*
*	Parameters :	BufferAdr	->	Decides usage of either buffer 1 or 2
*					PageAdr		->	Address of flash page to be programmed
*
*	Purpose :		Transfers a page from dataflash SRAM buffer to flash
*					
******************************************************************************/
void Buffer_To_Page (unsigned char BufferNo, unsigned int PageAdr)
{
  DF_CS_inactive;							//make sure to toggle CS signal in order
	DF_CS_active;												//to reset dataflash command decoder
		
	if (1 == BufferNo)											//program flash page from buffer 1
	{
		DF_SPI_RW(Buf1ToFlashWE);								//buffer 1 to flash with erase op-code
		DF_SPI_RW((unsigned char)(PageAdr >> (16 - PageBits)));	//upper part of page address
		DF_SPI_RW((unsigned char)(PageAdr << (PageBits - 8)));	//lower part of page address
		DF_SPI_RW(0x00);										//don't cares
	}
	else	
	if (2 == BufferNo)											//program flash page from buffer 2
	{
		DF_SPI_RW(Buf2ToFlashWE);								//buffer 2 to flash with erase op-code
		DF_SPI_RW((unsigned char)(PageAdr >> (16 - PageBits)));	//upper part of page address
		DF_SPI_RW((unsigned char)(PageAdr << (PageBits - 8)));	//lower part of page address
		DF_SPI_RW(0x00);										//don't cares
	}
	
	DF_CS_inactive;												//initiate flash page programming
	DF_CS_active;												
	
	while(!(Read_DF_status() & 0x80));							//monitor the status register, wait until busy-flag is high
	
	DF_CS_inactive;												//initiate flash page programming
}


/*****************************************************************************
*
*	Function name : Cont_Flash_Read_Enable
*
*	Returns :		None
*
*	Parameters :	PageAdr		->	Address of flash page where cont.read starts from
*					IntPageAdr	->	Internal page address where cont.read starts from
*
*	Purpose :		Initiates a continuous read from a location in the DataFlash
*					
******************************************************************************/
void Cont_Flash_Read_Enable (unsigned int PageAdr, unsigned int IntPageAdr)
{
	DF_CS_inactive;																//make sure to toggle CS signal in order
	DF_CS_active;												//to reset dataflash command decoder	
	DF_SPI_RW(ContArrayRead);													//Continuous Array Read op-code
	DF_SPI_RW((unsigned char)(PageAdr >> (16 - PageBits)));						//upper part of page address
	DF_SPI_RW((unsigned char)((PageAdr << (PageBits - 8))+ (IntPageAdr>>8)));	//lower part of page address and MSB of int.page adr.
	DF_SPI_RW((unsigned char)(IntPageAdr));										//LSB byte of internal page address
	DF_SPI_RW(0x00);															//perform 4 dummy writes
	DF_SPI_RW(0x00);															//in order to intiate DataFlash
	DF_SPI_RW(0x00);															//address pointers
	DF_SPI_RW(0x00);
	
  DF_CS_active;																//to reset dataflash command decoder
}

/*
page eraase
*/
void Page_Erase (unsigned int PageAdr)
{

	DF_CS_inactive;															//make sure to toggle CS signal in order
	DF_CS_active;																//to reset dataflash command decoder

  DF_SPI_RW(PageErase);
	DF_SPI_RW((unsigned char)(PageAdr >> (16 - PageBits)));	//upper part of page address
	DF_SPI_RW((unsigned char)(PageAdr << (PageBits - 8)));	//lower part of page address
  DF_SPI_RW(0x00);	
	
	DF_CS_inactive;																//make sure to toggle CS signal in order
}



/**
  * @}
  */

/**
  * @}
  */

/******************* (C) COPYRIGHT 2009 STMicroelectronics *****END OF FILE****/
