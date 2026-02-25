#ifndef NEXT_GENERATION_SMART_WAKE_UP_DEIVCE_DISPLAY_HPP
#define NEXT_GENERATION_SMART_WAKE_UP_DEIVCE_DISPLAY_HPP

#include <Arduino.h>

namespace display {
void init();
void drawMainScreen(const String &time_text, const String &day_date_text,
                    const String &humidity, const String &pressure,
                    const String &temperature, const String &alarm_time);
}  // namespace display

#endif  // NEXT_GENERATION_SMART_WAKE_UP_DEIVCE_DISPLAY_HPP