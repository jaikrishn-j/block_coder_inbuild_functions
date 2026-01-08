// Auto-generated code


#ifdef ESP32

	#include <WiFi.h>

#else

	#include <ESP8266WiFi.h>

#endif

#include <map>

#include <PubSubClient.h>

const char* ssid = "Your_SSID";
const char* password = "Your_PASSWORD";

const char* mqtt_host = "broker.emqx.io";

const uint16_t mqtt_port = 1883;

WiFiClient espClient;

PubSubClient client(espClient);

std::map<String, int> topicRegistry;
std::map<String, int> lastPublishedValues;

void callback(char* topic, byte* payload, unsigned int length);

void reconnect();

String lastTopic = "";

String lastMsg = "";

void writeDigitalToDashboard(int signalLevel, const char* topic);
void readDigital(int pinD, int &stateD);
void writeDigital(int targetPin, int signalLevel);
void readDigitalFromDashboard(int &stateD, const char* topic);

void setup() {
	Serial.begin(115200);
	WiFi.begin(ssid, password);
	while (WiFi.status() != WL_CONNECTED) delay(500);
	
	client.setServer(mqtt_broker, mqtt_port);
	client.setCallback(callback);
	pinMode(2, INPUT);
	pinMode(3, OUTPUT);
}

void loop() {
	int e_getPin_1767780006610_pin_output_readDigital_1767780016267_pinD_digital_in_1767780019860 = 2;
	int e_readDigital_1767780016267_stateD_digital_out_writeDigitalToDashboard_1767780002074_signalLevel_digital_in_1767780022760;
	int e_readDigitalFromDashboard_1767869262340_stateD_digital_out_writeDigital_1767869255266_signalLevel_digital_in_1767869267533;
	int e_getPin_1767867844597_pin_output_writeDigital_1767869255266_targetPin_digital_in_1767869271783 = 3;
	if (!client.connected()) reconnect();
	client.loop();


	// Function calls
	readDigitalFromDashboard(e_readDigitalFromDashboard_1767869262340_stateD_digital_out_writeDigital_1767869255266_signalLevel_digital_in_1767869267533, "readDigitalFromDashboard-1767869262340");
	readDigital(e_getPin_1767780006610_pin_output_readDigital_1767780016267_pinD_digital_in_1767780019860, e_readDigital_1767780016267_stateD_digital_out_writeDigitalToDashboard_1767780002074_signalLevel_digital_in_1767780022760);
	writeDigital(e_getPin_1767867844597_pin_output_writeDigital_1767869255266_targetPin_digital_in_1767869271783, e_readDigitalFromDashboard_1767869262340_stateD_digital_out_writeDigital_1767869255266_signalLevel_digital_in_1767869267533);
	writeDigitalToDashboard(e_readDigital_1767780016267_stateD_digital_out_writeDigitalToDashboard_1767780002074_signalLevel_digital_in_1767780022760, "writeDigitalToDashboard-1767780002074");
}

// Function definition for writeDigitalToDashboard
void writeDigitalToDashboard(int signalLevel, const char* topic) {
  if (!client.connected()) return;

  // Only publish if the value has changed
  if (signalLevel != lastPublishedValues[topic]) {
    char msg[2];
    itoa(signalLevel, msg, 10);
    if (client.publish(topic, msg)) {
      lastPublishedValues[topic] = signalLevel;
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
  if (lastTopic == String(topic)) {
    // Accept common ON/1/true variants
    String msg = lastMsg;
    stateD = (msg == "1" || msg == "on" || msg == "ON" || msg == "true") ? 1 : 0;
    // Clear lastTopic to avoid reprocessing (optional but safe)
    lastTopic = "";
  }
}


void callback(char* topic, byte* payload, unsigned int length) {
	char message[length + 1];
	memcpy(message, payload, length);
	message[length] = '\0';
	
	int value = atoi(message);
	topicRegistry[String(topic)] = value; // Store for the loop functions
	
	Serial.printf("Topic: %s | Message: %d\n", topic, value);
}
void reconnect() {
	while (!client.connected()) {
		Serial.print("Attempting MQTT connection...");
		String clientId = "NodeMCU-" + String(random(0xffff), HEX);
		
		if (client.connect(clientId.c_str())) {
			Serial.println("connected");
			// Re-subscribe to all topics currently in our registry keys
			for (auto const& [topic, val] : topicRegistry) {
				client.subscribe(topic.c_str());
			}
		} else {
			Serial.print("failed, rc=");
			Serial.print(client.state());
			delay(5000);
		}
	}
}