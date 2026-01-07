void writeAnalogToDashboard(int targetPin, int intensity, const char* topic) {
  // 1. First, we apply the intensity to the physical pin on the ESP8266
  // Range is typically 0-1023
  analogWrite(targetPin, constrain(intensity, 0, 1023));

  // 2. Prepare the data for the Dashboard
  // Convert the integer to a character array (string)
  char payload[10];
  itoa(intensity, payload, 10); 

  // 3. Publish to the MQTT broker
  if (client.connected()) {
    // We use the 'retained' flag (true) so the dashboard shows 
    // the last known value even if it refreshes.
    client.publish(topic, payload, true);
  }
}