/**********************************************************************
* Filename:             main.c
* Project:              DefaultProject
* Version: 		        2.0.0
* Chip type:            STM32F107VC-CortexM3
* PLL freq:		        
* CPU freq:		        
* Author: 	            Mostafa Tavallodi Sharif - 09391671368
* Company: 		        
* Creation Date:        
* Creation Time:        
* Description:          
**********************************************************************/

#include "stm32f10x.h"
#include "delay.h"
#include "rtl.h"
#include "stdio.h"
#include "string.h"

U8 udp_soc;

U16 udp_callback (U8 socket, U8 *remip, U16 remport, U8 *buf, U16 len) 
{
  /* This function is called when UDP data is received */

  /* Process received data from 'buf' */

  return (0);
}

/*********************************************************************
* @brief
* @param[in]
* @return
*********************************************************************/
int main(void)
{
    char udp_msg[] = {"Hello World!"};
    U8 remip[4] = {192,168,0,1};
    U8 *sendbuf;
    U16 len;     
    init_TcpNet();

    udp_soc = udp_get_socket (0, UDP_OPT_SEND_CS | UDP_OPT_CHK_CS, udp_callback);
    if (udp_soc != 0) 
    {
        /* Open UDP port 1000 for communication */
        udp_open (udp_soc, 1000);
    }

    while(1)
	{
        main_TcpNet();
        len = strlen (udp_msg);
        sendbuf = udp_get_buf (len);
        strcpy (sendbuf, udp_msg);
        /* Send 'Hello World!' to remote peer */
        udp_send (udp_soc, remip, 1000, sendbuf, len);        
        delayMs(100);
	}
}
