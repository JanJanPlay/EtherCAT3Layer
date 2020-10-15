/*
2020.10.13
Author:Jan
参考cubemx can网上教程编写
https://blog.csdn.net/u012308586/article/details/81001102
*/

#include "esc_can.h"

CAN_HandleTypeDef hcan1;
CAN_TxHeaderTypeDef Tx_Mesg;
CAN_RxHeaderTypeDef Rx_Mesg;
uint8_t CAN_Rx_Flag = 0;

/* 用户初始化函数 初始化CAN过滤器 */
void CAN_User_Init(CAN_HandleTypeDef* hcan)
{
	CAN_FilterTypeDef  sFilterConfig;
	HAL_StatusTypeDef  HAL_Status;

	Tx_Mesg.IDE=CAN_ID_STD;
	Tx_Mesg.RTR=CAN_RTR_DATA;
	/* 0~13 14~27 */
	sFilterConfig.FilterBank = 0;  
	/* filter 列表模式 */	
	sFilterConfig.FilterMode = CAN_FILTERMODE_IDMASK;	//CAN_FILTERMODE_IDMASK CAN_FILTERMODE_IDLIST
	sFilterConfig.FilterScale = CAN_FILTERSCALE_32BIT;	//CAN_FILTERSCALE_32BIT CAN_FILTERSCALE_16BIT

	sFilterConfig.FilterIdHigh = 1<<5;   	
	sFilterConfig.FilterIdLow = 0;    

	sFilterConfig.FilterMaskIdHigh = 1<<5;
	sFilterConfig.FilterMaskIdLow = 0; 
	sFilterConfig.FilterFIFOAssignment = CAN_RX_FIFO0;   

	sFilterConfig.FilterActivation = ENABLE;  	
	sFilterConfig.SlaveStartFilterBank = 0; 

	HAL_Status=HAL_CAN_ConfigFilter(hcan,&sFilterConfig);
	HAL_Status=HAL_CAN_Start(hcan);  
	if(HAL_Status!=HAL_OK){

	}
	
	HAL_Status=HAL_CAN_ActivateNotification(hcan,CAN_IT_RX_FIFO0_MSG_PENDING);
	if(HAL_Status!=HAL_OK){

	}
}

void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)  //CAN接收回调函数
{
	uint8_t Data[8];
//	uint8_t tx_buf[]="can test";
//	uint8_t result;
	HAL_StatusTypeDef HAL_RetVal;
	
	if(hcan ==&hcan1){	
		HAL_RetVal=HAL_CAN_GetRxMessage(hcan,CAN_RX_FIFO0,&Rx_Mesg,Data);
		if(HAL_OK==HAL_RetVal){ 
			//直接调用发送函数会出错
//			result = CANx_SendNormalData(hcan,0xAA,tx_buf,8);
			CAN_Rx_Flag = 1;
		}
	}
}

uint8_t CANx_SendNormalData(CAN_HandleTypeDef* hcan,uint16_t ID,uint8_t *pData,uint16_t Len)
{
	HAL_StatusTypeDef HAL_RetVal;
	uint16_t SendTimes,SendCNT=0;
	uint8_t  FreeTxNum=0;
	Tx_Mesg.StdId=ID;
	
	if(!hcan || ! pData ||!Len)  return 1;
	
	SendTimes=Len/8+(Len%8?1:0);
	FreeTxNum=HAL_CAN_GetTxMailboxesFreeLevel(hcan);
	Tx_Mesg.DLC=8;
	
	while(SendTimes--){
		if(0==SendTimes){
			if(Len%8)
			Tx_Mesg.DLC=Len%8;
		}
		while(0==FreeTxNum){
			FreeTxNum=HAL_CAN_GetTxMailboxesFreeLevel(hcan);
		}
		HAL_Delay(1);   //没有延时可能会发送失败
		HAL_RetVal=HAL_CAN_AddTxMessage(hcan,&Tx_Mesg,pData+SendCNT,(uint32_t*)CAN_TX_MAILBOX0); 
		if(HAL_RetVal!=HAL_OK)
		{
			return 2;
		}
		SendCNT+=8;
	}

	return 0;
}


/**
  * @brief CAN1 Initialization Function
  * @param None
  * @retval None
  */
void MX_CAN1_Init(void)
{
	hcan1.Instance = CAN1;
	hcan1.Init.Prescaler = 7;	
	hcan1.Init.Mode = CAN_MODE_NORMAL;
	hcan1.Init.SyncJumpWidth = CAN_SJW_1TQ;
	hcan1.Init.TimeSeg1 = CAN_BS1_5TQ;	
	hcan1.Init.TimeSeg2 = CAN_BS2_6TQ;	
	hcan1.Init.TimeTriggeredMode = DISABLE;
	hcan1.Init.AutoBusOff = DISABLE;
	hcan1.Init.AutoWakeUp = DISABLE;
	hcan1.Init.AutoRetransmission = DISABLE;
	hcan1.Init.ReceiveFifoLocked = DISABLE;
	hcan1.Init.TransmitFifoPriority = DISABLE;
	if (HAL_CAN_Init(&hcan1) != HAL_OK)
	{
		Error_Handler();
	}
}
