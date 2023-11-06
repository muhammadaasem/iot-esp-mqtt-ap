
/**************************
broker: broker.hivemq.com
topic: testingESP1234/data
json payload:
{
  "command": "setStatus",
  "switch1": "OFF",
  "switch2": "ON",
  "switch3": "OFF"
}

**************************/



#include <Arduino.h>
#include <ESP8266WiFi.h>
#include "ConfigParams.h"      // Include the ConfigParams definition
#include "esp_eeprom.h"
#include "esp_AP_server.h"
#include "esp_MQTT_client.h"
#include "esp_commander.h"

// Initialize configuration with sample values
ConfigParams config = {
  "WIFI_SSID",             // SSID
  "yourpassowrd",         // Password
  "broker.emqx.io",   // MQTT server
  1883,                   // MQTT port
  "testingESP1234/data",      // Operation topic
  "testingESP1234/config"          // Configuration topic
};

// Instances of your classes
ESPEEPROMManager eepromManager;
ESPAPServer apServer;
ESPMQTTClient mqttClient(config);
ESPCommander commander(config.relayPins); // Pass the relay pins from config

void setup() {
  // Start the serial communication
  Serial.begin(115200);
  Serial.print("\n\nStarting....\n\n");

  // Initialize EEPROM and load the configuration
  eepromManager.begin();
  config = eepromManager.getConfig();

  // Initialize the Access Point
  apServer.begin();

  // Initialize the MQTT client
  mqttClient.begin();

  // Initialize commander
  // Remove commander.begin() if it does not exist in your ESPCommander class
}

void loop() {
  // Handle AP server client
  apServer.handleClient();

  // Handle MQTT client
  mqttClient.handleClient();

  // Handle commander tasks
  // You would typically have some logic to read commands and pass them to the commander
  // For example:
  // String command = readCommand(); // Implement readCommand to get commands from an input source
  // commander.handleCommand(command);

  // Handle any other tasks
  // ...
}
