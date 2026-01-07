void writeAnalog(int targetPin, int intensity) {
  // On ESP8266, the default analogWrite range is 0 to 1023 (10-bit).
  // We constrain the value to ensure it stays within hardware limits.
  int safeIntensity = constrain(intensity, 0, 1023);

  // Apply the PWM signal to the pin
  analogWrite(targetPin, safeIntensity);
  
  // Note: All GPIOs (0-16) support analogWrite, but GPIO16 (D0) 
  // uses a different timer and might behave slightly differently.
}