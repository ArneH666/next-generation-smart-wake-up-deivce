#include "VehicleController.hpp"

#include "../../include/Pins.hpp"

#include <Arduino.h>

void setMotorDirection(int motor_forward_pin, int motor_reverse_pin);

namespace vehicle_controller {
void driveDirection(const MotorDirection direction) {
  switch (direction) {
  case FORWARD:
    setMotorDirection(HIGH, LOW);
    break;
  case REVERSE:
    setMotorDirection(LOW, HIGH);
    break;
  case STOP:
    setMotorDirection(LOW, LOW);
    break;
  }
}

void turnAngle(const int turn_angle) {
  const int duty_cycle = 102.4 + turn_angle * 2.161 + 0.5;
  ledcWrite(SERVO_STEERING_CHANEL, duty_cycle);
}

} // namespace vehicle_controller

void setMotorDirection(const int motor_forward_pin,
                       const int motor_reverse_pin) {
  digitalWrite(MOTOR_FORWARD_PIN, motor_forward_pin);
  digitalWrite(MOTOR_REVERSE_PIN, motor_reverse_pin);
}
