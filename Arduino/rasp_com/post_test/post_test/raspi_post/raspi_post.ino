#include <ESP8266WiFi.h>
#include <PubSubClient.h>

// WiFi settings
const char *ssid = "LAB LHWC";             // Replace with your WiFi name
const char *password = "MOBILIDADELHWC";   // Replace with your WiFi password

// MQTT Broker settings
const char *mqtt_broker = "10.0.1.119";  // EMQX broker endpoint
const char *mqtt_topics[] = {
    "/mcc/pressure1",
    "/mcc/pressure2",
    "/mcc/pressure3",
    "/mcc/motor_rpm",
    "/mcc/gen_rpm",
    "/mcc/dc_cur",
    "/mcc/dc_volt"
};  // MQTT topic

const char* test = "/mcc/dc_volt";
const int num_topics = sizeof(mqtt_topics) / sizeof(mqtt_topics[0]); 

const int mqtt_port = 1883;  // MQTT port (TCP)
float c = 0.1;
WiFiClient espClient;
PubSubClient mqtt_client(espClient);

void connectToWiFi();

void connectToMQTTBroker();

void processMessage(String message);

void setup() {
    Serial.begin(115200);
    connectToWiFi();
    mqtt_client.setServer(mqtt_broker, mqtt_port);
    connectToMQTTBroker();
}

void connectToWiFi() {
    WiFi.begin(ssid, password);
    Serial.print("Connecting to WiFi");
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        //Serial.print(".");
    }
    //Serial.println("\nConnected to the WiFi network");
}

void connectToMQTTBroker() {
  while (!mqtt_client.connected()) {
    String client_id = "esp8266-client-" + String(WiFi.macAddress());
    //Serial.printf("Connecting to MQTT Broker as %s.....\n", client_id.c_str());
    if (mqtt_client.connect(client_id.c_str())) {
      //Serial.println("Connected to MQTT broker");
      // Remover a linha de inscrição (subscribe)
      // mqtt_client.subscribe(mqtt_topic);  // Esta linha foi removida
    } else {
      //Serial.print("Failed to connect to MQTT broker, rc=");
      //Serial.print(mqtt_client.state());
      //Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

void loop() {
    if (!mqtt_client.connected()) {
      connectToMQTTBroker();
    } else {
      if (Serial.available() > 0) {
        // Recebe o código via Serial
        String code = Serial.readStringUntil('\n');  // Lê até encontrar uma nova linha
        code.trim();  // Remove espaços em branco extras
        processMessage(code);
        code = "";
        }
      delay(100);
    }
    mqtt_client.loop();  // Mantém a conexão MQTT ativa
}
void processMessage(String message) {
    // Extrai os dois primeiros caracteres como ID
    String id = message.substring(0, 2);
    // Extrai o restante como valor
    String value = message.substring(2);

    // Converte o ID e o valor para números inteiros, se necessário
    int idNumber = id.toInt();
    float valueNumber = value.toFloat();

    // Exemplo de como usar o ID para determinar o tópico MQTT
    if (idNumber >= 0 && idNumber < num_topics) {
        const char *topic = mqtt_topics[idNumber];
        char buffer[10];
        dtostrf(valueNumber, 6, 2, buffer);  // Converte o valor para string com 2 casas decimais
        mqtt_client.publish(topic, buffer);  // Publica o valor no tópico correspondente

        //Serial.print("Published to ");
        //Serial.print(topic);
        //Serial.print(": ");
        //Serial.println(buffer);
    } else {
        //Serial.println("ID fora do intervalo.");
    }
}