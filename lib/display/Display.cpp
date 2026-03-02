#include "Display.hpp"

#include <Arduino.h>

#include <AmbientSensor.hpp>
#include <TimeHandler.hpp>
#include <cmath>

#include "images/icons.hpp"

ExtractedTime extractAlarmData(time_t current_time_t, time_t previous_time_t);

// Main Screen Buttons
TFT_eSPI_Button contrast_button, time_button, alarm_button, temperature_button,
    pressure_button;

// Time Setting Buttons
TFT_eSPI_Button time_confirm_button, time_cancel_button, time_num_0_button,
    time_num_1_button, time_num_2_button, time_num_3_button, time_num_4_button,
    time_num_5_button, time_num_6_button, time_num_7_button, time_num_8_button,
    time_num_9_button, time_backspace_button;

// Alarm Setting Buttons
TFT_eSPI_Button alarm_add_button, alarm_up_button, alarm_down_button,
    alarm_cancel_button, alarm_delete_1_button, alarm_delete_2_button,
    alarm_delete_3_button;

namespace display {
Display::Display(const alarm_handler::AlarmHandler &handler) {
  this->alarm_handler = handler;
  this->TFT_Display.init();
  this->TFT_Display.setRotation(3);
  this->TFT_Display.setTextFont(0);
  this->TFT_Display.fillScreen(TFT_BLACK);
  this->time_setting_responsibility = UNDEFINED;

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

  time_confirm_button.initButtonUL(&this->TFT_Display, 404, 40, 56, 64,
                                   TFT_TRANSPARENT, TFT_TRANSPARENT,
                                   TFT_TRANSPARENT, button_text, 1);
  time_cancel_button.initButtonUL(&this->TFT_Display, 405, 201, 55, 80,
                                  TFT_TRANSPARENT, TFT_TRANSPARENT,
                                  TFT_TRANSPARENT, button_text, 1);
  time_num_0_button.initButtonUL(&this->TFT_Display, 25, 178, 35, 49,
                                 TFT_TRANSPARENT, TFT_TRANSPARENT,
                                 TFT_TRANSPARENT, button_text, 1);
  time_num_1_button.initButtonUL(&this->TFT_Display, 85, 178, 35, 49,
                                 TFT_TRANSPARENT, TFT_TRANSPARENT,
                                 TFT_TRANSPARENT, button_text, 1);
  time_num_2_button.initButtonUL(&this->TFT_Display, 145, 178, 35, 49,
                                 TFT_TRANSPARENT, TFT_TRANSPARENT,
                                 TFT_TRANSPARENT, button_text, 1);
  time_num_3_button.initButtonUL(&this->TFT_Display, 205, 178, 35, 49,
                                 TFT_TRANSPARENT, TFT_TRANSPARENT,
                                 TFT_TRANSPARENT, button_text, 1);
  time_num_4_button.initButtonUL(&this->TFT_Display, 266, 178, 35, 49,
                                 TFT_TRANSPARENT, TFT_TRANSPARENT,
                                 TFT_TRANSPARENT, button_text, 1);
  time_num_5_button.initButtonUL(&this->TFT_Display, 25, 251, 35, 49,
                                 TFT_TRANSPARENT, TFT_TRANSPARENT,
                                 TFT_TRANSPARENT, button_text, 1);
  time_num_6_button.initButtonUL(&this->TFT_Display, 85, 251, 35, 49,
                                 TFT_TRANSPARENT, TFT_TRANSPARENT,
                                 TFT_TRANSPARENT, button_text, 1);
  time_num_7_button.initButtonUL(&this->TFT_Display, 145, 251, 35, 49,
                                 TFT_TRANSPARENT, TFT_TRANSPARENT,
                                 TFT_TRANSPARENT, button_text, 1);
  time_num_8_button.initButtonUL(&this->TFT_Display, 205, 251, 35, 49,
                                 TFT_TRANSPARENT, TFT_TRANSPARENT,
                                 TFT_TRANSPARENT, button_text, 1);
  time_num_9_button.initButtonUL(&this->TFT_Display, 266, 251, 35, 49,
                                 TFT_TRANSPARENT, TFT_TRANSPARENT,
                                 TFT_TRANSPARENT, button_text, 1);
  time_backspace_button.initButtonUL(&this->TFT_Display, 325, 251, 35, 49,
                                     TFT_TRANSPARENT, TFT_TRANSPARENT,
                                     TFT_TRANSPARENT, button_text, 1);

  alarm_add_button.initButtonUL(&this->TFT_Display, 404, 15, 56, 56,
                                TFT_TRANSPARENT, TFT_TRANSPARENT,
                                TFT_TRANSPARENT, button_text, 1);
  alarm_up_button.initButtonUL(&this->TFT_Display, 412, 92, 40, 56,
                               TFT_TRANSPARENT, TFT_TRANSPARENT,
                               TFT_TRANSPARENT, button_text, 1);
  alarm_down_button.initButtonUL(&this->TFT_Display, 412, 172, 40, 56,
                                 TFT_TRANSPARENT, TFT_TRANSPARENT,
                                 TFT_TRANSPARENT, button_text, 1);
  alarm_cancel_button.initButtonUL(&this->TFT_Display, 405, 240, 55, 80,
                                   TFT_TRANSPARENT, TFT_TRANSPARENT,
                                   TFT_TRANSPARENT, button_text, 1);
  alarm_delete_1_button.initButtonUL(&this->TFT_Display, 322, 17, 55, 80,
                                     TFT_TRANSPARENT, TFT_TRANSPARENT,
                                     TFT_TRANSPARENT, button_text, 1);
  alarm_delete_2_button.initButtonUL(&this->TFT_Display, 322, 123, 55, 80,
                                     TFT_TRANSPARENT, TFT_TRANSPARENT,
                                     TFT_TRANSPARENT, button_text, 1);
  alarm_delete_3_button.initButtonUL(&this->TFT_Display, 322, 229, 55, 80,
                                     TFT_TRANSPARENT, TFT_TRANSPARENT,
                                     TFT_TRANSPARENT, button_text, 1);
}

void Display::draw() {
  this->TFT_Display.invertDisplay(this->inverted_colors);
  switch (this->current_screen) {
    case MAIN_SCREEN: {
      MainScreenData data;
      data.current_time = time_handler::getDateTime("H:i:s");
      data.current_date = time_handler::getDateTime("D, d. M");
      data.humidity =
          String(static_cast<int>(round(ambient_sensor::readHumidity()))) + "%";
      if (this->pressure_metric_system) {
        data.pressure =
            String(static_cast<int>(round(ambient_sensor::readPressure()))) +
            " hPa";
      } else {
        data.pressure =
            String(roundf(0.02953 *  // NOLINT(*-narrowing-conversions)
                          ambient_sensor::readPressure() * 100) /
                   100) +
            "\"Hg";
      }
      if (temperature_metric_system) {
        data.temperature =
            String(static_cast<int>(round(ambient_sensor::readTemperature())));
      } else {
        data.temperature = String(static_cast<int>(
            round(ambient_sensor::readTemperature() * 1.8 + 32)));
      }
      time_t t = this->alarm_handler.getNextAlarm();
      if (t != 0) {
        ExtractedTime et = extractAlarmData(t, t);
        data.alarm_time = et.current_time.substring(0, 5);
      } else {
        data.alarm_time = "XX:XX";
      }
      data.is_day = time_handler::isDay();
      this->drawMainScreen(data);
      break;
    }
    case (TIME_SETTING_SCREEN): {
      this->drawTimeSettingScreen();
      break;
    }
    case (ALARM_OVERVIEW_SCREEN): {
      const AlarmList al = this->alarm_handler.getAlarms(this->page);
      this->drawAlarmOverviewScreen(al);
      break;
    }
    case (SETTINGS_SCREEN): {
      break;
    }
  }
}

void Display::handleTouch() {
  uint16_t x = 0, y = 0;

  if (not this->TFT_Display.getTouch(&x, &y)) {
    return;
  }

  if (millis() - this->last_touch < 200) {
    return;
  }

  this->last_touch = millis();

  // INFO: Ignoring narrowing conversion due to problem in TFT_eSPI
  // NOLINTBEGIN(*-narrowing-conversions)
  switch (this->current_screen) {
    case MAIN_SCREEN: {
      if (contrast_button.contains(x, y)) {
        this->inverted_colors = not this->inverted_colors;
      } else if (temperature_button.contains(x, y)) {
        this->temperature_metric_system = not this->temperature_metric_system;
        this->temperature_system_change = true;
      } else if (pressure_button.contains(x, y)) {
        this->pressure_metric_system = not this->pressure_metric_system;
      } else if (time_button.contains(x, y)) {
        this->current_screen = TIME_SETTING_SCREEN;
        this->time_setting_responsibility = CURRENT_TIME;
        this->screen_changed = true;
      } else if (alarm_button.contains(x, y)) {
        this->current_screen = ALARM_OVERVIEW_SCREEN;
        this->screen_changed = true;
      }
      break;
    }
    case TIME_SETTING_SCREEN: {
      if (time_confirm_button.contains(x, y)) {
        if (this->time_setting_responsibility == CURRENT_TIME) {
          const bool success = time_handler::setDateTime(
              this->current_time_setting_screen_data.current_input);
          if (success) {
            this->current_screen = MAIN_SCREEN;
            this->screen_changed = true;
            this->current_time_setting_screen_data = TimeSettingScreenData();
            this->previous_time_setting_screen_data = TimeSettingScreenData();
          }
        } else {
          const time_t epoch = time_handler::getEpochTime(
              this->current_time_setting_screen_data.current_input);
          this->alarm_handler.newAlarm(epoch);
          this->current_screen = ALARM_OVERVIEW_SCREEN;
          this->screen_changed = true;
          this->current_time_setting_screen_data = TimeSettingScreenData();
          this->previous_time_setting_screen_data = TimeSettingScreenData();
        }
      } else if (time_cancel_button.contains(x, y)) {
        if (this->time_setting_responsibility == CURRENT_TIME) {
          this->current_screen = MAIN_SCREEN;
        } else {
          this->current_screen = ALARM_OVERVIEW_SCREEN;
        }
        this->screen_changed = true;
        this->current_time_setting_screen_data = TimeSettingScreenData();
        this->previous_time_setting_screen_data = TimeSettingScreenData();
      } else if (time_backspace_button.contains(x, y) &&
                 this->current_time_setting_screen_data.current_index >= 0) {
        if (this->current_time_setting_screen_data.current_index != -1) {
          this->current_time_setting_screen_data.current_input.setCharAt(
              this->current_time_setting_screen_data.current_index, ' ');
          this->current_time_setting_screen_data.current_index--;
        } else {
          this->current_time_setting_screen_data.current_input.setCharAt(0,
                                                                         ' ');
        }
      } else if (time_num_0_button.contains(x, y) &&
                 this->current_time_setting_screen_data.current_index < 14) {
        if (this->current_time_setting_screen_data.current_index != 13) {
          this->current_time_setting_screen_data.current_index++;
        }
        this->current_time_setting_screen_data.current_input.setCharAt(
            this->current_time_setting_screen_data.current_index, '0');
      } else if (time_num_1_button.contains(x, y) &&
                 this->current_time_setting_screen_data.current_index < 14) {
        if (this->current_time_setting_screen_data.current_index != 13) {
          this->current_time_setting_screen_data.current_index++;
        }
        this->current_time_setting_screen_data.current_input.setCharAt(
            this->current_time_setting_screen_data.current_index, '1');
      } else if (time_num_2_button.contains(x, y) &&
                 this->current_time_setting_screen_data.current_index < 14) {
        if (this->current_time_setting_screen_data.current_index != 13) {
          this->current_time_setting_screen_data.current_index++;
        }
        this->current_time_setting_screen_data.current_input.setCharAt(
            this->current_time_setting_screen_data.current_index, '2');
      } else if (time_num_3_button.contains(x, y) &&
                 this->current_time_setting_screen_data.current_index < 14) {
        if (this->current_time_setting_screen_data.current_index != 13) {
          this->current_time_setting_screen_data.current_index++;
        }
        this->current_time_setting_screen_data.current_input.setCharAt(
            this->current_time_setting_screen_data.current_index, '3');
      } else if (time_num_4_button.contains(x, y) &&
                 this->current_time_setting_screen_data.current_index < 14) {
        if (this->current_time_setting_screen_data.current_index != 13) {
          this->current_time_setting_screen_data.current_index++;
        }
        this->current_time_setting_screen_data.current_input.setCharAt(
            this->current_time_setting_screen_data.current_index, '4');
      } else if (time_num_5_button.contains(x, y) &&
                 this->current_time_setting_screen_data.current_index < 14) {
        if (this->current_time_setting_screen_data.current_index != 13) {
          this->current_time_setting_screen_data.current_index++;
        }
        this->current_time_setting_screen_data.current_input.setCharAt(
            this->current_time_setting_screen_data.current_index, '5');
      } else if (time_num_6_button.contains(x, y) &&
                 this->current_time_setting_screen_data.current_index < 14) {
        if (this->current_time_setting_screen_data.current_index != 13) {
          this->current_time_setting_screen_data.current_index++;
        }
        this->current_time_setting_screen_data.current_input.setCharAt(
            this->current_time_setting_screen_data.current_index, '6');
      } else if (time_num_7_button.contains(x, y) &&
                 this->current_time_setting_screen_data.current_index < 14) {
        if (this->current_time_setting_screen_data.current_index != 13) {
          this->current_time_setting_screen_data.current_index++;
        }
        this->current_time_setting_screen_data.current_input.setCharAt(
            this->current_time_setting_screen_data.current_index, '7');
      } else if (time_num_8_button.contains(x, y) &&
                 this->current_time_setting_screen_data.current_index < 14) {
        if (this->current_time_setting_screen_data.current_index != 13) {
          this->current_time_setting_screen_data.current_index++;
        }
        this->current_time_setting_screen_data.current_input.setCharAt(
            this->current_time_setting_screen_data.current_index, '8');
      } else if (time_num_9_button.contains(x, y) &&
                 this->current_time_setting_screen_data.current_index < 14) {
        if (this->current_time_setting_screen_data.current_index != 13) {
          this->current_time_setting_screen_data.current_index++;
        }
        this->current_time_setting_screen_data.current_input.setCharAt(
            this->current_time_setting_screen_data.current_index, '9');
      }

      const String curr = this->current_time_setting_screen_data.current_input;
      this->current_time_setting_screen_data.current_time =
          curr.substring(0, 2) + ":" + curr.substring(2, 4) + ":" +
          curr.substring(4, 6);
      this->current_time_setting_screen_data.current_date =
          curr.substring(6, 8) + "." + curr.substring(8, 10) + "." +
          curr.substring(10);
      break;
    }
    case ALARM_OVERVIEW_SCREEN: {
      if (alarm_add_button.contains(x, y)) {
        this->current_alarms = AlarmList();
        this->current_screen = TIME_SETTING_SCREEN;
        this->time_setting_responsibility = SET_ALARM;
        this->screen_changed = true;
      } else if (alarm_up_button.contains(x, y) &&
                 !this->current_alarms.is_first_page) {
        this->page -= 1;
      } else if (alarm_down_button.contains(x, y) &&
                 !this->current_alarms.is_last_page) {
        this->page += 1;
      } else if (alarm_cancel_button.contains(x, y)) {
        this->current_screen = MAIN_SCREEN;
        this->screen_changed = true;
        this->current_alarms = AlarmList();
      } else if (alarm_delete_1_button.contains(x, y) &&
                 this->current_alarms.alarm1 != 0) {
        this->alarm_handler.removeAlarm(this->page * 3);
      } else if (alarm_delete_2_button.contains(x, y) &&
                 this->current_alarms.alarm2 != 0) {
        this->alarm_handler.removeAlarm(this->page * 3 + 1);
      } else if (alarm_delete_3_button.contains(x, y) &&
                 this->current_alarms.alarm3 != 0) {
        this->alarm_handler.removeAlarm(this->page * 3 + 2);
      }
      break;
    }
    case SETTINGS_SCREEN: {
      break;
    }
  }
  // NOLINTEND(*-narrowing-conversions)
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

  if (this->temperature_system_change || this->screen_changed) {
    // Temperature Celsius
    if (temperature_metric_system) {
      this->TFT_Display.drawBitmap(322, 208, TEMPERATURE_FAHRENHEIT_IMAGE, 48,
                                   48, TFT_BLACK);
      this->TFT_Display.drawBitmap(322, 208, TEMPERATURE_CELSIUS_IMAGE, 48, 48,
                                   TFT_WHITE);
    } else {
      this->TFT_Display.drawBitmap(322, 208, TEMPERATURE_CELSIUS_IMAGE, 48, 48,
                                   TFT_BLACK);
      this->TFT_Display.drawBitmap(322, 208, TEMPERATURE_FAHRENHEIT_IMAGE, 48,
                                   48, TFT_WHITE);
    }
    this->temperature_system_change = false;
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
    if (this->time_dependent_theme) {
      this->inverted_colors = main_screen_data.is_day;
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
  const TimeSettingScreenData previous_data =
      this->previous_time_setting_screen_data;

  if (this->screen_changed) {
    this->TFT_Display.fillScreen(TFT_BLACK);

    // Icons & Lines & Numpad
    // Confirm
    this->TFT_Display.drawBitmap(404, 49, CONFIRM_IMAGE, 56, 64, TFT_WHITE);
    // Cancel
    this->TFT_Display.drawBitmap(405, 201, CANCEL_IMAGE, 55, 80, TFT_WHITE);
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
    // Line 1
    this->TFT_Display.drawLine(384, 0, 384, 320, TFT_WHITE);
    // Line 2
    this->TFT_Display.drawLine(0, 139, 384, 139, TFT_WHITE);

    this->TFT_Display.setTextSize(5);
    // Time
    this->TFT_Display.drawString(
        this->current_time_setting_screen_data.current_time, 74, 20);
    // Date
    this->TFT_Display.drawString(
        this->current_time_setting_screen_data.current_date, 44, 65);
  }

  // Time
  if (current_data.current_time != previous_data.current_time) {
    this->TFT_Display.setTextColor(TFT_BLACK);
    this->TFT_Display.drawString(
        this->previous_time_setting_screen_data.current_time, 74, 20);
    this->TFT_Display.setTextColor(TFT_WHITE);
    this->TFT_Display.drawString(
        this->current_time_setting_screen_data.current_time, 74, 20);
  }

  // Date
  if (current_data.current_date != previous_data.current_date) {
    this->TFT_Display.setTextColor(TFT_BLACK);
    this->TFT_Display.drawString(
        this->previous_time_setting_screen_data.current_date, 44, 65);
    this->TFT_Display.setTextColor(TFT_WHITE);
    this->TFT_Display.drawString(
        this->current_time_setting_screen_data.current_date, 44, 65);
  }

  this->previous_time_setting_screen_data.current_time =
      this->current_time_setting_screen_data.current_time;
  this->previous_time_setting_screen_data.current_date =
      this->current_time_setting_screen_data.current_date;

  if (this->screen_changed) {
    this->screen_changed = false;
  }
}

void Display::drawAlarmOverviewScreen(const AlarmList &alarm_list) {
  if (this->screen_changed) {
    this->TFT_Display.fillScreen(TFT_BLACK);
    // cancel
    this->TFT_Display.drawBitmap(405, 240, CANCEL_IMAGE, 55, 80, TFT_WHITE);
    // Plus 2
    this->TFT_Display.fillRect(404, 38, 56, 10, TFT_WHITE);
    // Plus 1
    this->TFT_Display.fillRect(427, 15, 10, 56, TFT_WHITE);
    // Line 3
    this->TFT_Display.drawLine(0, 213, 388, 213, TFT_WHITE);
    // Line 2
    this->TFT_Display.drawLine(0, 108, 388, 108, TFT_WHITE);
    // Line 1
    this->TFT_Display.drawLine(388, 1, 388, 317, TFT_WHITE);
  }

  // Arrow Up
  if (alarm_list.is_first_page != this->current_alarms.is_first_page) {
    if (alarm_list.is_first_page) {
      this->TFT_Display.drawBitmap(412, 93, ARROW_UP_IMAGE, 40, 56, TFT_BLACK);
    } else {
      this->TFT_Display.drawBitmap(412, 93, ARROW_UP_IMAGE, 40, 56, TFT_WHITE);
    }
  }

  // Arrow Down
  if (alarm_list.is_last_page != this->current_alarms.is_last_page) {
    if (alarm_list.is_last_page) {
      this->TFT_Display.drawBitmap(412, 172, ARROW_DOWN_IMAGE, 40, 56,
                                   TFT_BLACK);
    } else {
      this->TFT_Display.drawBitmap(412, 172, ARROW_DOWN_IMAGE, 40, 56,
                                   TFT_WHITE);
    }
  }

  // Alarm 1
  if (alarm_list.alarm1 != this->current_alarms.alarm1) {
    const ExtractedTime et =
        extractAlarmData(alarm_list.alarm1, this->current_alarms.alarm1);

    if (this->current_alarms.alarm1 != 0) {
      TFT_Display.setTextColor(TFT_BLACK);
      // Time 1
      this->TFT_Display.drawString(et.previous_time, 45, 15);
      // Date 1
      this->TFT_Display.drawString(et.previous_date, 15, 60);

      TFT_Display.setTextColor(TFT_WHITE);
    }

    if (alarm_list.alarm1 == 0) {
      // Delete Alarm 1
      this->TFT_Display.drawBitmap(322, 17, CANCEL_IMAGE, 55, 80, TFT_BLACK);
    } else {
      Serial.println(et.current_time);
      // Delete Alarm 1
      this->TFT_Display.drawBitmap(322, 17, CANCEL_IMAGE, 55, 80, TFT_WHITE);
      // Time 1
      this->TFT_Display.drawString(et.current_time, 45, 15);
      // Date 1
      this->TFT_Display.drawString(et.current_date, 15, 60);
    }
  }

  // Alarm 2
  if (alarm_list.alarm2 != this->current_alarms.alarm2) {
    const ExtractedTime et =
        extractAlarmData(alarm_list.alarm2, this->current_alarms.alarm2);

    if (this->current_alarms.alarm2 != 0) {
      TFT_Display.setTextColor(TFT_BLACK);
      // Time 1
      this->TFT_Display.drawString(et.previous_time, 45, 120);
      // Date 1
      this->TFT_Display.drawString(et.previous_date, 15, 165);

      TFT_Display.setTextColor(TFT_WHITE);
    }

    if (alarm_list.alarm2 == 0) {
      // Delete Alarm 1
      this->TFT_Display.drawBitmap(322, 123, CANCEL_IMAGE, 55, 80, TFT_BLACK);
    } else {
      // Delete Alarm 1
      this->TFT_Display.drawBitmap(322, 123, CANCEL_IMAGE, 55, 80, TFT_WHITE);
      // Time 1
      this->TFT_Display.drawString(et.current_time, 45, 120);
      // Date 1
      this->TFT_Display.drawString(et.current_date, 15, 165);
    }
  }

  // Alarm 3
  if (alarm_list.alarm3 != this->current_alarms.alarm3) {
    const ExtractedTime et =
        extractAlarmData(alarm_list.alarm3, this->current_alarms.alarm3);

    if (this->current_alarms.alarm3 != 0) {
      TFT_Display.setTextColor(TFT_BLACK);
      // Time 1
      this->TFT_Display.drawString(et.previous_time, 45, 226);
      // Date 1
      this->TFT_Display.drawString(et.previous_date, 15, 270);

      TFT_Display.setTextColor(TFT_WHITE);
    }

    if (alarm_list.alarm3 == 0) {
      // Delete Alarm 1
      this->TFT_Display.drawBitmap(322, 229, CANCEL_IMAGE, 55, 80, TFT_BLACK);
    } else {
      // Delete Alarm 1
      this->TFT_Display.drawBitmap(322, 229, CANCEL_IMAGE, 55, 80, TFT_WHITE);
      // Time 1
      this->TFT_Display.drawString(et.current_time, 45, 226);
      // Date 1
      this->TFT_Display.drawString(et.current_date, 15, 270);
    }
  }

  this->screen_changed = false;
  this->current_alarms = alarm_list;
}

void Display::drawSettingsScreen() {}
}  // namespace display

ExtractedTime extractAlarmData(const time_t current_time_t,
                               const time_t previous_time_t) {
  const tm *current = std::localtime(&current_time_t);
  constexpr size_t time_size = 9;
  constexpr size_t date_size = 11;
  char curr_time[time_size];
  char curr_date[date_size];
  strftime(curr_time, time_size, "%T", current);
  strftime(curr_date, date_size, "%d.%m.%Y", current);

  const tm *previous = std::localtime(&previous_time_t);
  char prev_time[time_size];
  char prev_date[date_size];
  strftime(prev_time, time_size, "%T", previous);
  strftime(prev_date, date_size, "%d.%m.%Y", previous);

  ExtractedTime ET;

  ET.current_time = String(curr_time);
  ET.current_date = String(curr_date);
  ET.previous_time = String(prev_time);
  ET.previous_date = String(prev_date);

  return ET;
}