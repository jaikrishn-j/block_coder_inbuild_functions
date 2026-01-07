void readAnalog(int pinA, int &valueA) {
  // Read the analog value from the specified pin
  // On ESP8266, pinA should always be A0 (GPIO 17)
  int rawValue = analogRead(pinA);

  // Store the 10-bit result (0 to 1023) in the reference variable
  valueA = rawValue;
}