void writeAnalogToDashboard(int intensity, const char* topic) {
  // 1. Remember the last value sent
  static int lastIntensity = -1;
  
  // 2. Only send if the change is significant (e.g., > 3 units)
  // This prevents noise or minor fluctuations from flooding the broker
  if (abs(intensity - lastIntensity) > 3) {
    
    // Convert the integer to a null-terminated string
    char payload[12];
    
    // Publish to the MQTT topic (using global 'client')
    if (client.connected()) {
      client.publish(topic, payload, true);  // ← uses 'client', not 'mqttClient'
      
      // 3. Update the last sent value
      lastIntensity = intensity;
    }
  }
}