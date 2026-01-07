void readAnalogFromDashboard(int &valueA, const char* topic) {
  // Build null-terminated string from payload
  if (lastTopic == String(topic)) {
    valueA = lastMsg.toInt(); 
    // You can add constrain(value, 0, 255) here if needed
  }
}