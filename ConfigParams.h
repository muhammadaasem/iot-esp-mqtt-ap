// config_params.h
#ifndef CONFIG_PARAMS_H
#define CONFIG_PARAMS_H

struct ConfigParams {
  char ssid[15];
  char password[15];
  char mqtt_server[25];
  int mqtt_port;
  char topic_operation[50];
  char topic_config[50]; // You missed this line in your structure, it must be there as it's used elsewhere.
  int relayPins[4];
};

#endif // CONFIG
