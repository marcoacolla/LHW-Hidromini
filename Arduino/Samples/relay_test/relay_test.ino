
int relayPin1 = 8;
int relayPin2 = 9;
int relayPin3 = 10;
int relayPin4 = 11;

volatile byte relayState = HIGH;

long lastMsInterval = 0;
long msInterval = 4000;
long eachInterval = 1000;

void setup() {
  Serial.begin(115200);
  pinMode(relayPin1, OUTPUT);
  pinMode(relayPin2, OUTPUT);
  pinMode(relayPin3, OUTPUT);
  pinMode(relayPin4, OUTPUT);


}

void loop() {


  if((millis() - lastMsInterval) > msInterval){
    lastMsInterval = millis();

    digitalWrite(relayPin1, relayState);
    delay(eachInterval);
    digitalWrite(relayPin2, relayState);
    delay(eachInterval);
    digitalWrite(relayPin3, relayState);
    delay(eachInterval);
    digitalWrite(relayPin4, relayState);
    delay(eachInterval);
    
    relayState = !relayState;


  } 
  

}
