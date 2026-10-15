# OZ Scoreboard

This project is a small ESP32-based scoreboard that shows a live sports score on a MAX7219 LED matrix display.

The device connects to Wi‑Fi, subscribes to an MQTT topic, and updates the display whenever a new JSON message arrives. It shows:

- the home team short name on the left
- the current score in the center
- the away team short name on the right

Example payload:

```json
{
  "home_id": "A",
  "away_id": "B",
  "home_score": 2,
  "away_score": 1
}
```

This is intended for a simple scoreboard use case, such as a local match display or a simulated scoreboard in Wokwi.

## Project structure

- `wokwi/` contains the Arduino sketch and Wokwi simulation files
- `wokwi/sketch.ino` is the main ESP32 firmware
- `wokwi/diagram.json` describes the simulated hardware setup

## Hardware

- ESP32 dev board
- 4x MAX7219 LED matrix modules
- Wi‑Fi and MQTT connection for live updates

## Software

The firmware:

- connects to Wi‑Fi
- connects to an MQTT broker
- listens on a configured topic
- parses score updates from JSON
- refreshes the LED display text
