#include <ESP8266WiFi.h>
#include "ESP_MQTT_client.h"
#include "esp_eeprom.h"

// Constructor taking a reference to the config object
ESPMQTTClient::ESPMQTTClient(ConfigParams &config) : config(config), client(espClient) {
}

void ESPMQTTClient::begin() {
  WiFi.begin(config.ssid, config.password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi SSID: ");
  Serial.println(WiFi.SSID());

  client.setServer(config.mqtt_server, config.mqtt_port);
  client.setCallback([this](char* topic, byte* payload, unsigned int length) { this->callback(topic, payload, length); });
  reconnect();  // Try to connect upon starting
}

void ESPMQTTClient::handleClient() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}

void ESPMQTTClient::reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect with a unique client ID
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      client.publish(config.topic_operation, "hello world");
      // ... and resubscribe
      client.subscribe(config.topic_operation);
      client.subscribe(config.topic_config);

      // Display MQTT connection details
      Serial.print("Connected to MQTT Broker: ");
      Serial.println(config.mqtt_server);
      Serial.print("MQTT Port: ");
      Serial.println(config.mqtt_port);
      Serial.print("Subscribed to topics: ");
      Serial.print(config.topic_operation);
      Serial.print(", ");
      Serial.println(config.topic_config);
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}


void ESPMQTTClient::publish(const char* topic, const char* payload) {
  client.publish(topic, payload);
}

void ESPMQTTClient::subscribe(const char* topic) {
  client.subscribe(topic);
}

void ESPMQTTClient::callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived on topic: ");
  Serial.println(topic);

  Serial.print("Payload: ");
  for (unsigned int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();

  // Handle the message as needed
}
