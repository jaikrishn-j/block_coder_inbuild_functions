// Auto-generated code


#ifdef ESP32

	#include <WiFi.h>

#else

	#include <ESP8266WiFi.h>

#endif

#include <ArduinoJson.h>

#include <WebSocketsClient.h>

#include <MQTT.h>

WebSocketsClient webSocket;

MQTTClient mqttClient;

const char* ssid = "Your_SSID";
const char* password = "Your_PASSWORD";

const char* mqtt_host = "broker.hivemq.com";

const uint16_t mqtt_port = 8000;

void connectWebSocket();

void onMqttMessage(String &topic, String &payload);

String lastTopic = "";

String lastMsg = "";

void writeDigitalToDashboard(int signalLevel, const char* topic);
void readDigital(int pinD, int &stateD);
void writeDigital(int targetPin, int signalLevel);
void readDigitalFromDashboard(int &stateD, const char* topic);

void setup() {
	Serial.begin(115200);
	delay(100);

	Serial.println("Connecting to WiFi network: Your_SSID");
	WiFi.begin(ssid, password);
	while (WiFi.status() != WL_CONNECTED) {
		delay(500);
		Serial.print(".");
	}
	Serial.println("\nWiFi connected successfully");

	mqttClient.begin(mqtt_host, webSocket);

	mqttClient.onMessage(onMqttMessage);

	connectWebSocket();

	delay(1000); // Wait for connection

	// Subscribe to dashboard topics
	if (mqttClient.connected()) { mqttClient.subscribe("readDigitalFromDashboard-1767869262340"); }

	pinMode(2, INPUT);
	pinMode(3, OUTPUT);
}

void loop() {
	int e_getPin_1767780006610_pin_output_readDigital_1767780016267_pinD_digital_in_1767780019860 = 2;
	int e_readDigital_1767780016267_stateD_digital_out_writeDigitalToDashboard_1767780002074_signalLevel_digital_in_1767780022760;
	int e_readDigitalFromDashboard_1767869262340_stateD_digital_out_writeDigital_1767869255266_signalLevel_digital_in_1767869267533;
	int e_getPin_1767867844597_pin_output_writeDigital_1767869255266_targetPin_digital_in_1767869271783 = 3;
	webSocket.loop();
	mqttClient.loop();


	// Function calls
	readDigitalFromDashboard(e_readDigitalFromDashboard_1767869262340_stateD_digital_out_writeDigital_1767869255266_signalLevel_digital_in_1767869267533, "readDigitalFromDashboard-1767869262340");
	readDigital(e_getPin_1767780006610_pin_output_readDigital_1767780016267_pinD_digital_in_1767780019860, e_readDigital_1767780016267_stateD_digital_out_writeDigitalToDashboard_1767780002074_signalLevel_digital_in_1767780022760);
	writeDigital(e_getPin_1767867844597_pin_output_writeDigital_1767869255266_targetPin_digital_in_1767869271783, e_readDigitalFromDashboard_1767869262340_stateD_digital_out_writeDigital_1767869255266_signalLevel_digital_in_1767869267533);
	writeDigitalToDashboard(e_readDigital_1767780016267_stateD_digital_out_writeDigitalToDashboard_1767780002074_signalLevel_digital_in_1767780022760, "writeDigitalToDashboard-1767780002074");
}

// Function definition for writeDigitalToDashboard
void writeDigitalToDashboard(int signalLevel, const char* topic) {
  // 1. Create a variable that "remembers" the last signal level
  static int lastSignalLevel = -1; 

  // 2. ONLY proceed if the current signal is different from the last one
  if (signalLevel != lastSignalLevel) {
    
    // Prepare the payload for the MQTT broker
    const char* payload = (signalLevel == HIGH) ? "1" : "0";

    // Publish the state to the dashboard topic
    if (client.connected()) {
      client.publish(topic, payload, true);
      
      // 3. Update the "last signal" so we don't send it again until it changes
      lastSignalLevel = signalLevel;
    }
  }
}


// Function definition for readDigital
void readDigital(int pinD, int &stateD) {
  // Read the current digital level (HIGH or LOW) from the specified pin
  // On ESP8266, this returns 1 (HIGH) if voltage is ~3.3V and 0 (LOW) if ~0V
  int currentState = digitalRead(pinD);

  // Update the reference variable with the result
  stateD = currentState;
}


// Function definition for writeDigital
void writeDigital(int targetPin, int signalLevel) {
  // Directly set the pin state to HIGH (1) or LOW (0)
  // On ESP8266, HIGH outputs 3.3V
  digitalWrite(targetPin, signalLevel);
}


// Function definition for readDigitalFromDashboard
void readDigitalFromDashboard(int &stateD, const char* topic) {
  // Nur den Wert setzen, wenn eine neue Nachricht für dieses Topic da ist
  if (lastTopic == String(topic)) {
    stateD = (lastMsg == "1" || lastMsg == "ON") ? 1 : 0;
  }
}


void connectWebSocket() {
	Serial.println("Connecting to MQTT over WebSocket...");
	webSocket.begin(mqtt_host, mqtt_port, "/mqtt");
	webSocket.onEvent([](WStype_t type, uint8, uint8_t *payload, size_t length) {
		if (type == WStype_CONNECTED) {
			Serial.println("WebSocket connected");
			mqttClient.connect();
		} else if (type == WStype_TEXT) {
			mqttClient.poll((char*)payload, length);
		} else if (type == WStype_DISCONNECTED) {
			Serial.println("WebSocket disconnected");
		}
	});
}

void onMqttMessage(String &topic, String &payload) {
	lastTopic = topic;
	lastMsg = payload;
	Serial.print("MQTT: ["); Serial.print(topic); Serial.print("] "); Serial.println(payload);
}
