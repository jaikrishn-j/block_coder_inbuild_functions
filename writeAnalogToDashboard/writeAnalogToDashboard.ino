void writeAnalogToDashboard(int intensity, const char* topic) {
  // Convert the integer to string for MQTT payload
  char payload[12];
  snprintf(payload, sizeof(payload), "%d", intensity);
  
  // Publish to the topic
  if (client.connected()) {
    client.publish(topic, payload, true);
  }
}