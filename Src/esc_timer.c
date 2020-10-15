/*
2020.10.13
Author:Jan
*/

#include "esc_timer.h"
#include "main.h"
#include "ecatappl.h"
#include "user_app.h"
#include "esc_uart.h"

TIM_HandleTypeDef htim2;
uint8_t recvtimeout = 0;	//夹爪端是按字节返回数据的 所以要通过超时的方法判断帧结束
uint8_t sendflag = 0;		//发送控制指令标志(10)


/**
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
void MX_TIM2_Init(void)
{
	/* USER CODE BEGIN TIM2_Init 0 */

	/* USER CODE END TIM2_Init 0 */

	/* USER CODE BEGIN TIM2_Init 1 */

	/* USER CODE END TIM2_Init 1 */
	htim2.Instance = TIM2;
	htim2.Init.Prescaler = 41;		//41
	htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim2.Init.Period = 2000;			//2000
	htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	
	/* 调用 HAL_TIM_Base_MspInit 绑定中断函数 指定中断优先级*/
	HAL_TIM_Base_Init(&htim2);
	/* USER CODE BEGIN TIM2_Init 2 */

	/* USER CODE END TIM2_Init 2 */

}

/* 定时器中断回调函数 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	static uint32_t count;
	
    if(htim==(&htim2))
    {
        ECAT_CheckTimer();
		
		if(count++==25)
			CheckStatus();
		if(count==50) {
			sendflag = 1;
			count = 0;
		}
		
		if(recvtimeout>0) {
			if(--recvtimeout==0) {
				UART6_IDLECallBack();
			}
		}
    }
}

