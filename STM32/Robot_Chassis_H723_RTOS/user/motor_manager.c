//
// Created by Tang on 2026/8/16.
//

#include "motor_manager.h"
#include "pid.h"

M3508_t motor_1;
M3508_t motor_2;
M3508_t motor_3;
M3508_t motor_4;

PID motor_pid_1;
PID motor_pid_2;
PID motor_pid_3;
PID motor_pid_4;

void MotorManager_Init(void) {
    M3508_Init(&motor_1, 0x201);
    M3508_Init(&motor_2, 0x202);
    M3508_Init(&motor_3, 0x203);
    M3508_Init(&motor_4, 0x204);
}
