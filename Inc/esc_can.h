#ifndef _ESC_CAN_H_
#define _ESC_CAN_H_

#include "main.h"

void CAN_User_Init(CAN_HandleTypeDef* hcan);
uint8_t CANx_SendNormalData(CAN_HandleTypeDef* hcan,uint16_t ID,uint8_t *pData,uint16_t Len);
void MX_CAN1_Init(void);

#endif

