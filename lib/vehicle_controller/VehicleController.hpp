#ifndef NEXT_GENERATION_SMART_WAKE_UP_DEIVCE_VEHICLECONTROLLER_HPP
#define NEXT_GENERATION_SMART_WAKE_UP_DEIVCE_VEHICLECONTROLLER_HPP

namespace vehicle_controller {
enum MotorDirection {
  FORWARD,
  REVERSE,
  STOP,
};

void driveDirection(MotorDirection direction);
void turnAngle(int turn_angle);
} // namespace vehicle_controller

#endif // NEXT_GENERATION_SMART_WAKE_UP_DEIVCE_VEHICLECONTROLLER_HPP