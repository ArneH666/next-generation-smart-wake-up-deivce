#include "Display.hpp"

#include <Arduino.h>

#include <AmbientSensor.hpp>
#include <ProjectTypes.hpp>
#include <TimeHandler.hpp>

#include "images/icons.hpp"

// Main Screen Buttons
TFT_eSPI_Button contrast_button, time_button, alarm_button, temperature_button,
    pressure_button;

// Time Setting Buttons
TFT_eSPI_Button confirm_button, cancel_button, num_0_button, num_1_button,
    num_2_button, num_3_button, num_4_button, num_5_button, num_6_button,
    num_7_button, num_8_button, num_9_button, backspace_button;

namespace display {
Display::Display() {
  this->TFT_Display.init();
  this->TFT_Display.setRotation(3);
  this->TFT_Display.setTextFont(0);
  this->TFT_Display.fillScreen(TFT_BLACK);

  uint16_t calData[5] = {202, 3718, 273, 3565, 1};
  this->TFT_Display.setTouch(calData);

  char button_text[1] = "";
  contrast_button.initButtonUL(&this->TFT_Display, 420, 0, 60, 52,
                               TFT_TRANSPARENT, TFT_TRANSPARENT,
                               TFT_TRANSPARENT, button_text, 1);
  time_button.initButtonUL(&this->TFT_Display, 63, 50, 355, 149,
                           TFT_TRANSPARENT, TFT_TRANSPARENT, TFT_TRANSPARENT,
                           button_text, 1);
  alarm_button.initButtonUL(&this->TFT_Display, 15, 208, 200, 48,
                            TFT_TRANSPARENT, TFT_TRANSPARENT, TFT_TRANSPARENT,
                            button_text, 1);
  temperature_button.initButtonUL(&this->TFT_Display, 322, 208, 143, 48,
                                  TFT_TRANSPARENT, TFT_TRANSPARENT,
                                  TFT_TRANSPARENT, button_text, 1);
  pressure_button.initButtonUL(&this->TFT_Display, 15, 273, 235, 35,
                               TFT_TRANSPARENT, TFT_TRANSPARENT,
                               TFT_TRANSPARENT, button_text, 1);

  confirm_button.initButtonUL(&this->TFT_Display, 404, 40, 56, 64,
                              TFT_TRANSPARENT, TFT_TRANSPARENT, TFT_TRANSPARENT,
                              button_text, 1);
  cancel_button.initButtonUL(&this->TFT_Display, 405, 201, 55, 80,
                             TFT_TRANSPARENT, TFT_TRANSPARENT, TFT_TRANSPARENT,
                             button_text, 1);
  num_0_button.initButtonUL(&this->TFT_Display, 25, 178, 35, 49,
                            TFT_TRANSPARENT, TFT_TRANSPARENT, TFT_TRANSPARENT,
                            button_text, 1);
  num_1_button.initButtonUL(&this->TFT_Display, 85, 178, 35, 49,
                            TFT_TRANSPARENT, TFT_TRANSPARENT, TFT_TRANSPARENT,
                            button_text, 1);
  num_2_button.initButtonUL(&this->TFT_Display, 145, 178, 35, 49,
                            TFT_TRANSPARENT, TFT_TRANSPARENT, TFT_TRANSPARENT,
                            button_text, 1);
  num_3_button.initButtonUL(&this->TFT_Display, 205, 178, 35, 49,
                            TFT_TRANSPARENT, TFT_TRANSPARENT, TFT_TRANSPARENT,
                            button_text, 1);
  num_4_button.initButtonUL(&this->TFT_Display, 266, 178, 35, 49,
                            TFT_TRANSPARENT, TFT_TRANSPARENT, TFT_TRANSPARENT,
                            button_text, 1);
  num_5_button.initButtonUL(&this->TFT_Display, 25, 251, 35, 49,
                            TFT_TRANSPARENT, TFT_TRANSPARENT, TFT_TRANSPARENT,
                            button_text, 1);
  num_6_button.initButtonUL(&this->TFT_Display, 85, 251, 35, 49,
                            TFT_TRANSPARENT, TFT_TRANSPARENT, TFT_TRANSPARENT,
                            button_text, 1);
  num_7_button.initButtonUL(&this->TFT_Display, 145, 251, 35, 49,
                            TFT_TRANSPARENT, TFT_TRANSPARENT, TFT_TRANSPARENT,
                            button_text, 1);
  num_8_button.initButtonUL(&this->TFT_Display, 205, 251, 35, 49,
                            TFT_TRANSPARENT, TFT_TRANSPARENT, TFT_TRANSPARENT,
                            button_text, 1);
  num_9_button.initButtonUL(&this->TFT_Display, 266, 251, 35, 49,
                            TFT_TRANSPARENT, TFT_TRANSPARENT, TFT_TRANSPARENT,
                            button_text, 1);
  backspace_button.initButtonUL(&this->TFT_Display, 325, 251, 35, 49,
                                TFT_TRANSPARENT, TFT_TRANSPARENT,
                                TFT_TRANSPARENT, button_text, 1);
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
    data.is_day = time_handler::isDay();
    this->drawMainScreen(data);
  } else if (this->current_screen == TIME_SETTING_SCREEN) {
    this->drawTimeSettingScreen();
  } else {
    this->drawSettingsScreen();
  }
}

