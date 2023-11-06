#ifndef ESP_MQTT_CLIENT_H
#define ESP_MQTT_CLIENT_H

#include <PubSubClient.h>

#include "ConfigParams.h"

class ESPMQTTClient {
public:
  static ESPMQTTClient* instance;

  ESPMQTTClient();
  ESPMQTTClient(ConfigParams &config); // Constructor declaration
  void begin();
  void handleClient();
  void publish(const char* topic, const char* payload); // Declaration for publish
  void subscribe(const char* topic); // Declaration for subscribe
  String getLastMessage() const; // Corrected
  void setLastMessage(const String& message);

private:
  String lastMessage;
  ConfigParams &config;
  WiFiClient espClient;
  PubSubClient client;
  void reconnect();
  static void callback(char* topic, byte* payload, unsigned int length);
};

#endif // ESP_MQTT_CLIENT_H