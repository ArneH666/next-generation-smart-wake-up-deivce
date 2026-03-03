#include "TimeHandler.hpp"

#include <Arduino.h>
#include <ezTime.h>
#include <sunset.h>

#include <EnvironmentVariables.hpp>
#include <iomanip>
#include <locale>
#include <sstream>

Timezone TZGermany;
SunSet Sun;

String date = "";
double sunrise;
double sunset;

namespace time_handler {
void setup() {
  waitForSync(1);
  TZGermany.setLocation("Europe/Berlin");
  Sun.setPosition(LATITUDE, LONGITUDE, 1);
}

String getDateTime(String time_format) {
  return TZGermany.dateTime(std::move(time_format));
}

bool isDay() {
  if (date != TZGermany.dateTime("d.m.Y")) {
    Sun.setCurrentDate(TZGermany.year(), TZGermany.month(), TZGermany.day());
    sunrise = Sun.calcCivilSunrise();
    sunset = Sun.calcCivilSunset();
  }
  const double minutes_past_midnight =
      TZGermany.hour() * 60 + TZGermany.minute() +
      static_cast<double>(TZGermany.second()) / 60 +
      static_cast<double>(TZGermany.ms()) / 60000;
  return sunrise <= minutes_past_midnight && minutes_past_midnight < sunset;
}

bool setDateTime(const String& data) {
  if (getEpochTime(data) == -1) return false;

  const uint8_t hours = data.substring(0, 2).toInt(),
                minutes = data.substring(2, 4).toInt(),
                seconds = data.substring(4, 6).toInt(),
                days = data.substring(6, 8).toInt(),
                months = data.substring(8, 10).toInt();
  const uint16_t years = data.substring(10).toInt();

  Serial.printf("%u, %u, %u, %u, %u, %u\n", hours, minutes, seconds, days,
                months, years);

  TZGermany.setTime(hours, minutes, seconds, days, months, years);

  return true;
}

time_t getCurrentEpoch() { return TZGermany.now(); }

time_t getEpochTime(const String& data) {
  if (data.indexOf(' ') != -1) {
    return -1;
  }

  const String formatted = data.substring(6, 8) + "-" + data.substring(8, 10) +
                           "-" + data.substring(10) + "_" +
                           data.substring(0, 2) + "-" + data.substring(2, 4) +
                           "-" + data.substring(4, 6);

  std::tm t = {};
  std::istringstream ss(formatted.c_str());
  ss >> std::get_time(&t, "%d-%m-%Y_%H-%M-%S");

  if (ss.fail()) {
    return -1;
  }

  return mktime(&t);
}
}  // namespace time_handler