void Display::drawMainScreen(const MainScreenData &main_screen_data) {
  const MainScreenData current_data = this->current_main_screen_data;

  if (this->screen_changed) {
    this->TFT_Display.fillScreen(TFT_BLACK);
  }

  // Time
  if (current_data.current_time != main_screen_data.current_time ||
      this->screen_changed) {
    this->TFT_Display.setTextColor(TFT_BLACK);
    this->TFT_Display.setTextSize(7);
    this->TFT_Display.drawString(current_data.current_time, 76, 50);

    this->TFT_Display.setTextColor(TFT_WHITE);
    this->TFT_Display.drawString(main_screen_data.current_time, 76, 50);

    this->TFT_Display.setTextSize(5);
  }

  // Day & Date
  if (current_data.current_date != main_screen_data.current_date ||
      this->screen_changed) {
    this->TFT_Display.setTextColor(TFT_BLACK);
    this->TFT_Display.drawString(current_data.current_date, 63, 134);

    this->TFT_Display.setTextColor(TFT_WHITE);
    this->TFT_Display.drawString(main_screen_data.current_date, 63, 134);
  }

  // Icons & Lines
  if (this->screen_changed) {
    // Alarm Clock
    this->TFT_Display.drawBitmap(15, 208, ALARM_CLOCK_IMAGE, 45, 48, TFT_WHITE);

    // Temperature Celsius
    this->TFT_Display.drawBitmap(322, 208, TEMPERATURE_CELSIUS_IMAGE, 48, 48,
                                 TFT_WHITE);

    // Humidity
    this->TFT_Display.drawBitmap(307, 267, HUMIDITY_IMAGE, 33, 48, TFT_WHITE);

    // Contrast Image
    this->TFT_Display.drawBitmap(450, 0, DISPLAY_CONTRAST_IMAGE, 30, 32,
                                 TFT_WHITE);

    // Line 1
    this->TFT_Display.drawLine(0, 261, 479, 261, TFT_WHITE);

    // Line 2
    this->TFT_Display.drawLine(0, 202, 480, 202, TFT_WHITE);

    // Line 3
    this->TFT_Display.drawLine(278, 319, 278, 262, TFT_WHITE);

    // Line 4
    this->TFT_Display.drawLine(229, 261, 229, 203, TFT_WHITE);

    // Line 5
    this->TFT_Display.drawLine(307, 259, 307, 202, TFT_WHITE);
  }

  // Daytime & Nighttime
  if (current_main_screen_data.is_day != main_screen_data.is_day ||
      this->screen_changed) {
    if (main_screen_data.is_day) {
      this->TFT_Display.drawBitmap(245, 209, NIGHTTIME_IMAGE, 48, 48,
                                   TFT_BLACK);
      this->TFT_Display.drawBitmap(246, 209, DAYTIME_IMAGE, 45, 45, TFT_WHITE);
    } else {
      this->TFT_Display.drawBitmap(246, 209, DAYTIME_IMAGE, 45, 45, TFT_BLACK);
      this->TFT_Display.drawBitmap(245, 209, NIGHTTIME_IMAGE, 48, 48,
                                   TFT_WHITE);
    }
  }

  // Alarm Time
  if (current_main_screen_data.alarm_time != main_screen_data.alarm_time ||
      this->screen_changed) {
    this->TFT_Display.setTextColor(TFT_BLACK);
    this->TFT_Display.drawString(current_main_screen_data.alarm_time, 70, 214);
    this->TFT_Display.setTextColor(TFT_WHITE);
    this->TFT_Display.drawString(main_screen_data.alarm_time, 70, 214);
  }

  // Humidity Percent
  if (current_main_screen_data.humidity != main_screen_data.humidity ||
      this->screen_changed) {
    this->TFT_Display.setTextColor(TFT_BLACK);
    this->TFT_Display.drawString(current_main_screen_data.humidity, 350, 273);
    this->TFT_Display.setTextColor(TFT_WHITE);
    this->TFT_Display.drawString(main_screen_data.humidity, 350, 273);
  }

  // Temperature Text
  if (current_main_screen_data.temperature != main_screen_data.temperature ||
      this->screen_changed) {
    this->TFT_Display.setTextColor(TFT_BLACK);
    this->TFT_Display.drawString(current_main_screen_data.temperature, 380,
                                 214);
    this->TFT_Display.setTextColor(TFT_WHITE);
    this->TFT_Display.drawString(main_screen_data.temperature, 380, 214);
  }

  // Pressure
  if (current_main_screen_data.pressure != main_screen_data.pressure ||
      this->screen_changed) {
    this->TFT_Display.setTextColor(TFT_BLACK);
    this->TFT_Display.drawString(current_main_screen_data.pressure, 15, 273);
    this->TFT_Display.setTextColor(TFT_WHITE);
    this->TFT_Display.drawString(main_screen_data.pressure, 15, 273);
  }

  if (this->screen_changed) {
    this->screen_changed = false;
  }

  this->current_main_screen_data = main_screen_data;
}

