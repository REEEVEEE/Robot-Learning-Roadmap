#include <iostream>

class Motor {

private:
    float speed;

public:

    void set_speed(float speed)
    {
        this->speed = speed;
    }

    float get_speed()
    {
        return speed;
    }

};


int main(void)
{
    Motor motor_1;
    motor_1.set_speed(100);

    float speed = motor_1.get_speed();
    std::cout << speed << std::endl;

    return 0;
}