#include "Display.hpp"

#include <AmbientSensor.hpp>
#include <ProjectTypes.hpp>
#include <TimeHandler.hpp>

#include "images/icons.hpp"

// TODO: Use Sprites

namespace display {
Display::Display() : TFT_Sprite(&this->TFT_Display) {
  this->TFT_Display.init();
  this->TFT_Display.setRotation(3);
  this->TFT_Display.setTextFont(0);
  this->TFT_Display.fillScreen(0x0);

  this->TFT_Sprite.setColorDepth(1);
  this->TFT_Sprite.createSprite(480, 320);
  this->TFT_Sprite.setTextFont(0);

  uint16_t calData[5] = {202, 3718, 273, 3565, 1};
  this->TFT_Display.setTouch(calData);
}
void Display::draw() {
  this->TFT_Display.invertDisplay(this->inverted_colors);
  if (this->current_screen == MAIN_SCREEN) {
    MainScreenData data;
    data.current_time = time_handler::getDateTime("H:i:s");
    data.current_date = time_handler::getDateTime("D, d. M");
    data.humidity =
        String(static_cast<int>(round(ambient_sensor::readHumidity()))) + "%";
    data.pressure =
        String(static_cast<int>(round(ambient_sensor::readPressure()))) +
        " hPa";
    data.temperature =
        String(static_cast<int>(round(ambient_sensor::readTemperature())));
    data.alarm_time = "XX:XX";
    data.is_day = true;
    this->drawMainScreen(data);
  } else if (this->current_screen == TIME_SCREEN) {
    this->drawTimeScreen();
  } else {
    this->drawSettingsScreen();
  }
}

void Display::drawMainScreen(const MainScreenData &main_screen_data) {
  this->TFT_Sprite.pushSprite(0, 0, TFT_BLACK);
  this->TFT_Sprite.fillSprite(TFT_BLACK);

  // Time
  this->TFT_Sprite.setTextColor(0xFFFF);
  this->TFT_Sprite.setTextSize(7);

  this->TFT_Sprite.drawString(main_screen_data.current_time, 76, 50);

  // Day & Date
  this->TFT_Sprite.setTextSize(5);
  this->TFT_Sprite.drawString(main_screen_data.current_date, 63, 134);

  // Alarm Clock
  this->TFT_Sprite.drawBitmap(15, 208, ALARM_CLOCK_IMAGE, 45, 48, 0xFFFF);

  if (main_screen_data.is_day) {
    // Daytime
    this->TFT_Sprite.drawBitmap(246, 209, DAYTIME_IMAGE, 45, 45, 0xFFFF);
  } else {
    // Nighttime
    this->TFT_Sprite.drawBitmap(245, 209, NIGHTTIME_IMAGE, 48, 48, 0xFFFF);
  }

  // Temperature Celsius
  this->TFT_Sprite.drawBitmap(322, 207, TEMPERATURE_CELSIUS_IMAGE, 48, 48,
                              0xFFFF);

  // Humidity
  this->TFT_Sprite.drawBitmap(307, 267, HUMIDITY_IMAGE, 33, 48, 0xFFFF);

  // Alarm Time
  this->TFT_Sprite.drawString(main_screen_data.alarm_time, 70, 214);

  // Humidity Percent
  this->TFT_Sprite.drawString(main_screen_data.humidity, 350, 273);

  // Temperature Text
  this->TFT_Sprite.drawString(main_screen_data.temperature, 380, 214);

  // Pressure
  this->TFT_Sprite.drawString(main_screen_data.pressure, 15, 273);

  // Line 1
  this->TFT_Sprite.drawLine(0, 261, 479, 261, 0xFFFF);

  // Line 2
  this->TFT_Sprite.drawLine(0, 202, 480, 202, 0xFFFF);

  // Line 3
  this->TFT_Sprite.drawLine(278, 319, 278, 262, 0xFFFF);

  // Line 4
  this->TFT_Sprite.drawLine(229, 261, 229, 203, 0xFFFF);

  // Line 5
  this->TFT_Sprite.drawLine(307, 259, 307, 202, 0xFFFF);

  this->TFT_Sprite.drawBitmap(450, 0, DISPLAY_CONTRAST_IMAGE, 30, 32, 0xFFFF);

  this->TFT_Sprite.pushSprite(0, 0);
}
void Display::drawTimeScreen() { this->TFT_Display.fillScreen(0x0); }
void Display::drawSettingsScreen() {}
void Display::handleTouch() {
  uint16_t x = 0, y = 0;

  if (not this->TFT_Display.getTouch(&x, &y)) {
    return;
  }

  Serial.printf("x: %u; y: %u\n", x, y);

  switch (this->current_screen) {
    case MAIN_SCREEN:
      if ((76 <= x && x <= 405 && 50 <= y && y <= 99) ||
          (15 <= x && x <= 215 && 208 <= y && y <= 256)) {
        // Clock & Alarm
        this->current_screen = TIME_SCREEN;
      } else if ((322 <= x && x <= 465 && 207 <= y && y <= 255) ||
                 (15 <= x && x <= 250 && 273 <= y && y <= 308)) {
        // Temp & Pressure
        this->unit_system_metric = not this->unit_system_metric;
      } else if ((450 <= x && x <= 480 && y <= 32)) {
        // Contrast
        this->inverted_colors = not this->inverted_colors;
      }
    case TIME_SCREEN:
      return;
    case SETTINGS_SCREEN:
      return;
  }
}
}  // namespace display

