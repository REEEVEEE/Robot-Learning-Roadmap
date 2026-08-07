//
// Created by Tang on 2026/8/8.
//

#pragma once

class Motor {

private:
    float speed;
    const int id;

public:

    //构造函数
    Motor(int id);

    //设定速度
    void setSpeed(float speed);

    //获取速度
    float getSpeed() const;

    //获取ID
    int getID() const;

};
