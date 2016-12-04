//Author: Leo
//Date: 2015.04.09
//IDE Ver.: 1.0.3
//website: github.com/leolite
//MCU: ATMEL ATTINY13
//Programmer: usbtinyisp(@Ladyada https://learn.adafruit.com/usbtinyisp/drivers)
//hardware core: core13(@smeezekitty http://sourceforge.net/projects/ard-core13/)

/*
Analog Input and Anolog Output(PWM)

 
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


int pwmPin = 0; //Pin 0
int analogInPin = A1; //Pin 7

void setup()
{
  pinMode(pwmPin, OUTPUT);
  //pinMode(analogInPin, INPUT);
}

void loop()
{
  int analogIn = analogRead(analogInPin); // Read analog voltage on pin 7 (A1)
  analogWrite(pwmPin, analogIn / 4); // Output analog reading to dimmable LED
  delay(200);
}


