void writeAnalogToDashboard(int intensity, const char* topic) {
  // 1. Remember the last value sent
  static int lastIntensity = -1;
  
  // 2. Only send if the change is significant (e.g., > 3 units)
  // This prevents tiny electrical "noise" from spamming the broker
  if (abs(intensity - lastIntensity) > 3) {
    
    // Convert the integer to string for MQTT payload
    char payload[12];
    snprintf(payload, sizeof(payload), "%d", intensity);
    
    // Publish to the topic
    if (client.connected()) {
      client.publish(topic, payload, true);
      
      // 3. Update the memory
      lastIntensity = intensity;
    }
  }
}