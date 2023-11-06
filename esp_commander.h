// esp_commander.h
#ifndef ESP_COMMANDER_H
#define ESP_COMMANDER_H

#include <Arduino.h>

#define MAX_RELAYS 4

class ESPCommander {
public:
  ESPCommander(int relayPins[]);
  void handleCommand(const String& command);
  void begin();

private:
  int relayPins[MAX_RELAYS];
};

#endif // ESP_COMMANDER_H