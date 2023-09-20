/**
 * DHT11 Sensor Reader for Arduino
 * This sketch reads temperature and humidity data from the DHT11 sensor and prints the values to the serial port.
 * It also handles potential error states that might occur during reading.
 *
 * Author: Dhruba Saha
 * Version: 2.0.0
 * License: MIT
 */

// Include the DHT11 library for interfacing with the sensor.
#include <DHT11.h>

// Create an instance of the DHT11 class.
// - For Arduino: Connect the sensor to Digital I/O Pin 2.
// - For ESP32: Connect the sensor to pin GPIO2 or P2.
// - For ESP8266: Connect the sensor to GPIO2 or D4.
DHT11 dht11(2);

void setup()
{
    // Initialize serial communication to allow debugging and data readout.
    // Using a baud rate of 9600 bps.
    Serial.begin(9600);
}

void loop()
{
    // Attempt to read the temperature and humidity values from the DHT11 sensor.
    int temperature = dht11.readTemperature();

    // If using ESP32 or ESP8266 (xtensa architecture), uncomment the delay below.
    // This ensures stable readings when calling methods consecutively.
    // delay(50);

    int humidity = dht11.readHumidity();

    // Check the results of the readings.
    // If there are no errors, print the temperature and humidity values.
    // If there are errors, print the appropriate error messages.
    if (temperature != DHT11::ERROR_CHECKSUM && temperature != DHT11::ERROR_TIMEOUT &&
        humidity != DHT11::ERROR_CHECKSUM && humidity != DHT11::ERROR_TIMEOUT)
    {
        Serial.print("Temperature: ");
        Serial.print(temperature);
        Serial.println(" °C");

        Serial.print("Humidity: ");
        Serial.print(humidity);
        Serial.println(" %");
    }
    else
    {
        if (temperature == DHT11::ERROR_TIMEOUT || temperature == DHT11::ERROR_CHECKSUM)
        {
            Serial.print("Temperature Reading Error: ");
            Serial.println(DHT11::getErrorString(temperature));
        }
        if (humidity == DHT11::ERROR_TIMEOUT || humidity == DHT11::ERROR_CHECKSUM)
        {
            Serial.print("Humidity Reading Error: ");
            Serial.println(DHT11::getErrorString(humidity));
        }
    }

    // Wait for 1 seconds before the next reading.
    delay(1000);
}
