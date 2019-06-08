#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "spi_flash.h"
#include "string.h"

void writeData(unsigned int PageAdr,unsigned char *buffer)
{
  Buffer_Write_Str(1,PageAdr,528,buffer);
  Buffer_To_Page(1,PageAdr);
}
void readData(unsigned int PageAdr,unsigned char *buffer)
{
  Page_To_Buffer(PageAdr,1);
  Buffer_Read_Str(1,PageAdr,528,buffer);
}


int main(void)
{
	uint8_t buff[528];
	
	SystemInit();
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	
	SPI_FLASH_Init();

  Read_DF_status();
	
	memset(buff,0x40,sizeof(buff));

  writeData(10,buff);

  //Buffer_Write_Enable(0,1);

  memset(buff,0x00,sizeof(buff));

  readData(10,buff);

  Page_Erase(10);

  readData(10,buff);	
while (1);	
return 0;
}