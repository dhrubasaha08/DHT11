#ifndef DHT11_h
#define DHT11_h

#include "Arduino.h"

// DHT11 class for reading temperature and humidity data from a DHT11 sensor.
class DHT11
{
public:
  // Takes the pin number as an argument.
  DHT11(int pin);

  // Reads and returns the humidity from the sensor. Returns -1 if the checksum is incorrect.
  float readHumidity();

  // Reads and returns the temperature from the sensor. Returns -1 if the checksum is incorrect.
  float readTemperature();

private:
  int _pin;

  // Reads a byte of data from the sensor.
  byte readByte();

  // Sends the start signal to the sensor.
  void startSignal();
};

#endif