void readDigitalFromDashboard(int &stateD, const char* topic) {
  if (!client.connected()) return;

  // 1. Check if we are actually subscribed to this topic
  static std::map<String, bool> subbed;
  if (subbed.find(topic) == subbed.end()) {
    if (client.subscribe(topic)) {
      subbed[topic] = true;
      Serial.print("SUCCESS: Subscribed to "); Serial.println(topic);
    }
  }

  // 2. Fetch the latest value stored by the callback
  if (topicRegistry.count(topic)) {
    int newValue = topicRegistry[topic];
    
    // Debug print ONLY when it changes
    if (stateD != newValue) {
      Serial.printf("Variable Updated: %s is now %d\n", topic, newValue);
    }
    
    stateD = newValue;
  }
}