// void drawMainScreen(const String &time_text, const String &day_date_text,
//                     const String &humidity, const String &pressure,
//                     const String &temperature, const String &alarm_time,
//                     const bool is_day) {
//   this->TFT_Sprite.pushSprite(0, 0, TFT_BLACK);
//   this->TFT_Sprite.fillSprite(TFT_BLACK);
//
//   // Time
//   this->TFT_Sprite.setTextColor(0xFFFF);
//   this->TFT_Sprite.setTextSize(7);
//
//   this->TFT_Sprite.drawString(time_text, 76, 50);
//
//   // Day & Date
//   this->TFT_Sprite.setTextSize(5);
//   this->TFT_Sprite.drawString(day_date_text, 63, 134);
//
//   // Alarm Clock
//   this->TFT_Sprite.drawBitmap(15, 208, ALARM_CLOCK_IMAGE, 45, 48, 0xFFFF);
//
//   if (is_day) {
//     // Daytime
//     this->TFT_Sprite.drawBitmap(246, 209, DAYTIME_IMAGE, 45, 45, 0xFFFF);
//   } else {
//     // Nighttime
//     this->TFT_Sprite.drawBitmap(245, 209, NIGHTTIME_IMAGE, 48, 48, 0xFFFF);
//   }
//
//   // Temperature Celsius
//   this->TFT_Sprite.drawBitmap(322, 207, TEMPERATURE_CELSIUS_IMAGE, 48, 48,
//                               0xFFFF);
//
//   // Humidity
//   this->TFT_Sprite.drawBitmap(307, 267, HUMIDITY_IMAGE, 33, 48, 0xFFFF);
//
//   // Alarm Time
//   this->TFT_Sprite.drawString(alarm_time, 70, 214);
//
//   // Humidity Percent
//   this->TFT_Sprite.drawString(humidity, 350, 273);
//
//   // Temperature Text
//   this->TFT_Sprite.drawString(temperature, 380, 214);
//
//   // Pressure
//   this->TFT_Sprite.drawString(pressure, 15, 273);
//
//   // Line 1
//   this->TFT_Sprite.drawLine(0, 261, 479, 261, 0xFFFF);
//
//   // Line 2
//   this->TFT_Sprite.drawLine(0, 202, 480, 202, 0xFFFF);
//
//   // Line 3
//   this->TFT_Sprite.drawLine(278, 319, 278, 262, 0xFFFF);
//
//   // Line 4
//   this->TFT_Sprite.drawLine(229, 261, 229, 203, 0xFFFF);
//
//   // Line 5
//   this->TFT_Sprite.drawLine(307, 259, 307, 202, 0xFFFF);
//
//   this->TFT_Sprite.pushSprite(0, 0);
// }
//
// void drawTimeScreen() {
//   this->TFT_Sprite.pushSprite(0, 0, TFT_BLACK);
//   this->TFT_Sprite.fillSprite(TFT_BLACK);
//   this->TFT_Sprite.setTextSize(7);
//   this->TFT_Sprite.drawString("00:00", 103, 136);
//   // digit 1 hour down
//   this->TFT_Sprite.drawBitmap(30, 232, BUTTON_DOWN_IMAGE, 48, 42, 0xFFFF);
//   // digit 1 hour up
//   this->TFT_Sprite.drawBitmap(30, 46, BUTTON_UP_IMAGE, 48, 42, 0xFFFF);
//   // digit 2 hour up
//   this->TFT_Sprite.drawBitmap(102, 46, BUTTON_UP_IMAGE, 48, 42, 0xFFFF);
//   // digit 1 minute up
//   this->TFT_Sprite.drawBitmap(246, 46, BUTTON_UP_IMAGE, 48, 42, 0xFFFF);
//   // digit 2 minute up
//   this->TFT_Sprite.drawBitmap(318, 47, BUTTON_UP_IMAGE, 48, 42, 0xFFFF);
//   // digit 2 minute down
//   this->TFT_Sprite.drawBitmap(318, 232, BUTTON_DOWN_IMAGE, 48, 42, 0xFFFF);
//   // digit 1 minute down
//   this->TFT_Sprite.drawBitmap(246, 232, BUTTON_DOWN_IMAGE, 48, 42, 0xFFFF);
//   // digit 2 hour down
//   this->TFT_Sprite.drawBitmap(102, 232, BUTTON_DOWN_IMAGE, 48, 42, 0xFFFF);
//   // confirm
//   this->TFT_Sprite.drawBitmap(399, 74, CONFIRM_IMAGE, 56, 64, 0xFFFF);
//   // cancel
//   this->TFT_Sprite.drawBitmap(399, 168, CANCEL_IMAGE, 55, 80, 0xFFFF);
//
//   this->TFT_Sprite.pushSprite(0, 0);
// }