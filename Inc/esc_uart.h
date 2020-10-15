
#ifndef _ESC_UART_H_
#define _ESC_UART_H_

#include "stm32f4xx_hal.h"
#include "stdio.h"

void MX_USART6_UART_Init(void);
void UartSend(uint8_t *buf,uint16_t len);
void UART6_IDLECallBack(void);

#endif




