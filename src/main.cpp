#include <Arduino.h>
#include <ezTime.h>

#include <AlarmHandler.hpp>
#include <AmbientSensor.hpp>
#include <AutonomousDriving.hpp>
#include <BluetoothHandler.hpp>
#include <Display.hpp>
#include <NetworkHandler.hpp>
#include <PinModeSetter.hpp>
#include <TimeHandler.hpp>
#include <UltrasonicSensor.hpp>

auto Driver = autonomous_driving::Driver();
auto AlarmHandler = alarm_handler::AlarmHandler();
auto DisplayInstance = display::Display(AlarmHandler);

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
  events();
  if (AlarmHandler.checkForAlarm() && ultrasonic_sensor::detectHand()) {
      AlarmHandler.turnOffAlarm();
  }
  DisplayInstance.draw();
  DisplayInstance.handleTouch();
  bluetooth_handler::handleBluetoothMessage(Driver);
  Driver.drive();
  // Driver.drive();
}