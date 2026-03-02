#ifndef NEXT_GENERATION_SMART_WAKE_UP_DEIVCE_DISPLAY_HPP
#define NEXT_GENERATION_SMART_WAKE_UP_DEIVCE_DISPLAY_HPP

#include <TFT_eSPI.h>

#include <AlarmHandler.hpp>

enum CurrentScreen {
  MAIN_SCREEN,
  TIME_SETTING_SCREEN,
  ALARM_OVERVIEW_SCREEN,
  SETTINGS_SCREEN,
};

enum TimeSettingResponsibility {
  CURRENT_TIME,
  SET_ALARM,
  UNDEFINED,
};

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
  int current_index = -1;
};

struct ExtractedTime {
  String current_time;
  String current_date;
  String previous_time;
  String previous_date;
};

namespace display {
class Display {
 public:
  explicit Display(const alarm_handler::AlarmHandler& handler);
  void draw();
  void handleTouch();

 private:
  void drawMainScreen(const MainScreenData &main_screen_data);
  void drawTimeSettingScreen();
  void drawAlarmOverviewScreen(const AlarmList &alarm_list);
  void drawSettingsScreen();

  TFT_eSPI TFT_Display;
  alarm_handler::AlarmHandler alarm_handler;
  CurrentScreen current_screen = MAIN_SCREEN;
  MainScreenData current_main_screen_data;
  TimeSettingScreenData current_time_setting_screen_data;
  TimeSettingScreenData previous_time_setting_screen_data;
  AlarmList current_alarms;
  TimeSettingResponsibility time_setting_responsibility;
  bool pressure_metric_system = true;
  bool temperature_metric_system = true;
  bool temperature_system_change = false;
  bool inverted_colors = false;
  bool screen_changed = true;
  int page = 0;
  unsigned long last_touch = 0;

  bool time_dependent_theme = true;
};
}  // namespace display

#endif  // NEXT_GENERATION_SMART_WAKE_UP_DEIVCE_DISPLAY_HPP