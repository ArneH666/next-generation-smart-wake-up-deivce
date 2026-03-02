#include "UltrasonicSensor.hpp"

#include <Arduino.h>

#include <Pins.hpp>

void triggerSensor();

unsigned long last_measurement = 0;

namespace ultrasonic_sensor {
double getDistance() {
  triggerSensor();

  const unsigned long signal_duration =
      pulseIn(ULTRASONIC_SENSOR_ECHO_PIN, HIGH);

  return (signal_duration * 0.0344) / 2;
}

bool detectHand() {
  if (millis() - last_measurement < 60) {
    return false;
  }

  last_measurement = millis();

  const double distance = getDistance();

  if (distance <= 10) {
    return true;
  }
  return false;
}
}  // namespace ultrasonic_sensor

void triggerSensor() {
  digitalWrite(ULTRASONIC_SENSOR_TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(ULTRASONIC_SENSOR_TRIGGER_PIN, LOW);
}