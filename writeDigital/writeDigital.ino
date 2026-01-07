void writeDigital(int targetPin, int signalLevel) {
  // Directly set the pin state to HIGH (1) or LOW (0)
  // On ESP8266, HIGH outputs 3.3V
  digitalWrite(targetPin, signalLevel);
}