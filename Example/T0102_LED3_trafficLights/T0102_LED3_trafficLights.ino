//Author: Leo
//Date: 2015.02.13
//IDE Ver.: 1.0.3
//website: github.com/leolite
//MCU: ATMEL ATTINY13
//Programmer: usbtinyisp(@Ladyada https://learn.adafruit.com/usbtinyisp/drivers)
//hardware core: core13(@smeezekitty http://sourceforge.net/projects/ard-core13/)

/*
 Traffic lights with 3 LED
 
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


int redled =0;      // LED connected to digital pin 9
int yellowled =1;   // LED connected to digital pin 9
int greenled =2;    // LED connected to digital pin 9
void setup()
{
  // initialize the digital pin as an output.
  pinMode(redled, OUTPUT);
  pinMode(yellowled, OUTPUT); 
  pinMode(greenled, OUTPUT); 
}
void loop()
{
  digitalWrite(redled, HIGH);      // turn the LED on (HIGH is the voltage level)
  delay(2000);                     // wait for a second
  digitalWrite(redled, LOW);       // turn the LED off by making the voltage LOW
  digitalWrite(yellowled, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(500);                      // wait for a moment
  digitalWrite(yellowled, LOW);    // turn the LED off by making the voltage LOW
  digitalWrite(greenled, HIGH);    // turn the LED on (HIGH is the voltage level)
  delay(2000);                     // wait for a second
  digitalWrite(greenled, LOW);    // turn the LED off by making the voltage LOW
  digitalWrite(yellowled, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(500);                      // wait for a moment
  digitalWrite(yellowled, LOW);    // turn the LED off by making the voltage LOW
}




