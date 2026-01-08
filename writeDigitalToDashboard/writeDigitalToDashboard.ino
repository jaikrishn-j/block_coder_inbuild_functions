void writeDigitalToDashboard(int signalLevel, const char* topic) {
  if (!client.connected()) return;

  // Only publish if the value has changed
  if (signalLevel != lastPublishedValues[topic]) {
    char msg[2];
    itoa(signalLevel, msg, 10);
    if (client.publish(topic, msg)) {
      lastPublishedValues[topic] = signalLevel;
    }
  }
}