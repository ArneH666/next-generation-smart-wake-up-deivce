#include "AlarmHandler.hpp"

#include <Arduino.h>
#include <ezTime.h>

#include <TimeHandler.hpp>
#include <algorithm>
#include <cmath>
#include <iterator>

namespace alarm_handler {
void AlarmHandler::newAlarm(const time_t alarm_time) {
  const auto pos = std::upper_bound(this->alarmList.begin(),
                                    this->alarmList.end(), alarm_time);
  this->alarmList.insert(pos, alarm_time);
}

void AlarmHandler::removeAlarm(const long alarm_index) {
  this->alarmList.erase(this->alarmList.begin() + alarm_index);
  this->alarmList.shrink_to_fit();
}

bool AlarmHandler::checkForAlarm() {
  if (this->current_alarm) {
    return true;
  }

  if (this->alarmList.empty()) {
    return false;
  }

  if (this->alarmList.front() > time_handler::getCurrentEpoch()) {
    return false;
  }

  this->alarmList.erase(this->alarmList.begin());
  this->alarmList.shrink_to_fit();
  this->current_alarm = true;

  return true;
}

void AlarmHandler::turnOffAlarm() { this->current_alarm = false; }

time_t AlarmHandler::getNextAlarm() const {
  if (this->alarmList.empty()) {
    return 0;
  }
  return this->alarmList.front();
}

AlarmList AlarmHandler::getAlarms(const int page) const {
  const uint length = this->alarmList.size();
  const uint pages = ceil(length / 3);
  const uint offset_element = page * 3;

  AlarmList list;

  list.is_first_page = page == 0;
  list.is_last_page = page == pages;

  if (length > offset_element) {
    list.alarm1 = this->alarmList.at(offset_element);
  }
  if (length > offset_element + 1) {
    list.alarm2 = this->alarmList.at(offset_element + 1);
  }
  if (length > offset_element + 2) {
    list.alarm3 = this->alarmList.at(offset_element + 2);
  }

  return list;
}
}  // namespace alarm_handler