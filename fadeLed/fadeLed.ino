void fadeLed(int ledPin, int brightness) {
  // Constrain the brightness to the ESP8266 default PWM range (0 - 1023)
  // If your input is 0-255, you can use: int val = map(brightness, 0, 255, 0, 1023);
  int targetBrightness = constrain(brightness, 0, 1023);

  // Write the PWM signal to the pin
  analogWrite(ledPin, targetBrightness);
  
  // Note: On ESP8266, analogWrite works on almost all pins (GPIO 0-16),
  // but the frequency is 1kHz by default.
}