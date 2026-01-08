void readDigitalFromDashboard(int &stateD, const char* topic) {
  if (!client.connected()) return;

  // Auto-subscribe if we haven't already
  static std::map<String, bool> subscribedTopics;
  if (!subscribedTopics[topic]) {
    client.subscribe(topic);
    subscribedTopics[topic] = true;
  }

  // Update the variable from the registry
  if (topicRegistry.count(topic)) {
    stateD = topicRegistry[topic];
  }
}