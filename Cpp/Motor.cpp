#include <iostream>

class Motor {

private:
    float speed;
     const int id;

public:

    Motor(int id)
        :speed(0),
         id(id)
    {

    }

    void setSpeed(float speed)
    {
        this->speed = speed;
    }

    float getSpeed() const
    {
        return speed;
    }

    int getID() const
    {
        return id;
    }

};


int main(void)
{
    Motor motor_1(1);
    motor_1.setSpeed(100);

    float speed = motor_1.getSpeed();
    int id = motor_1.getID();
    std::cout << speed << std::endl;
    std::cout << id << std::endl;

    return 0;
}