
#include <Wire.h>
#include <hd44780.h>
#include <hd44780ioClass/hd44780_I2Cexp.h>

hd44780_I2Cexp lcd;

unsigned long interval = 2500;
unsigned long previousMillis = 0;

unsigned long pulsesPerCycle = 1000; //1000; para cwPin

int indexPin = 2;
int cwPin = 3;
int currentPin = A3;

volatile unsigned long pulses = 0;
volatile unsigned long cycles = 0;


void setup() {
  pinMode(indexPin, INPUT_PULLUP);
  pinMode(cwPin, INPUT);
  
  Serial.begin(9600);
  lcd.begin(20, 4);

  attachInterrupt(digitalPinToInterrupt(/*indexPin*/cwPin), pulseCounter, FALLING);
}

void loop() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    RPM_COUNT();

    float maxCurrent = 1023/5;
    int cs_reading = analogRead(currentPin);

    float a_Value = (cs_reading * 30000.0)/ (maxCurrent);
    lcd.setCursor(0, 2);
    
    lcd.print("Current: " );
    lcd.print(cs_reading);
    lcd.print("A");
    previousMillis = currentMillis;
  }
}
void pulseCounter(){
  pulses++;
}
void RPM_COUNT(){

    float rpm = (pulses) * (60000.0 / (interval*pulsesPerCycle));
    float hz = rpm/60;
    Serial.print("RPM: ");
    Serial.println(rpm);
    Serial.print("Hz: ");
    Serial.println(hz);
    Serial.print("Pulses: ");
    Serial.println(pulses);

    // Exibe a velocidade
    lcd.clear();
    lcd.setCursor(0, 0);
    
    lcd.print("RPM: ");
    lcd.print(rpm,2);

    lcd.setCursor(0, 1);
    lcd.print("Hz: ");
    lcd.print(hz, 2);
    
   
    
    pulses = 0;
  
}
