#ifndef NEXT_GENERATION_SMART_WAKE_UP_DEIVCE_SPEAKER_HPP
#define NEXT_GENERATION_SMART_WAKE_UP_DEIVCE_SPEAKER_HPP

#include <ctime>

#define BUFFER_SAMPLES 1024

enum ToneState {
  TONE_OFF,
  TONE_ON,
};

namespace speaker {
class Speaker {
 public:
  Speaker();
  void startAlarm();
  void writeAlarm();
  void endAlarm();

 private:
  void generateTone(int16_t *buffer);
  static void generateSilence(int16_t *buffer);

  bool alarm_active = false;
  int16_t audio_buffer[BUFFER_SAMPLES]{};
  unsigned long last_toggle = 0;
  ToneState tone_state = TONE_OFF;
  float phase = 0.0f;
};
}  // namespace speaker

#endif  // NEXT_GENERATION_SMART_WAKE_UP_DEIVCE_SPEAKER_HPP