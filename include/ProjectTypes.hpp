#ifndef NEXT_GENERATION_SMART_WAKE_UP_DEIVCE_PROJECTTYPES_HPP
#define NEXT_GENERATION_SMART_WAKE_UP_DEIVCE_PROJECTTYPES_HPP

#include <Arduino.h>

struct MainScreenData {
  String current_time = "00:00:00";
  String current_date = "Thu, 01. Jan";
  String alarm_time = "XX:XX";
  String temperature = "0";
  String pressure = "0 hPa";
  String humidity = "0%";
  bool is_day = true;
};

struct TimeSettingScreenData {
  String current_time = "  :  :  ";
  String current_date = "  .  .    ";
  String current_input = "              ";
  int current_index = 0;
};

#endif  // NEXT_GENERATION_SMART_WAKE_UP_DEIVCE_PROJECTTYPES_HPP
