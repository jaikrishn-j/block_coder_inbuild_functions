void writeDigitalToDashboard(int signalLevel, const char* topic) {
  static int lastSignalLevel = -1;
  if (signalLevel != lastSignalLevel) {
    const char* payload = (signalLevel == HIGH) ? "1" : "0";
    if (mqttClient.connected()) {
      mqttClient.publish(topic, payload, true); // ← mqttClient, not client
      lastSignalLevel = signalLevel;
    }
  }
}