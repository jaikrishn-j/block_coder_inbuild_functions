void readAnalogFromDashboard(int &valueA, const char* topic) {
  // Convert the integer value to a string/char array for MQTT transmission
  char payload[10];
  itoa(valueA, payload, 10); // Converts int to base-10 string

  // Check if the client is connected before publishing
  if (client.connected()) {
    // Publish the value to the specified topic
    // The 'true' parameter makes it a retained message (optional)
    client.publish(topic, payload);
  }
}