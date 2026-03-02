#ifndef NEXT_GENERATION_SMART_WAKE_UP_DEIVCE_ALARMHANDLER_HPP
#define NEXT_GENERATION_SMART_WAKE_UP_DEIVCE_ALARMHANDLER_HPP

#include <ctime>
#include <vector>

struct AlarmList {
  time_t alarm1 = 0;
  time_t alarm2 = 0;
  time_t alarm3 = 0;
  bool is_first_page = false;
  bool is_last_page = true;
};

namespace alarm_handler {
class AlarmHandler {
 public:
  void newAlarm(time_t alarm_time);
  void removeAlarm(long alarm_index);
  bool checkForAlarm();
  void turnOffAlarm();
  time_t getNextAlarm() const;
  AlarmList getAlarms(int page) const;

 private:
  bool current_alarm = false;
  std::vector<time_t> alarmList = {1772317233, 1772318233, 1772319233,
                                   1772329233, 1772339233, 1772349233,
                                   1772349233};
};
}  // namespace alarm_handler

#endif  // NEXT_GENERATION_SMART_WAKE_UP_DEIVCE_ALARMHANDLER_HPP