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

// Converts Temperature to fahrenheit
float DHT11::convertToFahrenheit(float Temp)
{
  float fT = (Temp * 1.8) + 32;
  return fT;
}
// Converts Temperature to Celsius
float DHT11::convertToCelsius(float FTemp)
{
  float cT = (FTemp - 32) * 5/9;
  return cT;
}
// Computes Heat Index
float DHT11::computeHeatIndex(float Temp, float rH, bool isFahrenheit)
{
  if(!isFahrenheit){
    float T = convertToFahrenheit(Temp);
  }
  float T = Temp;
  float RH = rH;
  float Hi;
  Hi = 0.5*(T+61.0+((T-68.0)*1.2)+(RH*0.094));
  if(Hi > 79){
    Hi =  -42.379+2.04901523*T+10.14333127*RH-.22475541*T*RH-.00683783
          *pow(T, 2)-.05481717*pow(RH, 2)+.00122874*pow(T, 2)*RH+.00085282*T
          *pow(RH,2)-.00000199*pow(T, 2)*pow(RH,2);
  }
  if((RH <= 13.) && (T >= 80.) && (T <= 112.)){
    Hi -= ((13-RH)/4)*sqrt(17-abs(T-95)/17);
  } else if((RH >= 85.) && (T >= 80.) && (T <= 87.)){
    Hi += ((RH-85)/10)*((87-T)/5);
  } 

  return isFahrenheit ? Hi : convertToCelsius(Hi);
  
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
