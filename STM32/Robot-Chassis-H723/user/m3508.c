//
// Created by Tang on 2026/8/9.
//

#include "m3508.h"
#include "can_bus.h"

static uint8_t Current_Data[8];

void M3508_Init(M3508_t *motor, uint16_t id) {
    motor->id = id;
    motor->targetCurrent = 0;
    motor->targetSpeed = 0;

    motor->angle = 0;
    motor->speed = 0;
    motor->current = 0;
    motor->temperature = 0;
}

void M3508_SetCurrent(M3508_t *motor, int16_t current) {
    motor->targetCurrent = current;
}

void M3508_SendCurrent(const M3508_t *motor1, const M3508_t *motor2, const M3508_t *motor3, const M3508_t *motor4) {

    const uint16_t value1 = (uint16_t) motor1->targetCurrent;
    const uint16_t value2 = (uint16_t) motor2->targetCurrent;
    const uint16_t value3 = (uint16_t) motor3->targetCurrent;
    const uint16_t value4 = (uint16_t) motor4->targetCurrent;

    Current_Data[0] = (uint8_t)(value1 >> 8);
    Current_Data[1] = (uint8_t)(value1 & 0xFF);
    Current_Data[2] = (uint8_t)(value2 >> 8);
    Current_Data[3] = (uint8_t)(value2 & 0xFF);
    Current_Data[4] = (uint8_t)(value3 >> 8);
    Current_Data[5] = (uint8_t)(value3 & 0xFF);
    Current_Data[6] = (uint8_t)(value4 >> 8);
    Current_Data[7] = (uint8_t)(value4 & 0xFF);

    CAN_Send(0x200, Current_Data);
}

void M3508_UpdateFeedback(M3508_t *motor, const uint8_t *data) {

    motor->angle = (uint16_t)((uint16_t)data[0]<<8 | data[1]);
    motor->speed = (int16_t)((uint16_t)data[2]<<8 | data[3]);
    motor->current = (int16_t)((uint16_t)data[4]<<8 | data[5]);
    motor->temperature = data[6];

}

void M3508_SetSpeed(M3508_t *motor, int16_t speed) {
    motor->targetSpeed = speed;
}
