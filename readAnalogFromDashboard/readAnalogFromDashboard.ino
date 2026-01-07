void readAnalogFromDashboard(int &valueA, const char* topic, byte* payload, unsigned int length) {
  // Build null-terminated string from payload
  char message[length + 1];
  memcpy(message, payload, length);
  message[length] = '\0';

  // Trim whitespace (optional but safer)
  String msgStr = String(message);
  msgStr.trim();

  // Convert to integer
  int val = msgStr.toInt();

  // Optional: clamp to valid analog range (e.g., 0–255 or 0–1023)
  // Here we assume 0–1023 (like ESP32 ADC or PWM range)
  if (val < 0) val = 0;
  if (val > 1023) val = 1023;

  valueA = val;
}