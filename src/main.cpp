#include <Arduino.h>

#include <AmbientSensor.hpp>
#include <AutonomousDriving.hpp>
#include <Display.hpp>
#include <NetworkHandler.hpp>
#include <PinModeSetter.hpp>
#include <TimeHandler.hpp>
#include <UltrasonicSensor.hpp>
#include <VehicleController.hpp>

auto Driver = autonomous_driving::Driver();

void setup() {
  Serial.begin(9600);
  Serial.println("Setup program start.");

  pinmode_setter::setPinModes();
  // network_handler::setup();
  // time_handler::setup();
  // ambient_sensor::setup();
  // Serial.println("Current time: " + time_handler::getDateTime("H:i:s"));
  display::init();
}

void loop() {
  // Serial.printf(
  //   "Temperature: %f\n"
  //   "Pressure: %fhPa\n"
  //   "Humidity: %f%%\n\n",
  //   ambient_sensor::readTemperature(),
  //   ambient_sensor::readPressure(),
  //   ambient_sensor::readHumidity()
  // );
  // Driver.drive();
  display::drawMainScreen("12:34", "Tue, 25. Feb", "56%", "1013hPa", "22",
                          "23:45");
  delay(100);
}