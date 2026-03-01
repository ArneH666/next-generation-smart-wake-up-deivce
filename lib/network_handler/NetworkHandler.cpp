#include "NetworkHandler.hpp"

#include <WiFi.h>

#include <EnvironmentVariables.hpp>

namespace network_handler {
void setup() {
  Serial.println("Starting Network Connection.");

  WiFiClass::mode(WIFI_STA);
  WiFiClass::setHostname("Scania Alarm");
  WiFi.begin(SSID, PASSWORD);

  Serial.println("Starting Network Connection.");

  for (int i = 0; i < 5; i++) {
    if (WiFiClass::status() != WL_CONNECTED) {
      Serial.println("Waiting for WiFi connection ...");
      delay(1000);
    } else {
      break;
    }
  }

  if (WiFiClass::status() == WL_CONNECTED) {
    Serial.printf(
        "Connected to Network successfully.\n"
        "-> Local IP: %s\n"
        "-> WiFi Strength: %i\n",
        WiFi.localIP().toString().c_str(), WiFi.RSSI());
  }
}
}  // namespace network_handler