#ifndef _CONFIG_H
#define _CONFIG_H

// Max7219 display
#define HARDWARE_TYPE MD_MAX72XX::PAROLA_HW
#define MAX_DEVICES 4

#define CLK_PIN 18  // VSPI_SCK
#define DATA_PIN 23 // VSPI_MOSI
#define CS_PIN 5    // VSPI_SS

// MQTT
const char* MQTT_SERVER = "broker.hivemq.com";
const char* MQTT_TOPIC = "oz/scoreboard";
const char* MQTT_CLIENT_NAME = "oz-score";

#endif // _CONFIG_H