void Display::drawTimeSettingScreen() {
  const TimeSettingScreenData current_data =
      this->current_time_setting_screen_data;

  if (this->screen_changed) {
    this->TFT_Display.fillScreen(TFT_BLACK);
  }

  // Confirm
  this->TFT_Display.drawBitmap(404, 49, CONFIRM_IMAGE, 56, 64, TFT_WHITE);

  // Cancel
  this->TFT_Display.drawBitmap(405, 201, CANCEL_IMAGE, 55, 80, TFT_WHITE);

  // Icons & Lines & Numpad
  if (this->screen_changed) {
    // Backspace
    this->TFT_Display.setTextSize(7);
    this->TFT_Display.drawString("<", 325, 251);

    // Num9
    this->TFT_Display.drawString("9", 265, 251);

    // Num8
    this->TFT_Display.drawString("8", 205, 251);

    // Num7
    this->TFT_Display.drawString("7", 145, 251);

    // Num6
    this->TFT_Display.drawString("6", 85, 251);

    // Num5
    this->TFT_Display.drawString("5", 25, 251);

    // Num4
    this->TFT_Display.drawString("4", 265, 178);

    // Num3
    this->TFT_Display.drawString("3", 205, 178);

    // Num2
    this->TFT_Display.drawString("2", 145, 178);

    // Num1
    this->TFT_Display.drawString("1", 85, 178);

    // Num0
    this->TFT_Display.drawString("0", 25, 178);

    // Layer 16
    this->TFT_Display.drawLine(384, 0, 384, 320, TFT_WHITE);

    // Layer 17
    this->TFT_Display.drawLine(0, 139, 384, 139, TFT_WHITE);

    this->TFT_Display.setTextSize(5);
  }

  // Time
  this->TFT_Display.fillRect(74, 20, 235, 35, TFT_BLACK);
  this->TFT_Display.drawString(
      this->current_time_setting_screen_data.current_time, 74, 20);

  // Date
  this->TFT_Display.fillRect(44, 65, 286, 35, TFT_BLACK);
  this->TFT_Display.drawString(
      this->current_time_setting_screen_data.current_date, 44, 65);

  if (this->screen_changed) {
    this->screen_changed = false;
  }
}

void Display::drawSettingsScreen() {}

void Display::drawAlarmSettingScreen() {}

