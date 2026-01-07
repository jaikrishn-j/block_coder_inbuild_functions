#include <DHT.h>

// On ESP8266, it's best to define the sensor type
#define DHTTYPE DHT11 // or DHT22

// We assume a global or static instance is needed if not already defined
DHT dht(tempSensor, DHTTYPE);

void senseTemperature(int tempSensor, int &tempValue) {
  // Ensure the sensor has been started
  static bool isStarted = false;
  if (!isStarted) {
    dht.begin();
    isStarted = true;
  }

  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();

  // Check if any reads failed and exit early (to prevent garbage data)
  if (isnan(t)) {
    // Optional: Set tempValue to a specific error code like -999
    return;
  }

  // Update the reference variable (converting float to int)
  tempValue = (int)t;
}