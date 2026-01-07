void readDigitalFromDashboard(int &stateD, const char* topic) {
  client.subscribe(topic);
  if (lastTopic == String(topic)) {
    stateD = (lastMsg == "1" || lastMsg == "ON") ? 1 : 0;
  }
}