#include "ultrasonic_sensor.hpp"
#include "../../include/Pins.hpp"
#include <Arduino.h>

void triggerSensor();

namespace ultrasonic_sensor {
float getDistance() {
  triggerSensor();

  const unsigned long signal_duration =
      pulseIn(ULTRASONIC_SENSOR_ECHO_PIN, HIGH);

  return (signal_duration * 0.0344) / 2;
}
} // namespace ultrasonic_sensor

void triggerSensor() {
  digitalWrite(ULTRASONIC_SENSOR_TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(ULTRASONIC_SENSOR_TRIGGER_PIN, LOW);
}