void Display::handleTouch() {
  uint16_t x = 0, y = 0;

  if (not this->TFT_Display.getTouch(&x, &y)) {
    return;
  }

  if (millis() - this->last_touch < 100) {
    return;
  }

  this->last_touch = millis();

  switch (this->current_screen) {
    case MAIN_SCREEN: {
      if (contrast_button.contains(x, y)) {
        this->inverted_colors = not this->inverted_colors;
      } else if (temperature_button.contains(x, y)) {
        this->temperature_metric_system = not this->temperature_metric_system;
      } else if (pressure_button.contains(x, y)) {
        this->pressure_metric_system = not this->pressure_metric_system;
      } else if (time_button.contains(x, y)) {
        this->current_screen = TIME_SETTING_SCREEN;
        this->screen_changed = true;
      } else if (alarm_button.contains(x, y)) {
        this->current_screen = ALARM_SETTING_SCREEN;
        this->screen_changed = true;
      }
      break;
    }
    case TIME_SETTING_SCREEN: {
      if (confirm_button.contains(x, y)) {
        Serial.println(this->current_time_setting_screen_data.current_input);
      } else if (cancel_button.contains(x, y)) {
        this->current_screen = MAIN_SCREEN;
        this->screen_changed = true;
      } else if (backspace_button.contains(x, y) &&
                 this->current_time_setting_screen_data.current_index > 0) {
        this->current_time_setting_screen_data.current_input.setCharAt(
            this->current_time_setting_screen_data.current_index, ' ');
        this->current_time_setting_screen_data.current_index--;
      } else if (num_0_button.contains(x, y) &&
                 this->current_time_setting_screen_data.current_index < 14) {
        this->current_time_setting_screen_data.current_input.setCharAt(
            this->current_time_setting_screen_data.current_index, '0');
        this->current_time_setting_screen_data.current_index++;
      } else if (num_1_button.contains(x, y) &&
                 this->current_time_setting_screen_data.current_index < 14) {
        this->current_time_setting_screen_data.current_input.setCharAt(
            this->current_time_setting_screen_data.current_index, '1');
        this->current_time_setting_screen_data.current_index++;
      } else if (num_2_button.contains(x, y) &&
                 this->current_time_setting_screen_data.current_index < 14) {
        this->current_time_setting_screen_data.current_input.setCharAt(
            this->current_time_setting_screen_data.current_index, '2');
        this->current_time_setting_screen_data.current_index++;
      } else if (num_3_button.contains(x, y) &&
                 this->current_time_setting_screen_data.current_index < 14) {
        this->current_time_setting_screen_data.current_input.setCharAt(
            this->current_time_setting_screen_data.current_index, '3');
        this->current_time_setting_screen_data.current_index++;
      } else if (num_4_button.contains(x, y) &&
                 this->current_time_setting_screen_data.current_index < 14) {
        this->current_time_setting_screen_data.current_input.setCharAt(
            this->current_time_setting_screen_data.current_index, '4');
        this->current_time_setting_screen_data.current_index++;
      } else if (num_5_button.contains(x, y) &&
                 this->current_time_setting_screen_data.current_index < 14) {
        this->current_time_setting_screen_data.current_input.setCharAt(
            this->current_time_setting_screen_data.current_index, '5');
        this->current_time_setting_screen_data.current_index++;
      } else if (num_6_button.contains(x, y) &&
                 this->current_time_setting_screen_data.current_index < 14) {
        this->current_time_setting_screen_data.current_input.setCharAt(
            this->current_time_setting_screen_data.current_index, '6');
        this->current_time_setting_screen_data.current_index++;
      } else if (num_7_button.contains(x, y) &&
                 this->current_time_setting_screen_data.current_index < 14) {
        this->current_time_setting_screen_data.current_input.setCharAt(
            this->current_time_setting_screen_data.current_index, '7');
        this->current_time_setting_screen_data.current_index++;
      } else if (num_8_button.contains(x, y) &&
                 this->current_time_setting_screen_data.current_index < 14) {
        this->current_time_setting_screen_data.current_input.setCharAt(
            this->current_time_setting_screen_data.current_index, '8');
        this->current_time_setting_screen_data.current_index++;
      } else if (num_9_button.contains(x, y) &&
                 this->current_time_setting_screen_data.current_index < 14) {
        this->current_time_setting_screen_data.current_input.setCharAt(
            this->current_time_setting_screen_data.current_index, '9');
        this->current_time_setting_screen_data.current_index++;
      }
      String curr = this->current_time_setting_screen_data.current_input;
      this->current_time_setting_screen_data.current_time =
          String(curr[0]) + curr[1] + ":" + curr[2] + curr[3] + ":" + curr[4] +
          curr[5];
      this->current_time_setting_screen_data.current_date =
          String(curr[6]) + curr[7] + "." + curr[8] + curr[9] + "." +
          curr.substring(10);
      break;
    }
    case ALARM_SETTING_SCREEN: {
      break;
    }
    case SETTINGS_SCREEN: {
      break;
    }
  }
}
}  // namespace display

