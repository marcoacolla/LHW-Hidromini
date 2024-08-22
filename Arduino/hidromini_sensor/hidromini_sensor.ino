
const unsigned long INTERVAL = 2500;
unsigned long previousMillis = 0;


const String pressure1_id = "00";
const String pressure2_id = "01";
const String pressure3_id = "02";
const String motor_rpm_id = "03";
const String gen_rpm_id = "04";
const String dc_cur_id = "05";
const String dc_volt_id = "06";


const int PRESSURE1_PIN = A2;  // Pino conectado ao manômetro de pressão
const int PRESSURE2_PIN = A0;  // Pino conectado ao manômetro de pressão
const int PRESSURE3_PIN = A1;  // Pino conectado ao manômetro de pressão
const int CURRENT_PIN = A3; 
const int VOLTAGE_PIN = A4;  // Pino conectado ao sensor ACS712

float sensorMaxP = 10.0;

const unsigned long PULSES_PER_CYCLE = 1000;
const int CW_PIN = 2;

volatile unsigned long pulses = 0;
float voltage;


void setup() {
  pinMode(CW_PIN, INPUT_PULLUP);
  Serial3.begin(115200);
  Serial.begin(115200);

  attachInterrupt(digitalPinToInterrupt(CW_PIN), pulseCounter, FALLING);

  // Mensagem inicial para verificar se o monitor serial está funcionando
  Serial.println("Iniciando o sistema...");
}

void loop() {
  
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= INTERVAL) {
    RPM_COUNT();
    MEASURE_PRESSURE();
    MEASURE_DC_CURRENT();
    VOLTAGE_COUNT();
    
    previousMillis = currentMillis;
  } 

}

void pulseCounter(){
  pulses++;
}

void MEASURE_DC_CURRENT(){
  
    // Leitura do sensor ACS712 com amostragem
    float AvgAcs = 0.0, AcsValueF = 0.0;
    int AcsValue, Samples = 0;
    for (int x = 0; x < 10; x++) {
        AcsValue = analogRead(CURRENT_PIN);   // Lê os valores do sensor de corrente
        Samples += AcsValue;                  // Soma as amostras
        delay(3);                             // Aguarda 3ms entre as amostras
    }
    AvgAcs = Samples / 10.0;;
                   // Calcula a média das amostras
    voltage = AvgAcs * (5.0 / 1024.0);        // Converte a média para tensão (0-5V)
    AcsValueF = (2.5 - voltage)/ 0.100;
    Serial.println(AcsValueF);   // Calcula a corrente em mA
    Send_Data(dc_cur_id, AcsValueF);

}
void MEASURE_PRESSURE(){
  
    // Leitura do manômetro de pressão
    float bar1 = ((analogRead(PRESSURE1_PIN) * (sensorMaxP / 1023.0)));        // Converte a tensão para pressão em bar
    float bar2 = ((analogRead(PRESSURE2_PIN) * (sensorMaxP / 1023.0)));      // Converte a tensão para pressão em bar
    float bar3 = ((analogRead(PRESSURE3_PIN) * (sensorMaxP / 1023.0)));   
         // Converte a tensão para pressão em bar
  if(Serial3.available()){ 
      Send_Data(pressure1_id, bar1);

      Send_Data(pressure2_id, bar2);

      Send_Data(pressure3_id, bar3);
    }

}
void RPM_COUNT() {
    float rpm = (pulses * 60000.0) / (INTERVAL * PULSES_PER_CYCLE);
    float gen_rpm = rpm *1.24;
    if(Serial3.available()){ 
      Send_Data(motor_rpm_id, rpm);
      Send_Data(gen_rpm_id, gen_rpm);
    }

    pulses = 0;
}
void Send_Data(String data_id, float data){
  Serial3.print(data_id);
  Serial3.println(data);
  //Serial.print(data_id);
  //Serial.println(data);
  delay(20);
}

void VOLTAGE_COUNT(){
  int reading = analogRead(VOLTAGE_PIN);  // Leitura do pino analógico A5

  float dcVoltage = (reading / 1023.0) * 105;

  if(Serial3.available()){ 
      Send_Data(dc_volt_id, dcVoltage);

    }
}
