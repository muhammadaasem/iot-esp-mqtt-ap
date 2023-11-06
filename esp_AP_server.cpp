
// esp_AP_server.cpp
#include "ConfigParams.h"
#include "esp_AP_server.h"
#include "esp_eeprom.h"

extern ESPEEPROMManager eepromManager; // Assuming this is declared somewhere to access EEPROM functions
ESPAPServer::ESPAPServer() {
  // Constructor implementation
  // Possibly initialize the server member variable here
}

void ESPAPServer::begin() {
  // Initialize the server on port 80
  server =new ESP8266WebServer(80);

  // Start the AP with the SSID and password provided
  WiFi.mode(WIFI_AP);
  WiFi.softAP(config.ssid, config.password);

  // Print the IP address
  Serial.print("AP IP address: ");
  Serial.println(WiFi.softAPIP());

  // Define the HTTP endpoints
  server->on("/", HTTP_GET, std::bind(&ESPAPServer::handleRoot, this));
  server->on("/save", HTTP_POST, std::bind(&ESPAPServer::handleSave, this));
  server->on("/reload", HTTP_GET, std::bind(&ESPAPServer::handleReload, this));

  // Start the server
  server->begin();
}

void ESPAPServer::handleClient() {
  // Handle client requests
  server->handleClient();
}

void ESPAPServer::handleRoot() {
  // Serve the HTML page with the configuration form
  String html = "<html><head><title>ESP Config</title></head><body>"
                "<h1>Device Configuration</h1>"
                "<form action=\"/save\" method=\"post\">"
                "SSID: <input type=\"text\" name=\"ssid\" value=\"" + String(config.ssid) + "\"><br>"
                "Password: <input type=\"password\" name=\"password\" value=\"" + String(config.password) + "\"><br>"
                "MQTT Server: <input type=\"text\" name=\"mqtt_server\" value=\"" + String(config.mqtt_server) + "\"><br>"
                "MQTT Port: <input type=\"number\" name=\"mqtt_port\" value=\"" + String(config.mqtt_port) + "\"><br>"
                "Operation Topic: <input type=\"text\" name=\"topic_operation\" value=\"" + String(config.topic_operation) + "\"><br>"
                "Config Topic: <input type=\"text\" name=\"topic_config\" value=\"" + String(config.topic_config) + "\"><br>"
                "<input type=\"submit\" value=\"Save\">"
                "</form></body></html>";
    html += "<form action=\"/reload\" method=\"get\">"
          "<input type=\"submit\" value=\"Reload\">"
          "</form>";

  server->send(200, "text/html", html);
}

void ESPAPServer::handleReload() {
  // Load the configuration from EEPROM
  config = eepromManager.getConfig();

  // Call handleRoot to serve the form with loaded values
  handleRoot();
}

void ESPAPServer::handleSave() {
  // Check if all parameters are present
  if (server->hasArg("ssid") && server->hasArg("password") && server->hasArg("mqtt_server") && server->hasArg("mqtt_port") && server->hasArg("topic_operation") && server->hasArg("topic_config")) {
    // Update the configuration parameters
    server->arg("ssid").toCharArray(config.ssid, sizeof(config.ssid));
    server->arg("password").toCharArray(config.password, sizeof(config.password));
    server->arg("mqtt_server").toCharArray(config.mqtt_server, sizeof(config.mqtt_server));
    config.mqtt_port = server->arg("mqtt_port").toInt();
    server->arg("topic_operation").toCharArray(config.topic_operation, sizeof(config.topic_operation));
    server->arg("topic_config").toCharArray(config.topic_config, sizeof(config.topic_config));

    // Save the updated configuration to EEPROM
    eepromManager.saveConfig(config);

    // Respond with a success message
    server->send(200, "text/html", "<html><body>Configuration saved. Restart the device to apply the changes.</body></html>");
  } else {
    // Respond with an error message
    server->send(400, "text/html", "<html><body>Missing configuration parameters.</body></html>");
  }
}
