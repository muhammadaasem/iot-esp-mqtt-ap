
// esp_eeprom.h
#ifndef ESP_EEPROM_H
#define ESP_EEPROM_H

#include <EEPROM.h>
#include "ConfigParams.h"
// Make sure to define the size of the EEPROM space used for configuration
#define EEPROM_SIZE sizeof(ConfigParams)

class ESPEEPROMManager {
public:
  ESPEEPROMManager();
  ~ESPEEPROMManager();
  void begin();
  ConfigParams getConfig();
  void saveConfig(const ConfigParams &config);
  void loadConfig(ConfigParams &config);
};

#endif // ESP_EEPROM_H
