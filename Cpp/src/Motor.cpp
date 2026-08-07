#include "Motor.hpp"

Motor::Motor(const int id)
    : speed(0),
      id(id)
{

}

void Motor::setSpeed(float speed)
{
    this->speed = speed;
}

float Motor::getSpeed() const
{
    return speed;
}

int Motor::getID() const
{
    return id;
}
