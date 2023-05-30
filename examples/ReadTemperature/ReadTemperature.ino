#include <DHT11.h>

// Create an instance of the DHT11 class and set the digital I/O pin.
DHT11 dht11(2);

void setup()
{
    // Initialize serial communication at 115200 baud.
    Serial.begin(115200);
}

void loop()
{
    // Read the temperature from the sensor.
    float temperature = dht11.readTemperature();

    // If the temperature reading was successful, print it to the serial monitor.
    if (temperature != -1)
    {
        Serial.print("Temperature: ");
        Serial.print(temperature);
        Serial.println(" C");
    }
    else
    {
        // If the temperature reading failed, print an error message.
        Serial.println("Error reading temperature");
    }

    // Wait for 2 seconds before the next reading.
    delay(2000);
}
