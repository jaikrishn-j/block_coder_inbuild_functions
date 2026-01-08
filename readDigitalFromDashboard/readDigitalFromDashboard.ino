void readDigitalFromDashboard(int &stateD, const char* topic) {
  // Nur den Wert setzen, wenn eine neue Nachricht für dieses Topic da ist
  if (lastTopic == String(topic)) {
    stateD = (lastMsg == "1" || lastMsg == "ON") ? 1 : 0;
  }
}