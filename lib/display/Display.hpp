#ifndef NEXT_GENERATION_SMART_WAKE_UP_DEIVCE_DISPLAY_HPP
#define NEXT_GENERATION_SMART_WAKE_UP_DEIVCE_DISPLAY_HPP

#include <TFT_eSPI.h>

#include <ProjectTypes.hpp>

enum CurrentScreen {
  MAIN_SCREEN,
  TIME_SETTING_SCREEN,
  ALARM_SETTING_SCREEN,
  SETTINGS_SCREEN,
};

namespace display {
class Display {
 public:
  Display();
  void draw();
  void handleTouch();

 private:
  void drawMainScreen(const MainScreenData &main_screen_data);
  void drawTimeSettingScreen();
  void drawAlarmSettingScreen();
  void drawSettingsScreen();

  TFT_eSPI TFT_Display;
  CurrentScreen current_screen = MAIN_SCREEN;
  MainScreenData current_main_screen_data;
  TimeSettingScreenData current_time_setting_screen_data;
  bool pressure_metric_system = true;
  bool temperature_metric_system = true;
  bool inverted_colors = false;
  bool screen_changed = true;
  unsigned long last_touch = 0;
};
}  // namespace display

#endif  // NEXT_GENERATION_SMART_WAKE_UP_DEIVCE_DISPLAY_HPP