#include "bsp.h"

GPIO_InitTypeDef GPIO_InitStructure;

void RCC_Configuration(void); 
void GPIO_Configuration(void);
  
int main(void)
{
  RCC_Configuration();
  GPIO_Configuration();
	while(1)
	{
		if(GPIO_ReadInputDataBit(KEY1_GPIO_PORT,KEY1_PIN) == 0){
			GPIO_SetBits(LED1_GPIO_PORT,LED1_PIN);	
		}
		else if (GPIO_ReadInputDataBit(KEY1_GPIO_PORT,KEY1_PIN) == 1)
			GPIO_ResetBits(LED1_GPIO_PORT,LED1_PIN);
   //----------------------------------------------------------
    if(GPIO_ReadInputDataBit(KEY2_GPIO_PORT,KEY2_PIN) == 0){
			GPIO_SetBits(LED2_GPIO_PORT,LED2_PIN);
		}			
		else if (GPIO_ReadInputDataBit(KEY2_GPIO_PORT,KEY2_PIN) == 1)
			GPIO_ResetBits(LED2_GPIO_PORT,LED2_PIN);
   //----------------------------------------------------------	
    if(GPIO_ReadInputDataBit(KEY3_GPIO_PORT,KEY3_PIN) == 0){
			GPIO_SetBits(LED3_GPIO_PORT,LED3_PIN);	
		}
		else if (GPIO_ReadInputDataBit(KEY3_GPIO_PORT,KEY3_PIN) == 1)
			GPIO_ResetBits(LED3_GPIO_PORT,LED3_PIN);
   //----------------------------------------------------------	
	  if(GPIO_ReadInputDataBit(KEY4_GPIO_PORT,KEY4_PIN) == 0){
			GPIO_SetBits(LED4_GPIO_PORT,LED4_PIN);	
		}
		else if (GPIO_ReadInputDataBit(KEY4_GPIO_PORT,KEY4_PIN) == 1)
			GPIO_ResetBits(LED4_GPIO_PORT,LED4_PIN);
   //----------------------------------------------------------	
	}
	
  return 0;
}

/*--------------------------------------- Configuration functions----------------------------------------------------------*/

void RCC_Configuration(void){
	RCC_APB2PeriphClockCmd(KEY1_GPIO_CLK|KEY2_GPIO_CLK|KEY3_GPIO_CLK|KEY4_GPIO_CLK , ENABLE);
}


void GPIO_Configuration(void){

  /* Configure LED1 in output pushpull mode */
  GPIO_InitStructure.GPIO_Pin = LED1_PIN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(LED1_GPIO_PORT, &GPIO_InitStructure);

	 /* Configure LED2 in output pushpull mode */
  GPIO_InitStructure.GPIO_Pin = LED2_PIN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(LED2_GPIO_PORT, &GPIO_InitStructure);
	
	 /* Configure LED3 in output pushpull mode */
  GPIO_InitStructure.GPIO_Pin = LED3_PIN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(LED3_GPIO_PORT, &GPIO_InitStructure);
	
		 /* Configure LED4 in output pushpull mode */
  GPIO_InitStructure.GPIO_Pin = LED4_PIN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(LED4_GPIO_PORT, &GPIO_InitStructure);
	
  //-----------------------------------------------------
	  /* Configure Keysclock */

		/* Configure KEY1  in input pullup mode */
	GPIO_InitStructure.GPIO_Pin = KEY1_PIN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_Init(KEY1_GPIO_PORT, &GPIO_InitStructure);	
		/* Configure KEY2  in input pullup mode */
	GPIO_InitStructure.GPIO_Pin = KEY2_PIN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_Init(KEY2_GPIO_PORT, &GPIO_InitStructure);	
		/* Configure KEY3  in input pullup mode */
	GPIO_InitStructure.GPIO_Pin = KEY3_PIN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_Init(KEY3_GPIO_PORT, &GPIO_InitStructure);	
		/* Configure KEY4  in input pullup mode */
	GPIO_InitStructure.GPIO_Pin = KEY4_PIN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_Init(KEY4_GPIO_PORT, &GPIO_InitStructure);	

}

