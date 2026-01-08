void writeDigitalToDashboard(int signalLevel, const char* topic) {
  // 1. Create a variable that "remembers" the last signal level
  static int lastSignalLevel = -1; 

  // 2. ONLY proceed if the current signal is different from the last one
  if (signalLevel != lastSignalLevel) {
    
    // Prepare the payload for the MQTT broker
    const char* payload = (signalLevel == HIGH) ? "1" : "0";

    // Publish the state to the dashboard topic
    if (client.connected()) {
      client.publish(topic, payload, true);
      
      // 3. Update the "last signal" so we don't send it again until it changes
      lastSignalLevel = signalLevel;
    }
  }
}