//
// Created by Tang on 2026/8/9.
//

#include "can_bus.h"

extern FDCAN_HandleTypeDef hfdcan1;
FDCAN_TxHeaderTypeDef txHeader;

void CAN_Init() {
    txHeader.IdType = FDCAN_STANDARD_ID;
    txHeader.TxFrameType = FDCAN_DATA_FRAME;
    txHeader.DataLength = FDCAN_DLC_BYTES_8;
    txHeader.ErrorStateIndicator = FDCAN_ESI_ACTIVE;
    txHeader.BitRateSwitch = FDCAN_BRS_OFF;
    txHeader.FDFormat = FDCAN_CLASSIC_CAN;
    txHeader.TxEventFifoControl = FDCAN_NO_TX_EVENTS;
    txHeader.MessageMarker = 0;

    if (HAL_FDCAN_Start(&hfdcan1) != HAL_OK) {
        Error_Handler();
    }
}



void CAN_Send(const uint16_t id, const uint8_t *data) {

    if ( id > 0x7FF ) return;
    txHeader.Identifier = id;

    HAL_FDCAN_AddMessageToTxFifoQ(&hfdcan1, &txHeader, data);

}


