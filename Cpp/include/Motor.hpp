//
// Created by Tang on 2026/8/8.
//

#pragma once

class Motor {

private:
    float currentSpeed;
    float targetSpeed;
    const int id;

public:

    //构造函数
    Motor(int id);

    //设定速度
    void setCurrentSpeed(float speed);

    //获取速度
    float getCurrentSpeed() const;

    //获取ID
    int getID() const;

    void setTargetSpeed(float speed);

    float getTargetSpeed() const;

};
