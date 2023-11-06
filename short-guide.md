# PINS, Boards, Tags, and Details

| GPIO # | ESP-01 | ESP-12E NODEMCU | WEMOS D1 MINI | Best for Input | Best for Output | State at Boot | Description |
|--------|--------|-----------------|---------------|----------------|-----------------|---------------|-------------|
| GPIO0  | -      | D3              | D3            | Yes            | Yes             | LOW           | Must be HIGH at boot to run the program; LOW to enter flashing mode |
| GPIO1  | TX     | TX              | TX            | No             | Yes             | HIGH          | Used for TX during boot; not recommended for other uses |
| GPIO2  | -      | D4              | D4            | Yes            | Yes (LED)       | HIGH          | Boot fails if pulled LOW; Often connected to onboard LED |
| GPIO3  | RX     | RX              | RX            | Yes            | No              | HIGH          | Used for RX during boot; can be used as a regular GPIO afterwards |
| GPIO4  | -      | D2              | D2            | Yes            | Yes             | HIGH          | General purpose IO, often used for I2C SDA |
| GPIO5  | -      | D1              | D1            | Yes            | Yes             | HIGH          | General purpose IO, often used for I2C SCL |
| GPIO6  | -      | -               | -             | No             | No              | -             | Connected to the flash memory; not recommended for use |
| GPIO7  | -      | -               | -             | No             | No              | -             | Connected to the flash memory; not recommended for use |
| GPIO8  | -      | -               | -             | No             | No              | -             | Connected to the flash memory; not recommended for use |
| GPIO9  | -      | SD2             | -             | No             | No              | -             | Connected to the flash memory; not recommended for use |
| GPIO10 | -      | SD3             | -             | No             | No              | -             | Connected to the flash memory; not recommended for use |
| GPIO11 | -      | -               | -             | No             | No              | -             | Connected to the flash memory; not recommended for use |
| GPIO12 | -      | D6              | D6            | Yes            | Yes             | HIGH          | General purpose IO |
| GPIO13 | -      | D7              | D7            | Yes            | Yes             | HIGH          | General purpose IO; Often used for SPI MISO |
| GPIO14 | -      | D5              | D5            | Yes            | Yes             | HIGH          | General purpose IO; Often used for SPI Clock |
| GPIO15 | -      | D8              | D8            | Yes            | Yes             | LOW           | Boot fails if pulled HIGH; Often used for SPI SS; Has built-in pull-down |
| GPIO16 | -      | D0              | D0            | Yes            | Yes             | -             | Can cause boot issues if connected to RST; used for deep sleep wake-up |



## Further Details:

- **GPIO 0**: Used to determine the boot mode. If it's connected to GND (LOW) when the ESP8266 powers up, it will enter flashing mode where new firmware can be uploaded. For regular operation, it should be HIGH on boot. After boot, it can be used as a regular input or output pin.

- **GPIO 1 (TX) & GPIO 3 (RX)**: These pins are used for serial communication during boot and program uploading. After boot, they can be repurposed as general I/O, but you should be careful as they will output boot messages at startup and during sleep wake-up, which can interfere with attached devices.

- **GPIO 2**: In some ESP8266 modules (like NodeMCU and Wemos D1 Mini), this pin is tied to an onboard LED and is active HIGH. It must be HIGH on boot, or the ESP will not start from the internal flash.

- **GPIO 15**: This pin has a built-in pull-down resistor. It must be pulled LOW during boot for the ESP to boot from the internal flash memory. It's often used for SPI communications (Chip Select/SS).

- **GPIO 16**: This pin is unique as it can be used to wake up the ESP8266 from deep sleep mode. However, if it's connected to the reset pin, it can interfere with normal booting.

Each GPIO pin may have specific electrical characteristics and limitations that make it more suitable for certain applications. For most general I/O purposes, GPIO 4, 5, 12, 13, and 14 are typically the best choices.
