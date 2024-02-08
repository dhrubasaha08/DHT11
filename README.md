# DHT11 Arduino Library
![Static Badge](https://img.shields.io/badge/Author-Dhruba%20Saha-red?link=https%3A%2F%2Fgithub.com%2Fdhrubasaha08)
![GitHub Release](https://img.shields.io/github/v/release/dhrubasaha08/DHT11)
[![GitHub](https://img.shields.io/github/license/dhrubasaha08/DHT11)](LICENSE) 
[![GitHub contributors](https://img.shields.io/github/contributors/dhrubasaha08/DHT11)](https://github.com/dhrubasaha08/DHT11/graphs/contributors) 
![GitHub Downloads (all assets, all releases)](https://img.shields.io/github/downloads/dhrubasaha08/DHT11/total)

## Table of Contents

- [DHT11 Arduino Library](#dht11-arduino-library)
  - [Table of Contents](#table-of-contents)
  - [Introduction](#introduction)
  - [Updates](#updates)
    - [v2.1.0 Hotfix `Latest`](#v210-hotfix-latest)
    - [v2.0.0 Update](#v200-update)
  - [How It Works](#how-it-works)
    - [Internal Protocol Handling](#internal-protocol-handling)
  - [Features](#features)
  - [Installation](#installation)
    - [Arduino IDE Library Manager](#arduino-ide-library-manager)
    - [Installing Manually from GitHub](#installing-manually-from-github)
  - [Usage](#usage)
    - [Basic Usage](#basic-usage)
    - [New Methods](#new-methods)
    - [Wiring Details](#wiring-details)
  - [Examples](#examples)
  - [Error Handling](#error-handling)
  - [Troubleshooting](#troubleshooting)
  - [FAQ](#faq)
  - [Compatibility](#compatibility)
    - [Contribute by Testing](#contribute-by-testing)
  - [Contributing](#contributing)
  - [Code of Conduct](#code-of-conduct)
  - [License](#license)
  - [External References](#external-references)

## Introduction
This Arduino library is designed for the DHT11 temperature and humidity sensor. It simplifies the process of reading temperature and humidity data, making it easy to integrate the DHT11 sensor into your Arduino projects.

**Author:** [Dhruba Saha](https://github.com/dhrubasaha08)

**Version:** 2.1.0

**License:** [MIT](/LICENSE)

## Updates

### v2.1.0 Hotfix `Latest`
- Introduced the `readTemperatureHumidity(int &temperature, int &humidity)` method, allowing for efficient simultaneous reading of temperature and humidity, streamlining the data acquisition process.
- Refactored the internal data reading process, reducing code repetition and improving maintainability.
- Enhanced error handling: Now, specific error codes are returned from the `readTemperatureHumidity` method, making it consistent with the `readTemperature` and `readHumidity` methods.
- Documentation updated to reflect the new changes and provide clear guidance on using the new library version.

*Note: The updates in version 2.1.0 are backward compatible with the previous versions(v2.x.x), ensuring a smooth transition for existing projects.*

### v2.0.0 Update
- Changed the return type of `readTemperature()` and `readHumidity()` methods from `float` to `int`. This aligns with the DHT11 sensor's 1-degree resolution.
- Enhanced code documentation for easier maintenance and better readability.
- Added the `getErrorString` method to return human-readable error messages based on error codes.
- Major code refactoring for better maintainability and robustness.
- Introduced the [`CONTRIBUTING.md`](CONTRIBUTING.md) file to guide contributors on how to effectively contribute to the library.
- Added a [`CODE_OF_CONDUCT.md`](CODE_OF_CONDUCT.md) to establish community guidelines and expectations for behavior.
- Introduced the [`ReadPlot`](/examples/ReadPlot/ReadPlot.ino) example which uses the Arduino Serial Plotter to display temperature and humidity data. This example provides a visual representation of the sensor's readings, making it easier to monitor environmental conditions in real-time.
- Added ESP32/ESP8266 compatibility.

## How It Works

The DHT11 sensor uses a custom single-wire protocol for communication. The basic process for reading data involves:

1. Sending a start signal to the DHT11 sensor.
2. Reading a series of pulses from the sensor representing data bits.
3. Interpreting the received bits to extract temperature and humidity values.
4. Validating the data using a checksum.

The library handles these steps internally, providing the user with a simple interface for reading temperature and humidity.

### Internal Protocol Handling

The library initiates the data request to the DHT11 sensor and then reads a 40-bit data stream in response. The data stream is parsed to obtain accurate temperature and humidity readings. The process of reading data from the DHT11 involves multiple steps:

![](/assets/communication.png)
**Source & Credit :** [Mouser DHT11 Datasheet](https://www.mouser.com/datasheet/2/758/DHT11-Technical-Data-Sheet-Translated-Version-1143054.pdf)

1. **Initialization and Request**: 
    - The MCU (like an Arduino) sends a start signal by pulling the data line low for at least 18ms.
    - The MCU then pulls the line high for 20-40us to indicate that it's ready to receive a response.

2. **DHT11 Response**:
    - Upon detecting the start signal from the MCU, the DHT11 sends a response signal.
    - This response consists of a 80us low voltage level followed by an 80us high voltage level.

3. **Data Transmission**:
    - The DHT11 transmits its data in a series of pulses. Each bit of data is represented by a specific combination of high and low voltage durations.
    - A '0' is represented by 50us of low voltage followed by 26-28us of high voltage.
    - A '1' is represented by 50us of low voltage followed by 70us of high voltage.
    - The DHT11 sends 40 bits of data in total: 16 bits for humidity, 16 bits for temperature, and 8 bits for checksum.
    - The checksum is the last 8 bits of the sum of the first 32 bits. It's used to verify data integrity.

4. **Data Interpretation**:
    - After reading the 40 bits, the MCU processes the data to extract temperature and humidity values.
    - The bits are grouped to form the integral and decimal parts of the temperature and humidity readings, though the DHT11 provides only integer values.
  
5. **Completion**:
    - After data transmission, the DHT11 pulls the data line low for 50us, marking the end of the communication. The MCU then pulls the line high, putting the DHT11 in a low-power standby mode.

This library abstracts these complexities, allowing users to easily read temperature and humidity values with simple function calls. Behind the scenes, it manages the signaling, data reading, and interpretation based on the DHT11's protocol.


## Features

- **Easy to Use**: Easy to use interface for reading temperature and humidity from the DHT11 sensor.
- **No External Dependencies**: The library is standalone and doesn't require any external libraries.
- **Example Sketches**: The library package includes example Arduino sketches to get you started quickly.
- **Error Handling**: The library package includes Error handling mechanisms to ensure robustness.

## Installation

### Arduino IDE Library Manager
1. Open the Arduino IDE.
2. Go to `Sketch` > `Include Library` > `Manage Libraries...`.
3. In the Library Manager, enter "DHT11" into the search box.
4. Find the DHT11 library in the list and install it.

### Installing Manually from GitHub
1. Download the latest release of the library from this GitHub repository as a ZIP file.
2. Open the Arduino IDE.
3. Go to `Sketch` > `Include Library` > `Add .ZIP Library...`.
4. Navigate to the downloaded ZIP file and select it to install.

## Usage

### Basic Usage

- Include the `DHT11.h` header file.
- Create an instance of the DHT11 class, specifying the digital pin connected to the sensor's data pin.
- Use `readTemperature()` and `readHumidity()` methods to read the data.
- `getErrorString(int errorCode)`: Returns a human-readable error message based on the provided error code.

### New Methods

- `readTemperatureHumidity(int &temperature, int &humidity)`: This new method allows for simultaneous reading of temperature and humidity, reducing the complexity and time required for separate readings. It returns an `int` indicating the success or specific error encountered during the operation.


### Wiring Details

The DHT11 sensor has three or four pins, depending on the variant:

- **VCC**: Connect to 3.3V or 5V on your MCU (based on your sensor's specification).
- **Data**: Connect to a digital I/O pin on your MCU (not an analog pin). For the provided examples, we use digital pin 2 by default.
- **Ground (GND)**: Connect to the ground of your MCU.
- **NC (No Connect)**: Some variants have this pin. It is not used and can be left unconnected.

Remember to use a pull-up resistor (typically 10kΩ) between the VCC and Data pins for reliable communication.(Optional)

## Examples

All examples provided use Arduino UNO's digital pin 2 as the default connection to the DHT11 sensor's data pin. Modify this in the code if using a different pin.

- **[Read Humidity](examples/ReadHumidity/ReadHumidity.ino)**  
  This example demonstrates how to simply read the humidity value from the DHT11 sensor and display it on the Arduino Serial Monitor. It's a basic introduction to using the library to get humidity data.

- **[Read Temperature and Humidity](examples/ReadTempAndHumidity/ReadTempAndHumidity.ino)**  
  A more comprehensive example that shows how to read both temperature and humidity values from the DHT11 sensor. Results are displayed on the Arduino Serial Monitor, giving users a complete view of the environment.

- **[Read Temperature](examples/ReadTemperature/ReadTemperature.ino)**  
  Similar to the 'Read Humidity' example, but focused solely on reading and displaying the temperature value from the DHT11 sensor. It provides a straightforward way to monitor temperature using the library.

- **[Read Plot](examples/ReadPlot/ReadPlot.ino)**  
  A visually interactive example that uses the Arduino Serial Plotter to graphically display temperature and humidity data in real-time. This is perfect for those who want a visual representation and trend analysis of the sensor's readings.

## Error Handling

The library provides clear error handling mechanisms. When reading data:

- If there's a timeout while waiting for a response from the sensor, the methods `readTemperature()` and `readHumidity()` & return the value `DHT11::ERROR_TIMEOUT`. <!-- TODO update for int readTemperatureHumidity(int &temperature, int &humidity); -->
- If there's a checksum mismatch indicating data corruption, the methods return the value `DHT11::ERROR_CHECKSUM`.

For translating these error codes to human-readable strings, the library offers the `DHT11::getErrorString(int errorCode)` method.

## Troubleshooting

- **Sensor Not Responding or Constant Timeouts:**  
  - Ensure the sensor receives the proper voltage (3.3V or 5V).
  - Double-check the data pin connection to the Arduino board.
  - Restart the Arduino IDE after any changes.
  
- **Checksum Errors:**  
  - Ensure minimal distance between the sensor and the Arduino board.
  - Check the surrounding environment for electrical noise sources.

- **Inaccurate or Unstable Readings:**  
  - Give the sensor time to stabilize after powering on.
  - Position the sensor away from direct sources of temperature or humidity changes.

- **Library Not Found in Arduino IDE:**  
  - Confirm the library's correct installation.
  - Restart the Arduino IDE.

## FAQ

1. **Is this library designed for the DHT22 sensor as well?**  
   No. The library caters exclusively to the DHT11 sensor. The DHT22 uses a different data format, necessitating a separate library.

2. **What's the recommended frequency for sensor readings?**  
   It's best to allow at least 1 second between readings for accurate and stable results.

3. **I'm experiencing persistent timeout errors. What can I do?**  
   Ensure proper wiring, verify the sensor's power source, and check if the specified data pin in the Arduino code matches your hardware setup.

4. **Has this library been tested on platforms other than the Arduino IDE?**  
   While it's been primarily tested on the Arduino IDE and Arduino Uno R3 board, it might work on other platforms or boards. However, results may vary.

5. **Is the library compatible with third-party platforms?**  
   Although tailored for the Arduino IDE, the library might function on other platforms. Still, I don't guarantee compatibility or consistent outcomes on third-party platforms.

## Compatibility

The library has been tested and confirmed to work on the following boards:

- Arduino Uno R3 (ATmega328P - AVR architecture)
- NodeMCU ESP32S v1.1 **`ESP-WROOM-32`** (Tensilica Xtensa LX6 - xtensa architecture) `*`
- NodeMCU ESP8266 v1.0 **`ESP8266MOD`** (Tensilica Xtensa LX106 - xtensa architecture) `*`

Given the vast number of boards and architectures available, it's a challenge for a solo developer to test on all. Community contributions in terms of compatibility testing are highly encouraged.

### Contribute by Testing

If you've successfully used this library on a board not listed above, please consider contributing by letting me know. This will help the community to have a broader understanding of the library's compatibility.

1. Fork the [repository](https://github.com/dhrubasaha08/DHT11).
2. Update the README with the board you've tested.
3. Create a pull request with your changes.

Your contribution will be greatly appreciated, and it will benefit the entire Arduino community.

## Contributing

For guidelines on contributing to this project, please see the [`CONTRIBUTING.md`](CONTRIBUTING.md) file.

## Code of Conduct

To understand the community guidelines and expected behavior, please refer to the [`CODE_OF_CONDUCT.md`](CODE_OF_CONDUCT.md) file.

## License

This library is licensed under the `MIT` License. See the [`LICENSE`](LICENSE) file for more details.

## External References

- [`DHT11 Datasheet`](https://www.mouser.com/datasheet/2/758/DHT11-Technical-Data-Sheet-Translated-Version-1143054.pdf)
