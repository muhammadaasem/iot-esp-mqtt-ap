# iot-esp-mqtt-ap: 

ESP based IoT codebase leverages MQTT for operation (sending / receiving data) and Access Point (AP) for OTA configuration.


## Introduction

The project utilizes the ESP8266 microcontroller to establish WiFi connections and communicate with MQTT brokers for IoT device management. It is designed for hobbyists and developers looking for a quick way to integrate IoT functionalities into their projects.


## Requirements
### Board
- ESP8266 boards

### Libraries
- PubSubClient by Nick O'Leary [doc](https://pubsubclient.knolleary.net/)

## Installation

To set up this project, follow these steps:

1. Clone the repository to your local machine:

```sh
git clone https://github.com/muhammadaasem/iot-esp-mqtt-ap.git
```

2. Open the project using the Arduino IDE or your preferred development environment.

3. Ensure you have all the necessary libraries installed. You can install libraries through the Arduino IDE Library Manager or by downloading them from the respective repositories and placing them in your libraries folder.

4. If required, update the `ConfigParams.h` file with your specific WiFi and MQTT broker details.

5. Flash the code to your ESP8266 module using the correct board settings in the Arduino IDE.

6. After uploading, the ESP8266 will start in Access Point mode. Connect to the ESP's network using the credentials set in `ConfigParams.h` to configure the device through the web interface.

7. Once configured, the device will attempt to connect to the specified WiFi network and MQTT broker, and you can begin sending commands and receiving messages.

## Usage

### Connecting to the Access Point

1. After flashing the ESP8266, it starts in Access Point (AP) mode. Use a Wi-Fi-enabled device to scan for new networks.
2. Connect to the ESP's Wi-Fi network using the SSID and password defined in `ConfigParams.h`.
3. Once connected, navigate to the ESP's IP address in a web browser. The default is usually `192.168.4.1`.
4. A web form should appear, allowing you to enter the Wi-Fi and MQTT broker details.

### Configuring Parameters

1. In the web form, fill in the fields for your home Wi-Fi SSID and password.
2. Provide the MQTT broker's domain or IP address, port, and topics for operation and configuration.
3. After entering the details, click the 'Save' button to store the configuration in the EEPROM.
4. Restart the ESP module to connect to your Wi-Fi and the MQTT broker with the new settings.

### Testing with MQTTX

1. Open [MQTTX](https://mqttx.app/) or any other MQTT client application.
2. Create a new connection, and enter your MQTT broker's details. (try with: broker.hivemq.com or broker.emqx.io)
3. Subscribe to the topics you've set in the ESP configuration to listen for messages. (try with: testingESP1234/data)
4. Publish messages to the operation topic to see the ESP respond or act on the commands.


```json
{
  "command": "setStatus",
  "switch1": "OFF",
  "switch2": "ON",
  "switch3": "OFF"
}
```

5. Observe the incoming messages from the ESP on the subscribed topics.



## License

[The license under which the project is made available. For example, MIT, GPL, etc.]

