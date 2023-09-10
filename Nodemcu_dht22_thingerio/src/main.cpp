#include <Arduino.h>
#define THINGER_USE_FUNCTIONAL
#define THINGER_SERIAL_DEBUG
#define _DISABLE_TLS_
#include <ThingerSmartConfig.h>
#include "arduino_secrets.h"

// library for DHT22
#include <Adafruit_Sensor.h>
#include <DHT.h>
// #include <DHT_U.h>

#define DHTPIN D2      // Digital pin connected to the DHT sensor
#define DHTTYPE DHT22 // DHT 22 (AM2302)

// DHT_Unified dht(DHTPIN, DHTTYPE);
DHT dht(DHTPIN, DHTTYPE);

ThingerSmartConfig thing(USERNAME, DEVICE_ID, DEVICE_CREDENTIAL);

void setup()
{
  // open serial for debugging
  Serial.begin(115200);

  pinMode(LED_BUILTIN, OUTPUT);

  // digital pin control example (i.e. turning on/off a light, a relay, configuring a parameter, etc)
  thing["led"] << digitalPin(LED_BUILTIN);

  // resource output example (i.e. reading a sensor value)
  thing["millis"] >> outputValue(millis());

  dht.begin();
  thing["Measurements DHT22"] >> [](pson &out)
  {
    out["Temperature *C"] = dht.readTemperature();
    // out["Temperature *F"] = dht.temperature(true);
    out["Humidity"] = dht.readHumidity();
  };

  // more details at http://docs.thinger.io/arduino/
}

void loop()
{
  thing.handle();
}

//restart pc