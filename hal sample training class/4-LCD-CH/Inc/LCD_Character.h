
#include "main.h"

/*

RS » PE[8]
E   » PE[4]
D4 » PE[0]
D5 » PE[1]
D6 » PE[2]
D7 » PE[3]
*/


#define LCD_Command     1
#define LCD_Data        2

#define RS0             HAL_GPIO_WritePin(GPIOE,LCD_RS_Pin,GPIO_PIN_RESET)
#define RS1             HAL_GPIO_WritePin(GPIOE,LCD_RS_Pin,GPIO_PIN_SET)

#define E0             HAL_GPIO_WritePin(GPIOE,LCD_E_Pin,GPIO_PIN_RESET)
#define E1             HAL_GPIO_WritePin(GPIOE,LCD_E_Pin,GPIO_PIN_SET)

void LCD_Init(void);
void Send_to_LCD(unsigned char Byte , unsigned char DataORCommand);
void LCD_GotoXY(unsigned char x , unsigned char y);
void WriteString2LCD(char *buf);
void LCD_Clear(void);
