/**
  ******************************************************************************
  * @file    SPI/M25P64_FLASH/spi_flash.h
  * @author  MCD Application Team
  * @version V3.1.2
  * @date    09/28/2009
  * @brief   Header for spi_flash.c file.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __SPI_FLASH_H
#define __SPI_FLASH_H

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f1xx_hal.h"
#include "stm32f1xx_ll_gpio.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Uncomment the line corresponding to the STMicroelectronics evaluation board
   used to run the example */



//Dataflash opcodes
#define FlashPageRead							0x52	// Main memory page read
#define FlashToBuf1Transfer 			0x53	// Main memory page to buffer 1 transfer
#define Buf1Read									0x54	// Buffer 1 read
#define FlashToBuf2Transfer 			0x55	// Main memory page to buffer 2 transfer
#define Buf2Read									0x56	// Buffer 2 read
#define StatusReg									0x57	// Status register
#define AutoPageReWrBuf1					0x58	// Auto page rewrite through buffer 1
#define AutoPageReWrBuf2					0x59	// Auto page rewrite through buffer 2
#define FlashToBuf1Compare    		0x60	// Main memory page to buffer 1 compare
#define FlashToBuf2Compare	    	0x61	// Main memory page to buffer 2 compare
#define ContArrayRead							0x68	// Continuous Array Read (Note : Only A/B-parts supported)
#define FlashProgBuf1							0x82	// Main memory page program through buffer 1
#define Buf1ToFlashWE   					0x83	// Buffer 1 to main memory page program with built-in erase
#define Buf1Write									0x84	// Buffer 1 write
#define FlashProgBuf2							0x85	// Main memory page program through buffer 2
#define Buf2ToFlashWE   					0x86	// Buffer 2 to main memory page program with built-in erase
#define Buf2Write									0x87	// Buffer 2 write
#define Buf1ToFlash     					0x88	// Buffer 1 to main memory page program without built-in erase
#define Buf2ToFlash		         		0x89	// Buffer 2 to main memory page program without built-in erase
#define PageErase                 0x81

/* Exported macro ------------------------------------------------------------*/

#define DF_CS_inactive    HAL_GPIO_WritePin(CS_GPIO_Port, CS_Pin, GPIO_PIN_SET);//HAL_GPIO_WritePin(CS_GPIO_Port, CS_Pin,GPIO_PIN_SET);
#define DF_CS_active      HAL_GPIO_WritePin(CS_GPIO_Port, CS_Pin, GPIO_PIN_RESET);



/* Exported functions --------------------------------------------------------*/
/*----- High layer function -----*/
//Function definitions
unsigned char       DF_SPI_RW                       (unsigned char output);
unsigned char       Read_DF_status                  (void);
void                Page_To_Buffer                  (unsigned int PageAdr, unsigned char BufferNo);
unsigned char       Buffer_Read_Byte                (unsigned char BufferNo, unsigned int IntPageAdr);
void                Buffer_Read_Str                 (unsigned char BufferNo, unsigned int IntPageAdr, unsigned int No_of_bytes, unsigned char *BufferPtr);
void                Buffer_Write_Enable             (unsigned char BufferNo, unsigned int IntPageAdr);
void                Buffer_Write_Byte               (unsigned char BufferNo, unsigned int IntPageAdr, unsigned char Data);
void                Buffer_Write_Str                (unsigned char BufferNo, unsigned int IntPageAdr, unsigned int No_of_bytes, unsigned char *BufferPtr);
void                Buffer_To_Page                  (unsigned char BufferNo, unsigned int PageAdr);
void                Cont_Flash_Read_Enable          (unsigned int PageAdr, unsigned int IntPageAdr);
void                Page_Erase                      (unsigned int PageAdr);

#endif /* __SPI_FLASH_H */

/******************* (C) COPYRIGHT 2009 STMicroelectronics *****END OF FILE****/
