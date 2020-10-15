/*
2020.09.16
Author:Jan
*/

#include "main.h"
#include "ecatappl.h"
#include "el9800hw.h"

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if(GPIO_Pin == ESC_IRQ_Pin)		//PC0
	{
		PDI_Isr();
	}
	if(GPIO_Pin == ESC_SYNC1_Pin)	//PC1
	{
		DISABLE_ESC_INT();
		Sync1_Isr();
		ENABLE_ESC_INT();
	}
	if(GPIO_Pin == ESC_SYNC0_Pin)	//PC3
	{
		DISABLE_ESC_INT();
		Sync0_Isr();
		ENABLE_ESC_INT();
	}
}
