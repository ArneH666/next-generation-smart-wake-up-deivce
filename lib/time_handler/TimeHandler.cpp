#include "TimeHandler.hpp"
#include "ezTime.h"
#include <Arduino.h>

#include <utility>

Timezone TZGermany;

namespace time_handler {
void setup() {
  waitForSync();
  TZGermany.setLocation("Europe/Berlin");
}

String getDateTime(String time_format) {
  return TZGermany.dateTime(std::move(time_format));
}
} // namespace time_handler