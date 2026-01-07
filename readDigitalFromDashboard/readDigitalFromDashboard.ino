void readDigitalFromDashboard(int &stateD, const char* topic, byte* payload, unsigned int length) {
  char message[length + 1];
  memcpy(message, payload, length);
  message[length] = '\0';
  String msgStr = String(message);
  msgStr.toLowerCase();

  if (msgStr.startsWith("{")) {
    StaticJsonDocument<64> doc;
    DeserializationError error = deserializeJson(doc, message);
    if (!error) {
      stateD = doc["state"] ? HIGH : LOW;
      return;
    }
  }

  if (msgStr == "1" || msgStr == "true" || msgStr == "on") {
    stateD = HIGH;
  } 
  else if (msgStr == "0" || msgStr == "false" || msgStr == "off") {
    stateD = LOW;
  }
}