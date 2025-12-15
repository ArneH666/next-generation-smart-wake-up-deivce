#include <Arduino.h>
#include "ultrasonic_sensor.hpp"
#include "Pins.hpp"

void triggerSensor();

namespace lib {
    float getDistance() {
        triggerSensor();

        const unsigned long signal_duration = pulseIn(ULTRASONIC_SENSOR_ECHO_PIN, HIGH);

        return (signal_duration * 0.0344) / 2;
    }
} // lib

void triggerSensor() {
    digitalWrite(ULTRASONIC_SENSOR_TRIGGER_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(ULTRASONIC_SENSOR_TRIGGER_PIN, LOW);
}