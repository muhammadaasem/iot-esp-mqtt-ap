
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
  mqttClient.begin(); //BUG01: if ssid, pw, broker, etc are not in eeprom correctly, then infinite loop goes on.

  // Initialize commander
  // Remove commander.begin() if it does not exist in your ESPCommander class
}

void loop() {
  // Handle AP server client
  apServer.handleClient();



  // Handle MQTT client
  mqttClient.handleClient();

  // Check if a new MQTT message has been received
  String command = mqttClient.getLastMessage();
  if (command != "") {
    // Pass the command to the commander
    // commander.handleCommand(command); if its string only
    commander.handleCommandJSON(command);


    // Clear the last message to indicate it has been handled
    mqttClient.setLastMessage("");
  }


  // Handle any other tasks
  // ...*/
}

