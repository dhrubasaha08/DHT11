/**
 * DHT11.cpp
 * Library for reading temperature and humidity from the DHT11 sensor.
 *
 * Author: Dhruba Saha
 * Version: 2.0.0
 * License: MIT
 * Modified: John Kennedy
 */

#include "DHT11.h"

/**
 * Constructor for the DHT11 class.
 * Initializes the pin to be used for communication and sets it to output mode.
 *
 * @param pin: Digital pin number on the Arduino board to which the DHT11 sensor is connected.
 */
DHT11::DHT11(int pin)
{
  _pin = pin;
  pinMode(_pin, OUTPUT);
  digitalWrite(_pin, HIGH);
  DHT11::readSensor();
}

/**
 * Reads and returns the temperature from the DHT11 sensor.
 *
 * @return: Temperature value in Celsius. 
 */
int DHT11::readTemperature()
{
  return DHT11::_temperature;
}

/**
 * Reads and returns the humidity from the DHT11 sensor.
 *
 * @return: Humidity value in percentage. 
 */
int DHT11::readHumidity()
{
  return DHT11::_humidity;
}

/**
 * Reads and saves the humidity and temperature from the DHT11 sensor.
 *
 * @return: Returns 0 if all OK.
 *          Returns DHT11::ERROR_TOOFREQUENT if poll frequency is too high
 *          Returns DHT11::ERROR_TIMEOUT if reading times out.
 *          Returns DHT11::ERROR_CHECKSUM if checksum validation fails.
 */
int DHT11::readSensor()
{
  if (millis() - DHT11::_pollTime > DHT11::_lastPollTime)
  {
    DHT11::_lastPollTime = millis();  
    delay(150);
    byte data[5] = {0, 0, 0, 0, 0};
    startSignal();
    unsigned long timeout_start = millis();

    while (digitalRead(_pin) == HIGH)
    {
      if (millis() - timeout_start > DHT11::TIMEOUT_DURATION)
      {
        return DHT11::ERROR_TIMEOUT;
      }
    }
  
    if (digitalRead(_pin) == LOW)
    {
      delayMicroseconds(80);
      if (digitalRead(_pin) == HIGH)
      {
        delayMicroseconds(80);
        for (int i = 0; i < 5; i++)
        {
          data[i] = readByte();
          if (data[i] == DHT11::ERROR_TIMEOUT)
          {
            return DHT11::ERROR_TIMEOUT;
          }
        }
        if (data[4] == ((data[0] + data[1] + data[2] + data[3]) & 0xFF))
        {
          DHT11::_temperature = data[2];
          DHT11::_humidity = data[0];
          return 0;
        }
      }
    }
    return DHT11::ERROR_CHECKSUM;
  } else {
    return DHT11::ERROR_TOOFREQUENT;
  }
}

/**
 * Reads a byte of data from the DHT11 sensor during the communication process.
 *
 * @return: A byte of data read from the sensor.
 */
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

/**
 * Sends a start signal to the DHT11 sensor to initiate a data read.
 * This involves setting the data pin low for a specific duration, then high,
 * and finally setting it to input mode to read the data.
 */
void DHT11::startSignal()
{
  pinMode(_pin, OUTPUT);
  digitalWrite(_pin, LOW);
  delay(18);
  digitalWrite(_pin, HIGH);
  delayMicroseconds(40);
  pinMode(_pin, INPUT);
}

/**
 * Returns a human-readable error message based on the provided error code.
 * This method facilitates easier debugging and user feedback by translating
 * numeric error codes into descriptive strings.
 *
 * @param errorCode The error code for which the description is required.
 * @return A descriptive string explaining the error.
 */
String DHT11::getErrorString(int errorCode)
{
  switch (errorCode)
  {
  case DHT11::ERROR_TIMEOUT:
    return "Error: Reading from DHT11 timed out.";
  case DHT11::ERROR_CHECKSUM:
    return "Error: Checksum mismatch while reading from DHT11.";
  default:
    return "Error: Unknown error code.";
  }
}
