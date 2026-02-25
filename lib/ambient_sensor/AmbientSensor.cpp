#include "AmbientSensor.hpp"

#include <Adafruit_BME280.h>

Adafruit_BME280 bme;

namespace ambient_sensor {
void setup() {
  if (!bme.begin(0x76)) {
    Serial.println("ambient_sensor > Could not find sensor.");
  }
}
float readTemperature() { return bme.readTemperature(); }
float readPressure() { return bme.readPressure() / 100.0F; }
float readHumidity() { return bme.readHumidity(); }
}  // namespace ambient_sensor