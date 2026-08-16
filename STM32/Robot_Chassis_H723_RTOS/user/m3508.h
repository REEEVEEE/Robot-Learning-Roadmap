//
// Created by Tang on 2026/8/9.
//

#ifndef ROBOT_CHASSIS_H723_M3508_H
#define ROBOT_CHASSIS_H723_M3508_H

#include <stdint.h>

typedef struct {

    uint16_t id;

    int16_t targetCurrent;
    int16_t targetSpeed;

    uint16_t angle;
    int16_t speed;
    int16_t current;
    uint8_t temperature;

} M3508_t;

void M3508_Init(M3508_t *motor, uint16_t id);
void M3508_SetCurrent(M3508_t *motor, int16_t current);
void M3508_SendCurrent(const M3508_t *motor1, const M3508_t *motor2, const M3508_t *motor3, const M3508_t *motor4);
void M3508_UpdateFeedback(M3508_t *motor, const uint8_t *data);
void M3508_SetSpeed(M3508_t *motor, int16_t speed);

#endif //ROBOT_CHASSIS_H723_M3508_H