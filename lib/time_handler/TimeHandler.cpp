#include "TimeHandler.hpp"

#include <Arduino.h>
#include <ezTime.h>
#include <sunset.h>

#include <EnvironmentVariables.hpp>

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
      TZGermany.hour() * 60 + TZGermany.minute() + TZGermany.second() / 60 +
      TZGermany.ms() / 60000;
  return sunrise <= minutes_past_midnight && minutes_past_midnight < sunset;
}
}  // namespace time_handler