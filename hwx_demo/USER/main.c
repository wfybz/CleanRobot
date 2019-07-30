/**
  ******************************************************************************
  * @file    Project/STM32F10x_StdPeriph_Template/main.c 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */  

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include <stdio.h>
#include "uart.h"
#include "adc.h"

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
	
void my_delay(__IO uint32_t nCount)
{
	for( ; nCount != 0; --nCount);
}
int main(void)
{
	unsigned char cmd;
	unsigned char help_flag = 1;
	float ADC_ConvValLocal = 0;
	
	UART1_Config();
	UART2_NVIC_Configuration();
	UART2_Config();
	ADC1_Config();
	
	while (1)
  {
		if(help_flag) {
			help_flag = 0;
			printf("******************************************************\n");
			printf("******************* Input Command ********************\n");
			printf("***** 1 ....................... Display Command  *****\n");
			printf("***** 2 ....................... Test ChaoShengBo *****\n");
			printf("***** 3 ....................... Test HongWaiXian *****\n");
			printf("******************************************************\n");
		}		
		cmd = uart_rx(USART1);
		printf("recv cmd: %02x\n",cmd);
		switch(cmd) {
			case 1:
				help_flag = 1;
				break;
			
			case 2:
				uart_tx(USART2, 0x55);
				break;
			
			case 3:
				ADC_ConvValLocal = (float)ADC_ConvertedVal/4096*3.3;
				printf("The Current ADC_Convertedval is %u\n", ADC_ConvertedVal);
				printf("The Current ADC_ConvValLocal is %f\n", ADC_ConvValLocal);
				my_delay(0xFFFFF);
				break;
			
			default:
				printf("Invalid Command!\n");
			break;
		} //end switch
	}//wnd while
}

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
















