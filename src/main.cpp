#include <Arduino.h>
#include <ezTime.h>

#include <AmbientSensor.hpp>
#include <AutonomousDriving.hpp>
#include <Display.hpp>
#include <NetworkHandler.hpp>
#include <PinModeSetter.hpp>
#include <TimeHandler.hpp>
#include <UltrasonicSensor.hpp>
#include <VehicleController.hpp>

auto Driver = autonomous_driving::Driver();
auto DisplayInstance = display::Display();

void setup() {
  Serial.begin(9600);
  Serial.println("Setup program start.");

  pinmode_setter::setPinModes();
  network_handler::setup();
  time_handler::setup();
  ambient_sensor::setup();
  Serial.println("Current time: " + time_handler::getDateTime("H:i:s"));
}

void loop() {
  // Serial.printf(
  //     "Temperature: %f\n"
  //     "Pressure: %fhPa\n"
  //     "Humidity: %f%%\n\n",
  //     ambient_sensor::readTemperature(), ambient_sensor::readPressure(),
  //     ambient_sensor::readHumidity());
  events();
  // Driver.drive();
  DisplayInstance.draw();
  DisplayInstance.handleTouch();
}