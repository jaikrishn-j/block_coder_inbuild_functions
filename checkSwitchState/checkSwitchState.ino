void checkSwitchState(int switchPin, int &switchStatus) {
  // Read the current physical state of the pin
  int currentState = digitalRead(switchPin);

  // Update the reference variable with the result
  // switchStatus will now reflect the state outside of this function
  switchStatus = currentState;
}