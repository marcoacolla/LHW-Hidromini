#include <Arduino.h>

int relay = 8;
volatile byte relayState = HIGH;

long lastMsInterval = 0;
long msInterval = 5000;

void setup() {
  Serial.begin(115200);
  pinMode(relay, OUTPUT);

}

void loop() {
  if((millis() - lastMsInterval) > msInterval){
    lastMsInterval = millis();

    digitalWrite(relay, relayState);
    Serial.println("LUZ: " +  !relayState);
    
    relayState = !relayState;


  } 
  

}
