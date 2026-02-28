#include <Arduino.h>
#include <ezTime.h>

#include <AmbientSensor.hpp>
#include <AutonomousDriving.hpp>
#include <Display.hpp>
#include <NetworkHandler.hpp>
#include <PinModeSetter.hpp>
#include <TimeHandler.hpp>
#include <BluetoothHandler.hpp>

auto Driver = autonomous_driving::Driver();
auto DisplayInstance = display::Display();

void setup() {
  Serial.begin(9600);
  Serial.println("Setup program start.");

  pinmode_setter::setPinModes();
  network_handler::setup();
  bluetooth_handler::init();
  time_handler::setup();
  ambient_sensor::setup();
}

void loop() {
  DisplayInstance.draw();
  DisplayInstance.handleTouch();
  bluetooth_handler::handleBluetoothMessage(Driver);
  Driver.drive();
  events();
  // Driver.drive();
}