#ifndef NEXT_GENERATION_SMART_WAKE_UP_DEIVCE_DISPLAY_HPP
#define NEXT_GENERATION_SMART_WAKE_UP_DEIVCE_DISPLAY_HPP

#include <Arduino.h>
#include <TFT_eSPI.h>

#include <ProjectTypes.hpp>

enum CurrentScreen {
  MAIN_SCREEN,
  TIME_SCREEN,
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
  void drawTimeScreen();
  void drawSettingsScreen();

  TFT_eSPI TFT_Display;
  TFT_eSprite TFT_Sprite;
  CurrentScreen current_screen = MAIN_SCREEN;
  bool unit_system_metric = true;
  bool inverted_colors = false;
};
}  // namespace display

#endif  // NEXT_GENERATION_SMART_WAKE_UP_DEIVCE_DISPLAY_HPP