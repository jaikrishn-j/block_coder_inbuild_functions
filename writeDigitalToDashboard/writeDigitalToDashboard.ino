void writeDigitalToDashboard(int targetPin, int signalLevel, const char* topic) {
  // 1. Physically set the pin on the ESP8266
  digitalWrite(targetPin, signalLevel);

  // 2. Prepare the payload for the MQTT broker
  // We send "1" for HIGH and "0" for LOW for maximum dashboard compatibility
  const char* payload = (signalLevel == HIGH) ? "1" : "0";

  // 3. Publish the state to the dashboard topic
  if (client.connected()) {
    // We use 'retained = true' so the dashboard always shows the 
    // correct state even if the UI is refreshed or reopened.
    client.publish(topic, payload, true);
  }
}