/**
 * DHT11.h
 * Header file for the DHT11 library, providing functionalities to interface with
 * the DHT11 temperature and humidity sensor.
 *
 * Author: Dhruba Saha
 * Version: 2.0.0
 * License: MIT
 */

#ifndef DHT11_h
#define DHT11_h

#include "Arduino.h"

/**
 * DHT11 Class
 * Provides methods to read temperature and humidity data from the DHT11 sensor.
 */
class DHT11
{
public:
  /**
   * Constructor
   * Initializes the data pin to be used for communication with the DHT11 sensor.
   *
   * @param pin: Digital pin number on the Arduino board to which the DHT11 sensor is connected.
   */
  DHT11(int pin);

  /**
   * Reads and returns the humidity from the DHT11 sensor.
   *
   * @return: Humidity value in percentage. Returns DHT11_ERROR_TIMEOUT if reading times out.
   *          Returns DHT11_ERROR_CHECKSUM if checksum validation fails.
   */
  int readHumidity();

  /**
   * Reads and returns the temperature from the DHT11 sensor.
   *
   * @return: Temperature value in Celsius. Returns DHT11_ERROR_TIMEOUT if reading times out.
   *          Returns DHT11_ERROR_CHECKSUM if checksum validation fails.
   */
  int readTemperature();

  // Constants to represent error codes.
  static const int ERROR_CHECKSUM = 254;   // Error code indicating checksum mismatch.
  static const int ERROR_TIMEOUT = 253;    // Error code indicating a timeout occurred during reading.
  static const int TIMEOUT_DURATION = 300; // Duration (in milliseconds) to wait before timing out.

  /**
   * Returns a human-readable error message based on the provided error code.
   *
   * @param errorCode: The error code for which the message is required.
   * @return: A string describing the error.
   */
  static String getErrorString(int errorCode);

private:
  int _pin; // Pin number used for communication with the DHT11 sensor.

  /**
   * Reads a byte of data from the DHT11 sensor.
   *
   * @return: A byte of data read from the sensor.
   */
  byte readByte();

  /**
   * Sends a start signal to the DHT11 sensor to initiate a data read.
   * This involves setting the data pin low for a specific duration, then high,
   * and finally setting it to input mode to read the data.
   */
  void startSignal();
};

#endif
