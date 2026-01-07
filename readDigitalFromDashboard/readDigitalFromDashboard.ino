void readDigitalFromDashboard(int &stateD, const char* topic, byte* payload, unsigned int length) {
  // 1. Convert payload to a temporary string for easier analysis
  char message[length + 1];
  memcpy(message, payload, length);
  message[length] = '\0';
  String msgStr = String(message);
  msgStr.toLowerCase(); // Standardize to lowercase for easier matching

  // 2. Check for JSON format {"state": ...}
  if (msgStr.startsWith("{")) {
    StaticJsonDocument<64> doc;
    DeserializationError error = deserializeJson(doc, message);
    if (!error) {
      // Handles both {"state": true} and {"state": 1}
      stateD = doc["state"] ? HIGH : LOW;
      return; // Exit early since we found the value
    }
  }

  // 3. Check for plain text formats: "1", "true", "on"
  if (msgStr == "1" || msgStr == "true" || msgStr == "on") {
    stateD = HIGH;
  } 
  // 4. Check for plain text formats: "0", "false", "off"
  else if (msgStr == "0" || msgStr == "false" || msgStr == "off") {
    stateD = LOW;
  }
}