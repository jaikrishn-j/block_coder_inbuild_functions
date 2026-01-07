void triggerRelay(int relayPin, int activate) {
  // Logic for Active-Low Relay Modules (Most common for ESP8266)
  if (activate == HIGH) {
    digitalWrite(relayPin, LOW);  // Pulling LOW completes the circuit for the relay coil
  } else {
    digitalWrite(relayPin, HIGH); // Pulling HIGH turns the relay off
  }

  /* NOTE: If your relay is Active-High, use this instead:
  digitalWrite(relayPin, activate);
  */
}