void readDigital(int pinD, int &stateD) {
  // Read the current digital level (HIGH or LOW) from the specified pin
  // On ESP8266, this returns 1 (HIGH) if voltage is ~3.3V and 0 (LOW) if ~0V
  int currentState = digitalRead(pinD);

  // Update the reference variable with the result
  stateD = currentState;
}