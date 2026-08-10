//
// Created by Tang on 2026/8/10.
//

#ifndef ROBOT_CHASSIS_H723_PID_HPP
#define ROBOT_CHASSIS_H723_PID_HPP

#include <stdint.h>

typedef struct {
    float kP;
    float kI;
    float kD;

    float integral;
    float lastError;

    float integralLimit;
    float outputLimit;

    float output;

    float dt;

    int is_first_call;
}PID;

void PID_Init(PID *pid, float kP, float kI, float kD, float dt, float integralLimit, float outputLimit);

float PID_Calculate( PID *pid, int16_t target, int16_t feedback);

void PID_Reset(PID *pid);

#endif //ROBOT_CHASSIS_H723_PID_HPP