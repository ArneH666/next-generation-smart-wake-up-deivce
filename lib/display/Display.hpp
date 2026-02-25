#ifndef NEXT_GENERATION_SMART_WAKE_UP_DEIVCE_DISPLAY_HPP
#define NEXT_GENERATION_SMART_WAKE_UP_DEIVCE_DISPLAY_HPP

#include <Arduino.h>

namespace display {
void init();
void drawMainScreen(String time_text, String day_date_text, String humidity,
                    String pressure, String temperature, String alarm_time);
} // namespace display

#endif // NEXT_GENERATION_SMART_WAKE_UP_DEIVCE_DISPLAY_HPP