// void drawMainScreen(const String &time_text, const String &day_date_text,
//                     const String &humidity, const String &pressure,
//                     const String &temperature, const String &alarm_time,
//                     const bool is_day) {
//   this->TFT_Display.pushSprite(0, 0, TFT_BLACK);
//   this->TFT_Display.fillSprite(TFT_BLACK);
//
//   // Time
//   this->TFT_Display.setTextColor(TFT_WHITE);
//   this->TFT_Display.setTextSize(7);
//
//   this->TFT_Display.drawString(time_text, 76, 50);
//
//   // Day & Date
//   this->TFT_Display.setTextSize(5);
//   this->TFT_Display.drawString(day_date_text, 63, 134);
//
//   // Alarm Clock
//   this->TFT_Display.drawBitmap(15, 208, ALARM_CLOCK_IMAGE, 45, 48,
//   TFT_WHITE);
//
//   if (is_day) {
//     // Daytime
//     this->TFT_Display.drawBitmap(246, 209, DAYTIME_IMAGE, 45, 45, TFT_WHITE);
//   } else {
//     // Nighttime
//     this->TFT_Display.drawBitmap(245, 209, NIGHTTIME_IMAGE, 48, 48,
//     TFT_WHITE);
//   }
//
//   // Temperature Celsius
//   this->TFT_Display.drawBitmap(322, 207, TEMPERATURE_CELSIUS_IMAGE, 48, 48,
//                               TFT_WHITE);
//
//   // Humidity
//   this->TFT_Display.drawBitmap(307, 267, HUMIDITY_IMAGE, 33, 48, TFT_WHITE);
//
//   // Alarm Time
//   this->TFT_Display.drawString(alarm_time, 70, 214);
//
//   // Humidity Percent
//   this->TFT_Display.drawString(humidity, 350, 273);
//
//   // Temperature Text
//   this->TFT_Display.drawString(temperature, 380, 214);
//
//   // Pressure
//   this->TFT_Display.drawString(pressure, 15, 273);
//
//   // Line 1
//   this->TFT_Display.drawLine(0, 261, 479, 261, TFT_WHITE);
//
//   // Line 2
//   this->TFT_Display.drawLine(0, 202, 480, 202, TFT_WHITE);
//
//   // Line 3
//   this->TFT_Display.drawLine(278, 319, 278, 262, TFT_WHITE);
//
//   // Line 4
//   this->TFT_Display.drawLine(229, 261, 229, 203, TFT_WHITE);
//
//   // Line 5
//   this->TFT_Display.drawLine(307, 259, 307, 202, TFT_WHITE);
//
//   this->TFT_Display.pushSprite(0, 0);
// }
//
// void drawTimeScreen() {
//   this->TFT_Display.pushSprite(0, 0, TFT_BLACK);
//   this->TFT_Display.fillSprite(TFT_BLACK);
//   this->TFT_Display.setTextSize(7);
//   this->TFT_Display.drawString("00:00", 103, 136);
//   // digit 1 hour down
//   this->TFT_Display.drawBitmap(30, 232, BUTTON_DOWN_IMAGE, 48, 42,
//   TFT_WHITE);
//   // digit 1 hour up
//   this->TFT_Display.drawBitmap(30, 46, BUTTON_UP_IMAGE, 48, 42, TFT_WHITE);
//   // digit 2 hour up
//   this->TFT_Display.drawBitmap(102, 46, BUTTON_UP_IMAGE, 48, 42, TFT_WHITE);
//   // digit 1 minute up
//   this->TFT_Display.drawBitmap(246, 46, BUTTON_UP_IMAGE, 48, 42, TFT_WHITE);
//   // digit 2 minute up
//   this->TFT_Display.drawBitmap(318, 47, BUTTON_UP_IMAGE, 48, 42, TFT_WHITE);
//   // digit 2 minute down
//   this->TFT_Display.drawBitmap(318, 232, BUTTON_DOWN_IMAGE, 48, 42,
//   TFT_WHITE);
//   // digit 1 minute down
//   this->TFT_Display.drawBitmap(246, 232, BUTTON_DOWN_IMAGE, 48, 42,
//   TFT_WHITE);
//   // digit 2 hour down
//   this->TFT_Display.drawBitmap(102, 232, BUTTON_DOWN_IMAGE, 48, 42,
//   TFT_WHITE);
//   // confirm
//   this->TFT_Display.drawBitmap(399, 74, CONFIRM_IMAGE, 56, 64, TFT_WHITE);
//   // cancel
//   this->TFT_Display.drawBitmap(399, 168, CANCEL_IMAGE, 55, 80, TFT_WHITE);
//
//   this->TFT_Display.pushSprite(0, 0);
// }