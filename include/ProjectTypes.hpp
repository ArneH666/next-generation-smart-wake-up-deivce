#ifndef NEXT_GENERATION_SMART_WAKE_UP_DEIVCE_PROJECTTYPES_HPP
#define NEXT_GENERATION_SMART_WAKE_UP_DEIVCE_PROJECTTYPES_HPP

#include <Arduino.h>

struct MainScreenData {
  String current_time = "00:00:00";
  String current_date = "Thu, 01. Jan";
  String alarm_time = "XX:XX";
  String temperature = "15";
  String pressure = "1013 hPa";
  String humidity = "36%";
  bool is_day = true;
};

#endif  // NEXT_GENERATION_SMART_WAKE_UP_DEIVCE_PROJECTTYPES_HPP
