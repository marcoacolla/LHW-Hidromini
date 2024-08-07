// 01.08.2024 - João V. S. Soeiro

int analogPin = A1; // Terminal do divisor de tensão 0-5V conectado ao pino analógico 3
int val = 0;        // Variável para guardar o valor lido de 0-1023 (valor binário)  
float volt = 0.0; // Variável para guardar a tensão lida na porta analógica 3
float bar = 0.0; // Variável para guardar a o valor da pressão (em bar)   

float rpm;
float g_rpm;

unsigned long interval = 2500;
unsigned long previousMillis = 0;

unsigned long pulsesPerCycle = 1000;

int cwPin = 3;
volatile unsigned long pulses = 0;

float sensorMaxP = 100.0;
 
void setup() {
  Serial.begin(9600);  // Configura a porta serial (UART)
  Serial3.begin(115200);         

}

void loop() {
  val = analogRead(A1);  // Lê o pino de entrada
  volt = bitToVolt(val);
  bar = bitToBar(val);

  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    RPM_COUNT();

    Serial3.print(bar);
    Serial3.print(",");
    Serial3.print("99");
    Serial3.print(",");
    Serial3.print("99");
    Serial3.print(",");
    Serial3.print(rpm);
    Serial3.print(",");
    Serial3.print(g_rpm);

    previousMillis = currentMillis;
  }
  
}

float bitToBar(int bits){
  return (bits * sensorMaxP) / 1023.0;
}
float bitToVolt(int bits){
  return (bits * 5.0) / 1023.0;
}

void pulseCounter(){
  pulses++;
}
void RPM_COUNT(){

  rpm = (pulses) * (60000.0 / (interval*pulsesPerCycle));
  g_rpm = rpm*1.24;

  pulses = 0;
}