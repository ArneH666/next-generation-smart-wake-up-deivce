#include "PinModeSetter.hpp"

#include <Arduino.h>

#include <Pins.hpp>

// TODO: Set the pin modes for all pins.

void setInputPins();

void setOutputPins();

void setSpecialPins();

void setMisc();

namespace pinmode_setter {
void setPinModes() {
  setInputPins();
  setOutputPins();
  setSpecialPins();
  setMisc();
}
}  // namespace pinmode_setter

void setInputPins() {
  constexpr int I = INPUT;
  pinMode(ULTRASONIC_SENSOR_ECHO_PIN, I);
}

void setOutputPins() {
  constexpr int O = OUTPUT;
  pinMode(ULTRASONIC_SENSOR_TRIGGER_PIN, O);
  pinMode(MOTOR_FORWARD_PIN, O);
  pinMode(MOTOR_REVERSE_PIN, O);
}

void setSpecialPins() {}

void setMisc() {
  ledcSetup(SERVO_STEERING_CHANEL, 50, 12);
  ledcAttachPin(SERVO_STEERING_PIN, SERVO_STEERING_CHANEL);
}