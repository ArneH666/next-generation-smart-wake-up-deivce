#ifndef NEXT_GENERATION_SMART_WAKE_UP_DEIVCE_AMBIENT_SENSOR_HPP
#define NEXT_GENERATION_SMART_WAKE_UP_DEIVCE_AMBIENT_SENSOR_HPP

namespace ambient_sensor {
void setup();
float readTemperature();
float readPressure();
float readAltitude();
float readHumidity();
} // namespace ambient_sensor

#endif // NEXT_GENERATION_SMART_WAKE_UP_DEIVCE_AMBIENT_SENSOR_HPP