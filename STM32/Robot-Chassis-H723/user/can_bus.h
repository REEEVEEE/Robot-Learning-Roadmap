//
// Created by Tang on 2026/8/9.
//

#ifndef ROBOT_CHASSIS_H723_CAN_BUS_H
#define ROBOT_CHASSIS_H723_CAN_BUS_H

#include "fdcan.h"

void CAN_Init(void);
void CAN_Send(uint16_t id, const uint8_t *data);

#endif //ROBOT_CHASSIS_H723_CAN_BUS_H