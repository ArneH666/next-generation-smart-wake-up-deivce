#ifndef NEXT_GENERATION_SMART_WAKE_UP_DEIVCE_TIMEHANDLER_HPP
#define NEXT_GENERATION_SMART_WAKE_UP_DEIVCE_TIMEHANDLER_HPP
#include <Arduino.h>

namespace time_handler {
void setup();
String getDateTime(String time_format);
} // namespace time_handler

#endif // NEXT_GENERATION_SMART_WAKE_UP_DEIVCE_TIMEHANDLER_HPP