// esp_commander.cpp
#include "esp_commander.h"

ESPCommander::ESPCommander(int pins[]) {
  for (int i = 0; i < MAX_RELAYS; i++) {
    relayPins[i] = pins[i];
  }
}

void ESPCommander::begin() {
  for (int i = 0; i < MAX_RELAYS; i++) {
    pinMode(relayPins[i], OUTPUT);
    digitalWrite(relayPins[i], LOW); // Initialize relays to OFF
  }
}

void ESPCommander::handleCommand(const String& command) {
  // Example command parsing
  if (command.startsWith("TURN_ON")) {
    int relayNumber = command.substring(8).toInt();
    if (relayNumber >= 0 && relayNumber < MAX_RELAYS) {
      digitalWrite(relayPins[relayNumber], HIGH);
      Serial.println("Relay " + String(relayNumber) + " turned on.");
    }
  } else if (command.startsWith("TURN_OFF")) {
    int relayNumber = command.substring(9).toInt();
    if (relayNumber >= 0 && relayNumber < MAX_RELAYS) {
      digitalWrite(relayPins[relayNumber], LOW);
      Serial.println("Relay " + String(relayNumber) + " turned off.");
    }
  }
  // Add more else if blocks for additional commands
}
