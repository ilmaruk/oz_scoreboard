#ifndef _MQTT_H
#define _MQTT_H

#include <ArduinoJson.h>

void reconnect_to_mqtt(PubSubClient* client) {
  // Loop until we're reconnected
  while (!client->connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client->connect(MQTT_CLIENT_NAME)) {
      Serial.println("connected");
      // Subscribe
      client->subscribe(MQTT_TOPIC, 1);
    } else {
      Serial.print("failed, rc=");
      Serial.print(client->state());
      Serial.println(" try again in 1 second");
      delay(1000);
    }
  }
}

void handle_mqtt_message(char* topic, byte* message, unsigned int length) {
  Serial.print("Message arrived on topic: ");
  Serial.println(topic);

  JsonDocument doc;
  deserializeJson(doc, message);

  const char* home_id = doc["home_id"];
  const char* away_id = doc["away_id"];
  size_t home_score = doc["home_score"];
  size_t away_score = doc["away_score"];
  
  snprintf(szMesg[ZONE_L], sizeof(szMesg[ZONE_L]), "%c", home_id[0]);
  snprintf(szMesg[ZONE_C], sizeof(szMesg[ZONE_C]), "%d-%d", home_score, away_score);
  snprintf(szMesg[ZONE_R], sizeof(szMesg[ZONE_R]), "%c", away_id[0]);

  info_has_changed = true;
}

#endif // _MQTT_H