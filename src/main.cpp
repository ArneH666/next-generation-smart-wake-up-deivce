#include <Arduino.h>

#include <AmbientSensor.hpp>
#include <NetworkHandler.hpp>
#include <PinModeSetter.hpp>
#include <TimeHandler.hpp>
#include <UltrasonicSensor.hpp>
#include <VehicleController.hpp>

void setup() {
  Serial.begin(9600);
  Serial.println("Setup program start.");

  pinmode_setter::setPinModes();
  network_handler::setup();
  time_handler::setup();
  // ambient_sensor::setup();
  Serial.println("Current time: " + time_handler::getDateTime("H:i:s"));
}

void loop() {
  /*Serial.printf(
    "Temperature: %f\n"
    "Pressure: %fhPa\n"
    "Altitude: %fm\n"
    "Humidity: %f%%\n",
    ambient_sensor::readTemperature(),
    ambient_sensor::readPressure(),
    ambient_sensor::readAltitude(),
    ambient_sensor::readHumidity()
  );*/
  // Serial.println(ultrasonic_sensor::getDistance());
}