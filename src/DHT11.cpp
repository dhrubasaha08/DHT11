#include "DHT11.h"

// Initializes the pin and sets it to output mode.
DHT11::DHT11(int pin)
{
  _pin = pin;
  pinMode(_pin, OUTPUT);
  digitalWrite(_pin, HIGH);
}

// Reads and returns the temperature from the sensor. Returns -1 if the checksum is incorrect.
float DHT11::readTemperature()
{
  delay(150);
  byte data[5] = {0, 0, 0, 0, 0};
  startSignal();

  if (digitalRead(_pin) == LOW)
  {
    delayMicroseconds(80);
    if (digitalRead(_pin) == HIGH)
    {
      delayMicroseconds(80);

      for (int i = 0; i < 5; i++)
      {
        data[i] = readByte();
      }

      if (data[4] == ((data[0] + data[1] + data[2] + data[3]) & 0xFF))
      {
        return data[2];
      }
    }
  }
  return -1;
}

// Reads and returns the humidity from the sensor. Returns -1 if the checksum is incorrect.
float DHT11::readHumidity()
{
  delay(150);
  byte data[5] = {0, 0, 0, 0, 0};
  startSignal();

  if (digitalRead(_pin) == LOW)
  {
    delayMicroseconds(80);
    if (digitalRead(_pin) == HIGH)
    {
      delayMicroseconds(80);

      for (int i = 0; i < 5; i++)
      {
        data[i] = readByte();
      }

      if (data[4] == ((data[0] + data[1] + data[2] + data[3]) & 0xFF))
      {
        return data[0];
      }
    }
  }
  return -1;
}

// Reads a byte of data from the sensor.
byte DHT11::readByte()
{
  byte value = 0;

  for (int i = 0; i < 8; i++)
  {
    while (digitalRead(_pin) == LOW)
      ;
    delayMicroseconds(30);
    if (digitalRead(_pin) == HIGH)
    {
      value |= (1 << (7 - i));
    }
    while (digitalRead(_pin) == HIGH)
      ;
  }
  return value;
}

// Sends the start signal to the sensor.
void DHT11::startSignal()
{
  pinMode(_pin, OUTPUT);
  digitalWrite(_pin, LOW);
  delay(18);
  digitalWrite(_pin, HIGH);
  delayMicroseconds(40);
  pinMode(_pin, INPUT);
}
