#ifndef NEXT_GENERATION_SMART_WAKE_UP_DEIVCE_BLUETOOTHHANDLER_HPP
#define NEXT_GENERATION_SMART_WAKE_UP_DEIVCE_BLUETOOTHHANDLER_HPP

#include <AutonomousDriving.hpp>

namespace bluetooth_handler {
void init();
void handleBluetoothMessage(autonomous_driving::Driver);
}  // namespace bluetooth_handler

#endif  // NEXT_GENERATION_SMART_WAKE_UP_DEIVCE_BLUETOOTHHANDLER_HPP
