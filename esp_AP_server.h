#ifndef ESP_AP_SERVER_H
#define ESP_AP_SERVER_H

#include <ESP8266WebServer.h>
#include "ConfigParams.h"
#include "esp_eeprom.h"

class ESPAPServer {
public:
  ESPAPServer(); // Constructor to initialize variables if needed
  void begin();
  void handleClient();

private:
ConfigParams config;
  ESP8266WebServer* server;
  void handleRoot();
  void handleSave();
  void handleReload();
};

#endif // ESP_AP_SERVER_H
