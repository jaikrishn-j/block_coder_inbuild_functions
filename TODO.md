In the Front end fix the code for having & for output values

Fix the on the github library code.
2. The MQTT "Flooding" Error (Critical)

Error Explanation: Your loop() runs thousands of times per second. Because there is no "if" statement checking if the pin value changed, your ESP is trying to send a message to the broker 1,000+ times every second.

Consequence: The HiveMQ public broker will see this as a Spam/DoS attack and automatically ban your IP address or disconnect your device within seconds.

Suggestion: You must implement a "State Change Detection." You should only call the write function if the current value is different from the last value read.

Generate random generated client id for client.connect()




void readDigitalFromDashboard(int &stateD, const char* topic) {
  if (lastTopic == String(topic)) {
    stateD = (lastMsg == "1" || lastMsg == "on" || lastMsg == "ON" || lastMsg == "true") ? 1 : 0;
    
    // IMPORTANT: Clear the lastTopic so we don't re-process the same message 
    // in the next loop iteration unless a NEW message arrives.
    lastTopic = ""; 
  }
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Added a more unique ID to avoid collisions
    String clientId = "ESP32Client-" + String(random(0xffff), HEX);
    
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      
      // FIX: You MUST subscribe here, otherwise it won't work after a reconnect
      client.subscribe("readDigitalFromDashboard-1767869262340");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}