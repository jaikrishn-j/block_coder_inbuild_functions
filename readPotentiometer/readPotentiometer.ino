void readPotentiometer(int potPin, int &potValue) {
  // Read the analog signal from the potentiometer
  // The ESP8266 ADC returns a value from 0 to 1023
  int rawRead = analogRead(potPin);

  // Update the reference variable with the current reading
  potValue = rawRead;
}