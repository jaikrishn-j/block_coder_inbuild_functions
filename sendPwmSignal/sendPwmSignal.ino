void sendPwmSignal(int pwmPin, int dutyCycle) {
  // On ESP8266, the default PWM range is 0 to 1023.
  // If your 'dutyCycle' input is 0-255, you should map it:
  // int scaledValue = map(dutyCycle, 0, 255, 0, 1023);
  
  // Ensure the value is within the ESP8266 hardware limits
  int safeDutyCycle = constrain(dutyCycle, 0, 1023);

  // Write the PWM signal to the pin
  analogWrite(pwmPin, safeDutyCycle);
  
  // Note: All pins except D0 (GPIO16) support high-quality PWM.
  // GPIO16 supports PWM but via a different hardware timer, making it less smooth.
}