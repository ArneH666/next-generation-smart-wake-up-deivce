#include "Display.hpp"
#include "images/icons.hpp"

auto tft = TFT_eSPI();

namespace display {
void init() {
  tft.init();
  tft.setRotation(1);
  tft.setFreeFont(1);
}

void drawMainScreen(String time_text, String day_date_text, String humidity,
                    String pressure, String temperature, String alarm_time) {
  tft.fillScreen(0x0);

  // Time
  tft.setTextColor(0xFFFF);
  tft.setTextSize(12);

  tft.drawString(time_text, 66, 36);

  // Day & Date
  tft.setTextSize(5);
  tft.drawString(day_date_text, 63, 134);

  // Alarm Clock
  tft.drawBitmap(15, 208, image_Alarm_Clock_bits, 45, 48, 0xFFFF);

  // Daytime
  tft.drawBitmap(246, 209, image_Daytime_bits, 45, 48, 0xFFFF);

  // Nighttime
  tft.drawBitmap(245, 209, image_Nighttime_bits, 48, 48, 0xFFFF);

  // Temperature Celsius
  tft.drawBitmap(322, 207, image_Temperature_Celsius_bits, 48, 48, 0xFFFF);

  // Humidity
  tft.drawBitmap(307, 267, image_Humidity_bits, 33, 48, 0xFFFF);

  // Alarm Time
  tft.drawString(alarm_time, 70, 214);

  // Humidity Percent
  tft.drawString(humidity, 350, 273);

  // Temperature Text
  tft.drawString(temperature, 380, 214);

  // Pressure
  tft.drawString(pressure, 15, 273);

  // Line 1
  tft.drawLine(0, 261, 479, 261, 0xFFFF);

  // Line 2
  tft.drawLine(0, 202, 480, 202, 0xFFFF);

  // Line 3
  tft.drawLine(278, 319, 278, 262, 0xFFFF);

  // Line 4
  tft.drawLine(229, 261, 229, 203, 0xFFFF);

  // Line 5
  tft.drawLine(307, 259, 307, 202, 0xFFFF);
}
}  // namespace display