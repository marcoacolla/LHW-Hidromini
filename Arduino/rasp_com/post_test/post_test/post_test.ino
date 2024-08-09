#include <WiFi.h>
#include <PubSubClient.h>

// WiFi settings
const char *ssid = "LAB LHW";             // Replace with your WiFi name
const char *password = "MOBILIDADELHW";   // Replace with your WiFi password

// MQTT Broker settings
const char *mqtt_broker = "10.0.1.119";  // EMQX broker endpoint
const char *mqtt_topic = "/esp8266/pressure";     // MQTT topic
const int mqtt_port = 1883;  // MQTT port (TCP)
float c = 0;
WiFiClient espClient;
PubSubClient mqtt_client(espClient);

void connectToWiFi();

void connectToMQTTBroker();

void mqttCallback(char *topic, byte *payload, unsigned int length);

void setup() {
    Serial.begin(115200);
    connectToWiFi();
    mqtt_client.setServer(mqtt_broker, mqtt_port);
    mqtt_client.setCallback(mqttCallback);
    connectToMQTTBroker();
}

void connectToWiFi() {
    WiFi.begin(ssid, password);
    Serial.print("Connecting to WiFi");
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\nConnected to the WiFi network");
}

void connectToMQTTBroker() {
  while (!mqtt_client.connected()) {
    String client_id = "esp8266-client-" + String(WiFi.macAddress());
    Serial.printf("Connecting to MQTT Broker as %s.....\n", client_id.c_str());
    if (mqtt_client.connect(client_id.c_str())) {
      Serial.println("Connected to MQTT broker");
      mqtt_client.subscribe(mqtt_topic);
      // Publish message upon successful connection
    } else {
      Serial.print("Failed to connect to MQTT broker, rc=");
      Serial.print(mqtt_client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

void mqttCallback(char *topic, byte *payload, unsigned int length) {
    Serial.print("Message received on topic: ");
    Serial.println(topic);
    Serial.print("Message:");
    for (unsigned int i = 0; i < length; i++) {
        Serial.print((char) payload[i]);
    }
    Serial.println();
    Serial.println("-----------------------");
}

void loop() {
    if (!mqtt_client.connected()) {
      connectToMQTTBroker();
    }else{
      static char buffer[7];
      dtostrf(c,6,2,buffer);
      mqtt_client.publish(mqtt_topic, buffer);
      c++;
      delay(1000);
    }
    mqtt_client.loop();
    
    
}