#ifndef NEXT_GENERATION_SMART_WAKE_UP_DEIVCE_TIMEHANDLER_HPP
#define NEXT_GENERATION_SMART_WAKE_UP_DEIVCE_TIMEHANDLER_HPP

#include <Arduino.h>
#include <ezTime.h>

namespace time_handler {
void setup();
String getDateTime(String time_format);
bool isDay();
bool setDateTime(const String &data);
time_t getCurrentEpoch();
time_t getEpochTime(const String& data);
}  // namespace time_handler

#endif  // NEXT_GENERATION_SMART_WAKE_UP_DEIVCE_TIMEHANDLER_HPP