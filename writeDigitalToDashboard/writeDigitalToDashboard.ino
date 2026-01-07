void writeDigitalToDashboard(int signalLevel, const char* topic) {
  // Prepare the payload for the MQTT broker
  const char* payload = (signalLevel == HIGH) ? "1" : "0";

  // Publish the state to the dashboard topic
  if (client.connected()) {
    // Use retained = true so dashboard shows correct state after refresh
    client.publish(topic, payload, true);
  }
}