
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

/*
int CONFIG_PIN=5; // The pin that boots the device in AP mode for configuration 
int GPIO_PIN[]={4,12,13, 14};
*/
int GPIO_PIN[]={D3, D6, D7, D5}, CONFIG_PIN=D1;
/**************
GPIO0 -> D3 
GPIO2 -> D4 
GPIO4 -> D2   **
GPIO5 -> D1   *
GPIO12 -> D6  *
GPIO13 -> D7  *
GPIO14 -> D5  *
GPIO15 -> D8
GPIO16 -> D0
***************/

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


  pinMode(CONFIG_PIN, INPUT_PULLUP); 

  // Check the GPIO pin status
  if (digitalRead(CONFIG_PIN) == LOW) {
    // If the pin is LOW, set to AP_MODE
    connection_mode = AP_MODE;
    Serial.println("Starting in AP_MODE due to CONFIG_PIN being LOW.");
  } else {
    // If the pin is HIGH, set to MQTT_MODE
    connection_mode = MQTT_MODE;
    Serial.println("Starting in MQTT_MODE.");
  }

  // Initialize EEPROM and load the configuration
  eepromManager.begin();
  config = eepromManager.getConfig();// New device will show blank values for config parameters

  if (connection_mode >=AP_MODE){
    apServer.begin(); // Initialize the Access Point
  }
  
  if (connection_mode >=MQTT_MODE){
    mqttClient.begin(); 
  }


  // MY CODE for setup
    pinMode(LED_BUILTIN, OUTPUT);
    
    for (int i = 0; i < sizeof(GPIO_PIN) / sizeof(GPIO_PIN[0]); ++i) {
      pinMode(GPIO_PIN[i], OUTPUT);
    }

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

  if (strcmp(commandStr, "setStatus") == 0) {
    // Process setStatus command by setting GPIOs according to the JSON fields
    digitalWrite(GPIO_PIN[0], doc["switch1"] == "ON" ? HIGH : LOW);
    digitalWrite(GPIO_PIN[1], doc["switch2"] == "ON" ? HIGH : LOW);
    digitalWrite(GPIO_PIN[2], doc["switch3"] == "ON" ? HIGH : LOW);
    digitalWrite(GPIO_PIN[3], doc["switch4"] == "ON" ? HIGH : LOW);
    Serial.println("Status set according to command");
  } else if (strcmp(commandStr, "getStatus") == 0) {
    // Process getStatus command by publishing the JSON to topic_config
    //mqttClient.publish(topic_config, command); // Ensure mqttClient and topic_config are accessible
    Serial.println("Status published to topic_config");
  } else {
    Serial.print("Unknown command: ");
    Serial.println(commandStr);
  }

  // Add more else if blocks for additional commands

  return true;
}
