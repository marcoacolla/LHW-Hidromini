
float voltage;
int pino = A0;

void setup()
{
  Serial.begin(9600);                    //Start Serial Monitor to display current read value on Serial monitor
}

void loop()
{
  unsigned int x=0;
  float AcsValue=0.0,Samples=0.0,AvgAcs=0.0,AcsValueF=0.0;
  for (int x = 0; x < 10; x++)          //Get 10 samples
  {
    AcsValue = analogRead(pino);           //Read current sensor values   
    Samples = Samples + AcsValue;        //Add samples together
    delay (3);                           // let ADC settle before next sample 3ms
  }
  AvgAcs=Samples/10.0;                   //Taking Average of Samples
  voltage=AvgAcs*(5.0 / 1024.0);  
  Serial.print("bits:");
  Serial.print(AvgAcs);       //((AvgAcs * (5.0 / 1024.0)) is converitng the read voltage in 0-5 volts
  Serial.print("Raw Voltage:");
  Serial.print(voltage);
  AcsValueF = (voltage)*1/0.757; //2.5 is offset,,,   0.185v is rise in output voltage when 1A current flows at input
  Serial.print("\t");
  Serial.print("Motor Current :");
  Serial.print(AcsValueF);               //Print the read current on Serial monitor
  Serial.println(" A");
  delay(3000);
}