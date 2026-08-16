//
// Created by Tang on 2026/8/9.
//

#include "can_bus.h"
#include "m3508.h"
#include "cmsis_os2.h"
#include "motor_manager.h"

extern osMessageQueueId_t CanRxQueueHandle;
extern FDCAN_HandleTypeDef hfdcan1;
FDCAN_TxHeaderTypeDef txHeader;
FDCAN_FilterTypeDef filter;
uint8_t RX_Buffer[8];

void CAN_Init() {
    //发送帧配置
    txHeader.IdType = FDCAN_STANDARD_ID;
    txHeader.TxFrameType = FDCAN_DATA_FRAME;
    txHeader.DataLength = FDCAN_DLC_BYTES_8;
    txHeader.ErrorStateIndicator = FDCAN_ESI_ACTIVE;
    txHeader.BitRateSwitch = FDCAN_BRS_OFF;
    txHeader.FDFormat = FDCAN_CLASSIC_CAN;
    txHeader.TxEventFifoControl = FDCAN_NO_TX_EVENTS;
    txHeader.MessageMarker = 0;

    //滤波器配置
    filter.IdType = FDCAN_STANDARD_ID;
    filter.FilterIndex = 0;
    filter.FilterType = FDCAN_FILTER_RANGE;
    filter.FilterConfig = FDCAN_FILTER_TO_RXFIFO1;
    filter.FilterID1 = 0x201;
    filter.FilterID2 = 0x204;

    if (HAL_FDCAN_ConfigFilter(&hfdcan1, &filter) != HAL_OK) {
        Error_Handler();
    }

    if (HAL_FDCAN_ConfigGlobalFilter(&hfdcan1, FDCAN_REJECT, FDCAN_REJECT, FDCAN_REJECT_REMOTE, FDCAN_REJECT_REMOTE ) != HAL_OK) {
        Error_Handler();
    }

    if (HAL_FDCAN_Start(&hfdcan1) != HAL_OK) {
        Error_Handler();
    }

    if (HAL_FDCAN_ActivateNotification(&hfdcan1, FDCAN_IT_RX_FIFO1_NEW_MESSAGE, 0) != HAL_OK) {
        Error_Handler();
    }
}



void CAN_Send(const uint16_t id, const uint8_t *data) {

    if ( id > 0x7FF ) return;
    txHeader.Identifier = id;

    if (HAL_FDCAN_AddMessageToTxFifoQ(&hfdcan1, &txHeader, data) != HAL_OK) {
        Error_Handler();
    }

}

void HAL_FDCAN_RxFifo1Callback(FDCAN_HandleTypeDef *hfdcan, uint32_t RxFifo1ITs) {
    if (hfdcan != &hfdcan1) return;

    if ((RxFifo1ITs & FDCAN_IT_RX_FIFO1_NEW_MESSAGE) == 0) return;

    FDCAN_RxHeaderTypeDef rxHeader;
    CanRxMessage_t rxMessage;

    if (HAL_FDCAN_GetRxMessage(hfdcan, FDCAN_RX_FIFO1, &rxHeader, rxMessage.data) != HAL_OK) {
        return;
    }

    rxMessage.id = rxHeader.Identifier;

    osMessageQueuePut(CanRxQueueHandle, &rxMessage, 0U, 0U);


}

