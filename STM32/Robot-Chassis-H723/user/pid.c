//
// Created by Tang on 2026/8/10.
//

#include "pid.h"

#include "main.h"

void PID_Init(PID *pid, float kP, float kI, float kD, float dt, float integralLimit, float outputLimit) {
    pid->kP = kP;
    pid->kI = kI;
    pid->kD = kD;
    pid->integral = 0;
    pid->lastError = 0;
    pid->output = 0;

    if (dt <= 0) {
        Error_Handler();
    }

    pid->dt = dt;
    pid->is_first_call = 1;

    pid->integralLimit = integralLimit;
    pid->outputLimit = outputLimit;
}

float PID_Calculate( PID *pid, int16_t target, int16_t feedback) {

    float error = (float) (target-feedback);

    float pOutput = pid->kP * error;

    pid->integral += error * pid->dt;

    if (pid->integral > pid->integralLimit) pid->integral = pid->integralLimit;
    if (pid->integral < -pid->integralLimit) pid->integral = -pid->integralLimit;

    float iOutput = pid->kI * pid->integral;

    float dOutput = 0;
    if (!pid->is_first_call) {
        dOutput = pid->kD * (error - pid->lastError) / pid->dt;
    }

    pid->output = pOutput + iOutput + dOutput;

    if (pid->output > pid->outputLimit) pid->output = pid->outputLimit;
    if (pid->output < -pid->outputLimit) pid->output = -pid->outputLimit;

    pid->lastError = error;

    if (pid->is_first_call) {
        pid->is_first_call = 0;
    }

    return pid->output;
}

void PID_Reset(PID *pid) {
    pid->integral = 0;
    pid->output = 0;
    pid->lastError = 0;
    pid->is_first_call = 1;
}
