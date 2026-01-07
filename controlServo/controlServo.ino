#include <Servo.h>

// We create a global or static instance to manage the pin
Servo myServo;

void controlServo(int servoPin, int angle) {
  // Check if the servo is already attached to this pin to avoid re-attaching
  if (!myServo.attached()) {
    myServo.attach(servoPin);
  }

  // Ensure the angle is within the standard 0-180 degree range
  int constrainedAngle = constrain(angle, 0, 180);

  // Write the angle to the servo
  myServo.write(constrainedAngle);
  
  // Note: On ESP8266, the Servo library uses Software PWM, 
  // which can sometimes twitch if the Wi-Fi stack is very busy.
}