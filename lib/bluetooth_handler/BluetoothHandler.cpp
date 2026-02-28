#include "BluetoothHandler.hpp"

#include <BluetoothSerial.h>

#include <VehicleController.hpp>
#include <AutonomousDriving.hpp>

BluetoothSerial BTSerial;

String getMessage();

namespace bluetooth_handler {
void init() { BTSerial.begin("Driving Alarm Arne"); }

void handleBluetoothMessage(autonomous_driving::Driver Driver) {
  const String message = getMessage();
  if (message == "") {
    return;
  }

  if (message.startsWith("steering:")) {
    const int turning_angle =
        map(message.substring(9).toInt(), -100, 100, 45, 135);
    vehicle_controller::turnAngle(turning_angle);
  } else if (message.startsWith("direction")) {
    switch (message[10]) {
      case 'F':
        vehicle_controller::driveDirection(vehicle_controller::FORWARD);
      case 'R':
        vehicle_controller::driveDirection(vehicle_controller::REVERSE);
      case 'S':
        vehicle_controller::driveDirection(vehicle_controller::STOP);
      default:;
    }
  } else if (message == "autonomous") {
    Driver.activated = not Driver.activated;
    if (!Driver.activated) {
      vehicle_controller::driveDirection(vehicle_controller::STOP);
      vehicle_controller::turnAngle(90);
    }
  }
}
}  // namespace bluetooth_handler

String getMessage() {
  String message = "";

  while (BTSerial.available()) {
    const char character = BTSerial.read();
    message += character;
  }

  // Remove LF & CR
  while (message.indexOf(10) != -1) {
    message.remove(message.indexOf(10));
  }
  while (message.indexOf(13) != -1) {
    message.remove(message.indexOf(13));
  }

  return message;
}