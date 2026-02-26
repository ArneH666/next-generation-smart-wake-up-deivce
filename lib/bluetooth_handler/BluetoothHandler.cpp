#import "BluetoothHandler.hpp"

#include <BluetoothSerial.h>

BluetoothSerial BTSerial;

namespace bluetooth_handler {
void init() {

}
void getMessage() {
  String msg = "";

  while (BTSerial.available()) {
    char ch = BTSerial.
  }
}
}
