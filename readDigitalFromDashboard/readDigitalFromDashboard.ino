void readDigitalFromDashboard(int &stateD, const char* topic) {
  if (lastTopic == String(topic)) {
    // Accept common ON/1/true variants
    String msg = lastMsg;
    stateD = (msg == "1" || msg == "on" || msg == "ON" || msg == "true") ? 1 : 0;
    // Clear lastTopic to avoid reprocessing (optional but safe)
    lastTopic = "";
  }
}