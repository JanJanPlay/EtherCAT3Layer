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
uint8_t recvtimeout = 0;	//��צ���ǰ��ֽڷ������ݵ� ����Ҫͨ����ʱ�ķ����ж�֡����
uint8_t sendflag = 0;		//���Ϳ���ָ���־(10)


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
	
	/* ���� HAL_TIM_Base_MspInit ���жϺ��� ָ���ж����ȼ�*/
	HAL_TIM_Base_Init(&htim2);
	/* USER CODE BEGIN TIM2_Init 2 */

	/* USER CODE END TIM2_Init 2 */

}

/* ��ʱ���жϻص����� */
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

