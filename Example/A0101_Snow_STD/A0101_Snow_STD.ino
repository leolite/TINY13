//Author: Leo
//Date: 2016.12.04
//IDE Ver.: 1.0.3
//website: github.com/leolite
//MCU: ATMEL ATTINY13
//Programmer: usbtinyisp(@Ladyada https://learn.adafruit.com/usbtinyisp/drivers)
//hardware core: core13(@smeezekitty http://sourceforge.net/projects/ard-core13/)

/*
 Water lights with 5 LED
 
 This example code is in the public domain.
 */

//       ATMEL ATTINY13 / ARDUINO
//
//                      +-\/-+
// [RST]ADC0 (D 5) PB5 1|    |8 Vcc
//      ADC3 (D 3) PB3 2|    |7 PB2 (D 2) ADC1[SCK]
//      ADC2 (D 4) PB4 3|    |6 PB1 (D 1) PWM1[MISO]
//                 GND 4|    |5 PB0 (D 0) PWM0[MOSI]
//                      +----+

int pinOut[] = {
  0,1,2,3,4};
int countOut = 5;
int timerOut = 200;
int countLed = 0;
boolean ledON = LOW;
void setup()
{
  // initialize the digital pin as an output.
  for(int i =0; i<countOut; i++){
    pinMode(pinOut[i], OUTPUT); 
  }
  pinMode(5, INPUT); 
  PORTB |= _BV(5); //HIGH
}
void loop()
{
  for (int i =0; i<countOut; i++){ 
    digitalWrite(pinOut[i], !ledON);  
  }
  digitalWrite(pinOut[countLed], ledON);
  countLed ++;
  if( countLed >= 5) countLed = 0;
  delay(timerOut);
}







