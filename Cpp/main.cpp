//
// Created by Tang on 2026/8/8.
//

#include <iostream>
#include "Motor.hpp"

int main()
{
    Motor motor_1(1);
    motor_1.setSpeed(100);

    float speed = motor_1.getSpeed();
    int id = motor_1.getID();
    float targetSpeed = motor_1.getTargetSpeed();
    std::cout << speed << std::endl;
    std::cout << id << std::endl;
    std::cout << targetSpeed << std::endl;

    motor_1.setTargetSpeed(150);
    targetSpeed = motor_1.getTargetSpeed();
    std::cout << targetSpeed << std::endl;


    return 0;
}
