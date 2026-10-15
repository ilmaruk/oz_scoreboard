#include "config.h"
#include "secrets.h"

#include <MD_Parola.h>

// #include <Arduino.h>
#include <PubSubClient.h>

#define ZONE_L 0
#define ZONE_C 1
#define ZONE_R 2

bool info_has_changed = true;
char szMesg[3][8] = {"?", "0-0", "?"};

#include "wifi.h"
#include "mqtt.h"
#include "clock_font.h"

WiFiClient espClient;
PubSubClient client(espClient);

MD_Parola display = MD_Parola(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);

void setup()
{
  // Serial setup
  Serial.begin(115200);

  // WiFi setup
  WiFi.mode(WIFI_STA);

  // MQTT setup
  client.setServer(MQTT_SERVER, 1883);
  client.setCallback(handle_mqtt_message);

  // Display setop
  display.begin(3);

  display.setZone(ZONE_L, 3, 3);
  display.setZone(ZONE_C, 1, 2);
  display.setZone(ZONE_R, 0, 0);

  display.setFont(oz_score);

  display.displayZoneText(ZONE_L, szMesg[ZONE_L], PA_LEFT, 0, 0,
                          PA_NO_EFFECT, PA_NO_EFFECT);
  display.displayZoneText(ZONE_C, szMesg[ZONE_C], PA_CENTER, 0, 0,
                          PA_NO_EFFECT, PA_NO_EFFECT);
  display.displayZoneText(ZONE_R, szMesg[ZONE_R], PA_RIGHT, 0, 0,
                          PA_NO_EFFECT, PA_NO_EFFECT);
}

void loop()
{
  connectToWiFi(wifi_ssid, wifi_password);

  if (!client.connected()) {
    reconnect_to_mqtt(&client);
  }
  client.loop();

  if (display.displayAnimate() && info_has_changed) {
    display.displayZoneText(ZONE_L, szMesg[ZONE_L], PA_LEFT, 0, 0,
                            PA_NO_EFFECT, PA_NO_EFFECT);
    display.displayZoneText(ZONE_C, szMesg[ZONE_C], PA_CENTER, 0, 0,
                            PA_NO_EFFECT, PA_NO_EFFECT);
    display.displayZoneText(ZONE_R, szMesg[ZONE_R], PA_RIGHT, 0, 0,
                            PA_NO_EFFECT, PA_NO_EFFECT);

    info_has_changed = false;
  }

  delay(500);
}
