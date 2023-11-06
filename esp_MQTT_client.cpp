
//esp_MQTT_client.cpp
#include <ESP8266WiFi.h>
#include "ESP_MQTT_client.h"
#include "esp_eeprom.h"

// Initialize the static instance pointer to nullptr
ESPMQTTClient* ESPMQTTClient::instance = nullptr;

// Constructor taking a reference to the config object
ESPMQTTClient::ESPMQTTClient(ConfigParams &config) : config(config), client(espClient) {
    ESPMQTTClient::instance = this; // Set the static instance pointer to this object
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

    // Set the MQTT server and the callback function
    client.setServer(config.mqtt_server, config.mqtt_port);
    client.setCallback(ESPMQTTClient::callback);
    reconnect(); // Attempt to connect to MQTT upon starting
}

void ESPMQTTClient::handleClient() {
    if (!client.connected()) {
        reconnect(); // Attempt to reconnect if not connected
    }
    client.loop(); // This should be called regularly to allow the client to process incoming messages and maintain its connection to the server
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
    client.publish(topic, payload); // Publish the payload to the given topic
}

void ESPMQTTClient::subscribe(const char* topic) {
    client.subscribe(topic); // Subscribe to the given topic
}

String ESPMQTTClient::getLastMessage() const {
    return lastMessage; // Return the last received message
}

void ESPMQTTClient::setLastMessage(const String& message) {
    lastMessage = message; // Set the last received message
}

// Static callback wrapper
void ESPMQTTClient::callback(char* topic, byte* payload, unsigned int length) {
    // Convert payload to a String
    String message;
    for (unsigned int i = 0; i < length; i++) {
        message += (char)payload[i];
    }

    // Print the message to the Serial monitor
    Serial.print("Message arrived on topic: ");
    Serial.println(topic);
    //Serial.print("Payload: ");
    //Serial.println(message);

    // Store the message if the instance is not null
    if (ESPMQTTClient::instance != nullptr) {
        ESPMQTTClient::instance->setLastMessage(message);
    }
}