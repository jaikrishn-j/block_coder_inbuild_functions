void blinkLed(int ledPin, int onOff) {
  // Use digitalWrite to set the pin state based on the input parameter
  // Note: On many ESP8266 boards, LED_BUILTIN is Active-Low
  if (onOff == HIGH) {
    digitalWrite(ledPin, HIGH); 
  } else {
    digitalWrite(ledPin, LOW);
  }
}