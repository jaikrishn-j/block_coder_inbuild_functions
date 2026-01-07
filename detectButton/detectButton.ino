void detectButton(int buttonPin, int &pressed) {
  // Read the current state of the button
  // Using ! (NOT) because LOW = Pressed in a Pull-up configuration
  int currentState = digitalRead(buttonPin);

  // Logic for Active-Low (Low = Pressed)
  if (currentState == LOW) {
    // Optional: add a tiny delay to debounce
    delay(50); 
    
    // Double check it's still pressed before confirming
    if (digitalRead(buttonPin) == LOW) {
      pressed = 1; // Mark as pressed
    }
  } else {
    pressed = 0; // Mark as not pressed
  }
}