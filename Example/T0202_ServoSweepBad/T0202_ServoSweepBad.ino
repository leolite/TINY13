
int servopin = 4;
int angle = 150;
void servopulse(int _angle)
{
  int myangle=map(_angle,0,180,500,2000);
  digitalWrite(servopin,HIGH);
  delayMicroseconds(myangle);
  digitalWrite(servopin,LOW);
  delay(20-myangle/1000);
}

void setup()
{
  pinMode(servopin, OUTPUT); 
}

void loop()
{
  for(int i=0;i<20;i++)
  {
    servopulse(angle);
  }
  delay(200);
}





