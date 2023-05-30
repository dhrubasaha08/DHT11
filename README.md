# DHT11

This is an Arduino library for the DHT11 temperature and humidity sensor. The library provides an easy-to-use interface for reading temperature and humidity data from the DHT11 sensor.

## How It Works

The DHT11 sensor provides temperature and humidity data over a single-wire interface. This library handles the low-level communication protocol with the sensor, allowing you to read the temperature and humidity data with simple function calls.

When you create an instance of the DHT11 class, you specify the pin that the sensor is connected to. Then, you can call the `readTemperature()` and `readHumidity()` methods to read the temperature and humidity data, respectively. These methods return the temperature in degrees Celsius and the relative humidity in percent, or `-1` if there was an error reading the data.

## Features

- **Easy to use**: Just create an instance of the DHT11 class and call the `readTemperature()` and `readHumidity()` methods.
- **No dependencies**: This library does not depend on any other libraries, so it's easy to install and use.
- **Examples included**: The library comes with example sketches that show you how to use it.

## Installation

To install the library, download the latest release from this repository and install it using the Arduino IDE's Library Manager.

## Usage

To use the library, include the `DHT11.h` header file in your sketch, create an instance of the DHT11 class, and call the `readTemperature()` and `readHumidity()` methods. See the example sketches included in the `examples` directory for more details.

## Contributing

Contributions to this library are welcome. Please open an issue if you find a bug or have a feature request, and feel free to submit pull requests if you've implemented a new feature or bug fix.

## License

This library is licensed under the MIT License. Please see the `LICENSE` file for more details.

## External References

- [DHT11 Datasheet](https://www.mouser.com/datasheet/2/758/DHT11-Technical-Data-Sheet-Translated-Version-1143054.pdf)
