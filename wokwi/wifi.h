#ifndef _WIFI_H
#define _WIFI_H

#include <WiFi.h>

void connectToWiFi(const char* ssid, const char* pass) {
  if (WiFi.status() == WL_CONNECTED) return;

  Serial.print("Connecting to WiFi ");
  Serial.print(ssid);
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(100);
  }
  Serial.print("Connected with IP ");
  Serial.println(WiFi.localIP());
}

#endif // _WIFI_H