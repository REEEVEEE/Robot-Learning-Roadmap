//
// Created by Tang on 2026/8/16.
//

#ifndef ROBOT_CHASSIS_H723_RTOS_MOTOR_MANAGER_H
#define ROBOT_CHASSIS_H723_RTOS_MOTOR_MANAGER_H

#include "m3508.h"
#include "pid.h"

extern M3508_t motor_1;
extern M3508_t motor_2;
extern M3508_t motor_3;
extern M3508_t motor_4;

extern PID motor_pid_1;
extern PID motor_pid_2;
extern PID motor_pid_3;
extern PID motor_pid_4;

void MotorManager_Init(void);

#endif //ROBOT_CHASSIS_H723_RTOS_MOTOR_MANAGER_H