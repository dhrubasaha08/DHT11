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
    // Read the humidity from the sensor.
    float humidity = dht11.readHumidity();

    // If the humidity reading was successful, print it to the serial monitor.
    if (humidity != -1)
    {
        Serial.print("Humidity: ");
        Serial.print(humidity);
        Serial.println(" %");
    }
    else
    {
        // If the humidity reading failed, print an error message.
        Serial.println("Error reading humidity");
    }

    // Wait for 2 seconds before the next reading.
    delay(2000);
}
