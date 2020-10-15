/*
2020.10.13
Author:Jan
*/

#include "esc_uart.h"
#include "main.h"
#include "el9800appl.h"

UART_HandleTypeDef huart6;

static uint8_t uart_buf[128];

static uint8_t* pBuff=uart_buf;
static uint8_t ctn=0;

#if 1
#pragma import(__use_no_semihosting)             
//标准库需要的支持函数                 
struct __FILE 
{ 
	int handle; 
}; 

FILE __stdout;       
//定义_sys_exit()以避免使用半主机模式    
void _sys_exit(int x) 
{ 
	x = x; 
} 
//重定义fputc函数 
int fputc(int ch, FILE *f)
{ 	
	while((USART6->SR&0X40)==0);//循环发送,直到发送完毕   
	USART6->DR = (uint8_t) ch;      
	return ch;
}
#endif 

/**
  * @brief USART6 Initialization Function
  * @param None
  * @retval None
  */
void MX_USART6_UART_Init(void)
{

	/* USER CODE BEGIN USART6_Init 0 */

	/* USER CODE END USART6_Init 0 */

	/* USER CODE BEGIN USART6_Init 1 */

	/* USER CODE END USART6_Init 1 */
	huart6.Instance = USART6;
	huart6.Init.BaudRate = 115200;
	huart6.Init.WordLength = UART_WORDLENGTH_8B;
	huart6.Init.StopBits = UART_STOPBITS_1;
	huart6.Init.Parity = UART_PARITY_NONE;
	huart6.Init.Mode = UART_MODE_TX_RX;
	huart6.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart6.Init.OverSampling = UART_OVERSAMPLING_16;
	if (HAL_UART_Init(&huart6) != HAL_OK)
	{
		Error_Handler();
	}
	/* USER CODE BEGIN USART6_Init 2 */

	/* USER CODE END USART6_Init 2 */

}

/* 串口发送函数 */
void UartSend(uint8_t *buf,uint16_t len)
{
	HAL_UART_Transmit(&huart6,buf,len,0x1000);					//发送接收到的数据
	while(__HAL_UART_GET_FLAG(&huart6,UART_FLAG_TC)!=SET);		//等待发送结束
}

/* 空闲中断回调函数 解析数据帧 */
extern uint16_t CRC16(const uint8_t *nData, uint16_t wLength);
void UART6_IDLECallBack(/*uint8_t *buff,uint8_t size*/)
{
	uint16_t crc;
	uint8_t i;
	
	/* 1.crc校验 */
	crc = CRC16(uart_buf,ctn-2);
	if((uart_buf[ctn-2]&0xff) + (uart_buf[ctn-1]<<8&0xff00) == crc) {
	/* 2.将接收的数据赋值到结构体 */
		if(uart_buf[1]==0x03 && ctn==21) {
			
			for(i=0;i<8;i++) {
				((uint16_t*)&sFeedBack.init)[i] = (uart_buf[3+2*i]<<8&0xff00)+uart_buf[4+2*i];
			}
		}
	}
	
	ctn=0;
	pBuff=uart_buf;
}

/* 串口空闲中断数据接收函数 esc_timer.c中定义 */
extern uint8_t recvtimeout;
void UART_IDLE_Handle(void)
{
	if(__HAL_UART_GET_FLAG(&huart6, UART_FLAG_RXNE) != RESET)
	{	
		uint8_t ch=(uint16_t) READ_REG(huart6.Instance->DR);
		*(pBuff++)=ch;
		ctn++;
		recvtimeout = 5;
		__HAL_UART_CLEAR_FLAG(&huart6,UART_FLAG_RXNE);
	}
	if(__HAL_UART_GET_FLAG(&huart6, UART_FLAG_IDLE) != RESET)
	{
		__HAL_UART_CLEAR_IDLEFLAG(&huart6);
	}
}
