
//esp_eeprom.cpp

#include "esp_eeprom.h"

// Constructor for ESPEEPROMManager
ESPEEPROMManager::ESPEEPROMManager() {
  // Initialization is done in the begin method
}

void ESPEEPROMManager::begin() {
  EEPROM.begin(EEPROM_SIZE);
}

ConfigParams ESPEEPROMManager::getConfig() {
  ConfigParams config;
  EEPROM.get(0, config);
  return config;
}

void ESPEEPROMManager::saveConfig(const ConfigParams &config) {
  EEPROM.put(0, config);
  EEPROM.commit();
}

void ESPEEPROMManager::loadConfig(ConfigParams &config) {
  EEPROM.get(0, config);
}

// Destructor for ESPEEPROMManager
ESPEEPROMManager::~ESPEEPROMManager() {
  EEPROM.end();
}

