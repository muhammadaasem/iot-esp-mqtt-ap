// esp_commander.cpp
#include "esp_commander.h"

ESPCommander::ESPCommander(int pins[]) {
  for (int i = 0; i < MAX_RELAYS; i++) {
    relayPins[i] = pins[i];
  }
}

void ESPCommander::begin() {
  pinMode(LED_BUILTIN, OUTPUT);
  for (int i = 0; i < MAX_RELAYS; i++) {
    pinMode(relayPins[i], OUTPUT);
    digitalWrite(relayPins[i], LOW); // Initialize relays to OFF
  }
}

void ESPCommander::handleCommand(const String& command) {
  Serial.println("Command received:");
  Serial.print(command);

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


bool ESPCommander::handleCommandJSON(const String& command) {
  StaticJsonDocument<256> doc; // Adjust the size according to your needs
  DeserializationError error = deserializeJson(doc, command);

  if (error) {
    Serial.print("JSON deserializeJson() failed: ");
    Serial.println(error.c_str());
    return false;
  }

  const char* commandStr = doc["command"]; // Extract the command value
  if (!commandStr) {
    Serial.println("JSON does not contain 'command'");
    return false;
  }

  if (strcmp(commandStr, "TURN_ON") == 0) {
    // Get additional parameters if needed
    // Perform TURN ON action
    digitalWrite(LED_BUILTIN, HIGH);
    Serial.println("Command TURN_ON executed");
  } else if (strcmp(commandStr, "TURN_OFF") == 0) {
    // Perform TURN OFF action
    
    digitalWrite(LED_BUILTIN, LOW);
    Serial.println("Command TURN_OFF executed");
  } else {
    Serial.print("UNKNOWN command executed: ");
    Serial.println(commandStr);
  }

  // Add more else if blocks for additional commands

  return true;
}