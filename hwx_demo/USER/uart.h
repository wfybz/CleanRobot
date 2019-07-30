#ifndef __UART_H__
#define __UART_H__

#include "stm32f10x.h"
#include <stdio.h>

typedef enum uart_csb {
	HALF = 1,
	FULL,
} UART_CSB_E;

typedef struct _uart_csb {
	UART_CSB_E  status;
	unsigned short distance;
}uart_csb_t;

extern uart_csb_t UartCsbVal;

void UART1_Config(void);
void UART2_Config(void);
void UART2_NVIC_Configuration(void);
unsigned char uart_tx(USART_TypeDef *USARTx, unsigned char ch);
unsigned char uart_rx(USART_TypeDef* USARTx);
int fputc(int ch, FILE* f);

#endif
