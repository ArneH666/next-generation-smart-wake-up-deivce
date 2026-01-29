#include "PinModeSetter.hpp"
#include "../../include/Pins.hpp"
#include <Arduino.h>

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
} // namespace pinmode_setter

void setInputPins() {
  constexpr int I = INPUT;
  pinMode(ULTRASONIC_SENSOR_ECHO_PIN, I);
}

void setOutputPins() {
  constexpr int O = OUTPUT;
  pinMode(ULTRASONIC_SENSOR_TRIGGER_PIN, O);
}

void setSpecialPins() {}

void setMisc() {
  ledcSetup(SERVO_STEERING_CHANEL, 50, 12);
  ledcAttachPin(SERVO_STEERING_PIN, SERVO_STEERING_CHANEL);
}