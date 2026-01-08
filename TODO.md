In the Front end fix the code for having & for output values

Fix the on the github library code.
2. The MQTT "Flooding" Error (Critical)

Error Explanation: Your loop() runs thousands of times per second. Because there is no "if" statement checking if the pin value changed, your ESP is trying to send a message to the broker 1,000+ times every second.

Consequence: The HiveMQ public broker will see this as a Spam/DoS attack and automatically ban your IP address or disconnect your device within seconds.

Suggestion: You must implement a "State Change Detection." You should only call the write function if the current value is different from the last value read.

Generate random generated client id for client.connect()