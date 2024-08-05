// 01.08.2024 - João V. S. Soeiro

int analogPin = A1; // Terminal do divisor de tensão 0-5V conectado ao pino analógico 3
int val = 0;        // Variável para guardar o valor lido de 0-1023 (valor binário)  
float volt = 0.0; // Variável para guardar a tensão lida na porta analógica 3
float bar = 0.0; // Variável para guardar a o valor da pressão (em bar)   

float sensorMaxP = 100.0;
 
void setup() {
  Serial.begin(9600);           // Configura a porta serial (UART)
}

void loop() {
  val = analogRead(A1);  // Lê o pino de entrada
  volt = bitToVolt(val);
  bar = bitToBar(val);
  
  Serial.println("----- Valores lidos-----");
  Serial.print(val);          // Imprime o valor na porta serial em bits
  Serial.println(" bits");
  Serial.print(volt, 4);              // Imprime o valor na porta serial em volts
  Serial.println(" Volts");
  Serial.print(bar, 4);              // Imprime o valor da porta serial em bar
  Serial.println(" Bar");
  Serial.println("------------------------");
  delay(2500);
}

float bitToBar(int bits){
  return (bits * sensorMaxP) / 1023.0;
}
float bitToVolt(int bits){
  return (bits * 5.0) / 1023.0;
}
