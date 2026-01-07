void monitorLight(int ldrPin, int &lightLevel) {
  // Read the analog value from the LDR pin
  // Note: On ESP8266, only A0 (GPIO 17) supports analogRead
  int rawValue = analogRead(ldrPin);

  // Assign the reading to the reference variable
  lightLevel = rawValue;
  
  // Optional: If you need a percentage (0-100%), use:
  // lightLevel = map(rawValue, 0, 1023, 0, 100);
}