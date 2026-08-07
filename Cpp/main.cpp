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
    std::cout << speed << std::endl;
    std::cout << id << std::endl;

    return 0;
}
