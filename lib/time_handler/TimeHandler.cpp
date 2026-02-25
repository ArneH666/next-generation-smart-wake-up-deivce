#include "TimeHandler.hpp"

#include <Arduino.h>
#include <ezTime.h>

Timezone TZGermany;

namespace time_handler {
void setup() {
  waitForSync();
  TZGermany.setLocation("Europe/Berlin");
}

String getDateTime(String time_format) {
  return TZGermany.dateTime(std::move(time_format));
}
}  // namespace time_handler