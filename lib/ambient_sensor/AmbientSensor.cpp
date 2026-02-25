#include "AmbientSensor.hpp"

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

#define SEA_LEVEL_PRESSURE 1013.25

Adafruit_BME280 bme;

namespace ambient_sensor {
void setup() {
  if (!bme.begin(0x76)) {
    Serial.println("ambient_sensor > Could not find sensor.");
  }
}
float readTemperature() { return bme.readTemperature(); }
float readPressure() { return bme.readPressure() / 100.0F; }
float readAltitude() { return bme.readAltitude(SEA_LEVEL_PRESSURE); }
float readHumidity() { return bme.readHumidity(); }
} // namespace ambient_sensor