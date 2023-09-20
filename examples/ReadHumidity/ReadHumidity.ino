/**
 * DHT11 Humidity Reader for Arduino
 * This sketch reads humidity data from the DHT11 sensor and prints the value to the serial port.
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
    // Attempt to read the humidity value from the DHT11 sensor.
    int humidity = dht11.readHumidity();

    // Check the result of the reading.
    // If there's no error, print the humidity value.
    // If there's an error, print the appropriate error message.
    if (humidity != DHT11::ERROR_CHECKSUM && humidity != DHT11::ERROR_TIMEOUT)
    {
        Serial.print("Humidity: ");
        Serial.print(humidity);
        Serial.println(" %");
    }
    else
    {
        Serial.println(DHT11::getErrorString(humidity));
    }

    // Wait for 1 seconds before the next reading.
    delay(1000);
}
