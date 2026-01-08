// Auto-generated code


#ifdef ESP32

	#include <WiFi.h>

#else

	#include <ESP8266WiFi.h>

#endif

#include <ArduinoJson.h>

#include <PubSubClient.h>

struct TopicMap {

	const char* topic;

	int* variable;

};

WiFiClient espClient;

PubSubClient client(espClient);

const char* ssid = "Your_SSID";
const char* password = "Your_PASSWORD";

const char* mqtt_server = "broker.hivemq.com";

void callback(char* topic, byte* payload, unsigned int length);

void reconnect();

String lastTopic = "";

String lastMsg = "";

void writeDigitalToDashboard(int signalLevel,  const char* topic);
void readDigital(int pinD, int &stateD);
void readDigitalFromDashboard(int &stateD,  const char* topic);
void writeDigital(int targetPin, int signalLevel);

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

	client.setServer(mqtt_server, 1883);

	client.setCallback(callback);

	pinMode(2, INPUT);
	pinMode(3, INPUT);
}

void loop() {
	int e_getPin_1767780006610_pin_output_readDigital_1767780016267_pinD_digital_in_1767780019860 = 3;
	int e_readDigital_1767780016267_stateD_digital_out_writeDigitalToDashboard_1767780002074_signalLevel_digital_in_1767780022760;
	int e_getPin_1767867844597_pin_output_writeDigital_1767867839045_targetPin_digital_in_1767867854718 = 3;
	int e_readDigitalFromDashboard_1767867833298_stateD_digital_out_writeDigital_1767867839045_signalLevel_digital_in_1767867857935;
	if (!client.connected()) reconnect();

	client.loop();


	// Function calls
	writeDigitalToDashboard(e_readDigitalFromDashboard_1767867833298_stateD_digital_out_writeDigital_1767867839045_signalLevel_digital_in_1767867857935, "readDigital-1767780016267");
	readDigital(3, e_readDigitalFromDashboard_1767867833298_stateD_digital_out_writeDigital_1767867839045_signalLevel_digital_in_1767867857935);
	readDigitalFromDashboard(e_readDigitalFromDashboard_1767867833298_stateD_digital_out_writeDigital_1767867839045_signalLevel_digital_in_1767867857935);
	writeDigital(3, e_readDigitalFromDashboard_1767867833298_stateD_digital_out_writeDigital_1767867839045_signalLevel_digital_in_1767867857935);
}

// Function definition for writeDigitalToDashboard
void writeDigitalToDashboard(int signalLevel, const char* topic) {
  // Prepare the payload for the MQTT broker
  const char* payload = (signalLevel == HIGH) ? "1" : "0";

  // Publish the state to the dashboard topic
  if (client.connected()) {
    // Use retained = true so dashboard shows correct state after refresh
    client.publish(topic, payload, true);
  }
}


// Function definition for getPin
// Function definition for readDigital
void readDigital(int pinD, int &stateD) {
  // Read the current digital level (HIGH or LOW) from the specified pin
  // On ESP8266, this returns 1 (HIGH) if voltage is ~3.3V and 0 (LOW) if ~0V
  int currentState = digitalRead(pinD);

  // Update the reference variable with the result
  stateD = currentState;
}


// Function definition for readDigitalFromDashboard
void readDigitalFromDashboard(int &stateD, const char* topic) {
  client.subscribe(topic);
  if (lastTopic == String(topic)) {
    stateD = (lastMsg == "1" || lastMsg == "ON") ? 1 : 0;
  }
}


// Function definition for writeDigital
void writeDigital(int targetPin, int signalLevel) {
  // Directly set the pin state to HIGH (1) or LOW (0)
  // On ESP8266, HIGH outputs 3.3V
  digitalWrite(targetPin, signalLevel);
}


void callback(char* topic, byte* payload, unsigned int length) {

	lastTopic = String(topic);

	lastMsg = "";

	for (int i = 0; i < length; i++) lastMsg += (char)payload[i];

}

void reconnect() {

	while (!client.connected()) {

		if (client.connect("ESP_Client")) {

			Serial.println("Connected");

		} else {

			delay(5000);

		}

	}

}
