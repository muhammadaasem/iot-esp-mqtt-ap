
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
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include "ConfigParams.h"      // Include the ConfigParams definition
#include "esp_eeprom.h"
#include "esp_AP_server.h"
#include "esp_MQTT_client.h"

#define AP_MODE 1
#define STA_MODE 2
#define MQTT_MODE 3

int connection_mode=AP_MODE;

// create an instance only. Its values will be populated at AP mode using form 
ConfigParams config;
String command="";

// Instances of your classes
ESPEEPROMManager eepromManager;
ESPAPServer apServer;
ESPMQTTClient mqttClient(config);

void setup() {
  // Start the serial communication
  Serial.begin(115200);
  Serial.print("\n\nStarting....\n\n");

  // Initialize EEPROM and load the configuration
  eepromManager.begin();
  config = eepromManager.getConfig();// New device will show blank values for config parameters

  if (connection_mode >=AP_MODE){
    apServer.begin(); // Initialize the Access Point
  }
  
  if (connection_mode >=MQTT_MODE){
    // Initialize the MQTT client
    // mqttClient.begin();
    mqttClient.begin(); 
    /* BUG01: infinite-connectivity-trials-for-MQTT 
    description: if ssid, pw, broker, etc are not in eeprom correctly, then infinite loop goes on.
    possible fix: attempt connectivity for MAX_MQTT_CONNECTION_TRIALS times after each 5 minutes delay.
    set flag CONNECTION_IS_ALIVE = 1 if its connected otherwise set CONNECTION_IS_ALIVE = 0
    */
  }


  // MY CODE for setup
    pinMode(LED_BUILTIN, OUTPUT);

}

void loop() {
  // Handle AP server client
  apServer.handleClient();

 
  if (connection_mode >=MQTT_MODE) {
    
    mqttClient.handleClient();
    command = mqttClient.getLastMessage(); // Check if a new MQTT message has been received
    mqttClient.setLastMessage("");   
  }


  if (command != "")  handleCommandJSON(command);
  
}


bool handleCommandJSON(const String& command) {
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