byte sensorpir = 12;
byte led = 13;


void setup()
{
  pinMode(sensorpir,INPUT);
  pinMode(led,OUTPUT);
  Serial.begin(9600);
}


void loop()
{
  
  if(digitalRead(sensorpir) == HIGH)
  {
    Serial.println("1");
    digitalWrite(led,HIGH);
    delay(10000);
    digitalWrite(led,LOW);
  }
  
}
