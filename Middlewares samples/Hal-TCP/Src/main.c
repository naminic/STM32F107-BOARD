/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "lwip.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "tcp.h"
#include "string.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
/* USER CODE BEGIN PFP */
void server_init				(u16_t port);
void 	server_conn_err		(void *arg, err_t err);
err_t server_recv				(void *arg, struct tcp_pcb *pcb, struct pbuf *p, err_t err);
err_t server_accept			(void *arg, struct tcp_pcb *pcb, err_t err);
char 	get_key_state			(void);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
#define KEYDEBOUNCE  	20
#define MAXDATALEN 		10	
#define LED1_ON  			'1'
#define LED2_ON				'2'		
#define LED3_ON				'3'
#define LED4_ON				'4'
#define LED1_OFF			'5'
#define LED2_OFF			'6'
#define LED3_OFF			'7'
#define LED4_OFF			'8'
#define GET_PB				'9'	
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */
  

  /* MCU Configuration--------------------------------------------------------*/

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
  MX_LWIP_Init();
  /* USER CODE BEGIN 2 */
  server_init(1000);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
		MX_LWIP_Process();
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the CPU, AHB and APB busses clocks 
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
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure the Systick interrupt time 
  */
  __HAL_RCC_PLLI2S_ENABLE();
}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, LED1_Pin|LED2_Pin|LED3_Pin|LED4_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : LED1_Pin LED2_Pin LED3_Pin LED4_Pin */
  GPIO_InitStruct.Pin = LED1_Pin|LED2_Pin|LED3_Pin|LED4_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : PB1_Pin PB2_Pin PB3_Pin PB4_Pin */
  GPIO_InitStruct.Pin = PB1_Pin|PB2_Pin|PB3_Pin|PB4_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */
/**
  * @brief  Called when a data is received on the server connection
  * @param  arg	the user argument
  * @param  pcb	the tcp_pcb that has received the data
  * @param  p	the packet buffer
  * @param  err	the error value linked with the received data
  * @retval error value
  */
err_t server_recv(void *arg, struct tcp_pcb *pcb, struct pbuf *p, err_t err)
{

	
  char *c;
  int i;
	char data_read[MAXDATALEN]={0};
	char data_send[MAXDATALEN]={0};
 

  /* We perform here any necessary processing on the pbuf */
  if (p != NULL) 
  {        
	/* We call this function to tell the LwIp that we have processed the data */
	/* This lets the stack advertise a larger window, so more data can be received*/
	tcp_recved(pcb, p->tot_len);
		
	c = p->payload;	
		
	for( i = 0 ; i < p->len ; i++)
  {
	  data_read[i] = c[i];
	}		
	
	switch (data_read[0])
	{
	  case LED1_ON:
			HAL_GPIO_WritePin(LED1_GPIO_Port,LED1_Pin,1);
			break;
		case LED2_ON:
			HAL_GPIO_WritePin(LED2_GPIO_Port,LED2_Pin,1);
			break;
		case LED3_ON:
			HAL_GPIO_WritePin(LED3_GPIO_Port,LED3_Pin,1);
			break;
		case LED4_ON:
			HAL_GPIO_WritePin(LED4_GPIO_Port,LED4_Pin,1);
			break;
		case LED1_OFF:
			HAL_GPIO_WritePin(LED1_GPIO_Port,LED1_Pin,0);
			break;
		case LED2_OFF:
			HAL_GPIO_WritePin(LED2_GPIO_Port,LED2_Pin,0);
			break;
		case LED3_OFF:
			HAL_GPIO_WritePin(LED3_GPIO_Port,LED3_Pin,0);
			break;
		case LED4_OFF:
			HAL_GPIO_WritePin(LED4_GPIO_Port,LED4_Pin,0);
			break;
		case GET_PB:
			sprintf(data_send,"%d",get_key_state());
		  tcp_write(pcb,data_send,strlen(data_send),1);
			break;
	}


	
	/* End of processing, we free the pbuf */
    pbuf_free(p);
  }  
  else if (err == ERR_OK) 
  {
    /* When the pbuf is NULL and the err is ERR_OK, the remote end is closing the connection. */
    /* We close the connection */
    return tcp_close(pcb);
  }
  return ERR_OK;


}

/**
  * @brief  This function when the server connection is established
  * @param  arg  user supplied argument 
  * @param  pcb	 the tcp_pcb which accepted the connection
  * @param  err	 error value
  * @retval ERR_OK
  */
err_t server_accept(void *arg, struct tcp_pcb *pcb, err_t err)
{     
  /* Configure LwIP to use our call back functions. */
  tcp_err(pcb, server_conn_err);
  tcp_recv(pcb, server_recv);
  return ERR_OK;
}

/**
  * @brief  Initialize the server application  
  * @param  None 
  * @retval None 
  */
void server_init(u16_t port)
{
  struct tcp_pcb *pcb;	            		
  
  /* Create a new TCP control block  */
  pcb = tcp_new();	                		 	

  /* Assign to the new pcb a local IP address and a port number */
  /* Using IP_ADDR_ANY allow the pcb to be used by any local interface */
  tcp_bind(pcb, IP_ADDR_ANY, port);       


  /* Set the connection to the LISTEN state */
  pcb = tcp_listen(pcb);				

  /* Specify the function to be called when a connection is established */	
  tcp_accept(pcb, server_accept);   
										
}

/**
  * @brief  This function is called when an error occurs on the connection 
  * @param  arg
  * @parm   err
  * @retval None 
  */
void server_conn_err(void *arg, err_t err)
{
  struct name *name;
  name = (struct name *)arg;

  mem_free(name);
}


char get_key_state(void)
{
  if(!HAL_GPIO_ReadPin(PB1_GPIO_Port,PB1_Pin))
	{
		HAL_Delay(KEYDEBOUNCE);
		if(!HAL_GPIO_ReadPin(PB1_GPIO_Port,PB1_Pin))
		{	
		 while(!HAL_GPIO_ReadPin(PB1_GPIO_Port,PB1_Pin)); 	
		 return 1;
		}			
	}	
	
  if(!HAL_GPIO_ReadPin(PB2_GPIO_Port,PB2_Pin))
	{
		HAL_Delay(KEYDEBOUNCE);
		if(!HAL_GPIO_ReadPin(PB2_GPIO_Port,PB2_Pin))
		{	
		 while(!HAL_GPIO_ReadPin(PB2_GPIO_Port,PB2_Pin)); 	
		 return 2;
		}	
	}

  if(!HAL_GPIO_ReadPin(PB3_GPIO_Port,PB3_Pin))
	{
		HAL_Delay(KEYDEBOUNCE);
		if(!HAL_GPIO_ReadPin(PB3_GPIO_Port,PB3_Pin))
		{	
		 while(!HAL_GPIO_ReadPin(PB3_GPIO_Port,PB3_Pin)); 	
		 return 3;
		}		
	}

  if(!HAL_GPIO_ReadPin(PB4_GPIO_Port,PB4_Pin))
	{
		HAL_Delay(KEYDEBOUNCE);
		if(!HAL_GPIO_ReadPin(PB4_GPIO_Port,PB4_Pin))
		{	
		 while(!HAL_GPIO_ReadPin(PB4_GPIO_Port,PB4_Pin)); 	
		 return 4;
		}	
	}

  return 0;	
}	
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

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
void assert_failed(uint8_t *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
