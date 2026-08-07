#include "Motor.hpp"

Motor::Motor(int id)
    : currentSpeed(0),
      targetSpeed(0),
      id(id)
{

}

void Motor::setCurrentSpeed(float speed)
{
    this->currentSpeed = speed;
}

float Motor::getCurrentSpeed() const
{
    return currentSpeed;
}

int Motor::getID() const
{
    return id;
}

void Motor::setTargetSpeed(float speed) {
    this->targetSpeed = speed;
}

float Motor::getTargetSpeed() const {
    return targetSpeed;
}
