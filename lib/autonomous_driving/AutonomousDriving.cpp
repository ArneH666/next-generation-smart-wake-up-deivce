#include "AutonomousDriving.hpp"

#include <Arduino.h>

#include <UltrasonicSensor.hpp>
#include <VehicleController.hpp>

namespace autonomous_driving {
Driver::Driver() {}

void Driver::drive() {
  const int ultrasonic_sensor_distance = ultrasonic_sensor::getDistance();

  if (this->last_step_millis != 0 || millis() - this->last_step_millis < 500) {
    vehicle_controller::driveDirection(vehicle_controller::REVERSE);
  } else {
    this->last_step_millis = 0;
  }

  if (ultrasonic_sensor_distance > 50) {
    vehicle_controller::turnAngle(90);
    vehicle_controller::driveDirection(vehicle_controller::FORWARD);
    Serial.println("Driving straight");
  } else if (ultrasonic_sensor_distance > 20) {
    vehicle_controller::turnAngle(115);
    vehicle_controller::driveDirection(vehicle_controller::FORWARD);
    Serial.println("Driving right");
  } else {
    vehicle_controller::turnAngle(90);
    vehicle_controller::driveDirection(vehicle_controller::REVERSE);
    this->last_step_millis = millis();
    Serial.println("Driving backwards");
  }
}
}  // namespace autonomous_driving