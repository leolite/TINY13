//Author: Leo
//Date: 2015.02.17
//IDE Ver.: 1.0.3
//website: github.com/leolite
//MCU: ATMEL ATTINY13
//Programmer: usbtinyisp(@Ladyada https://learn.adafruit.com/usbtinyisp/drivers)
//hardware core: core13(@smeezekitty http://sourceforge.net/projects/ard-core13/)

/*
  Blink
 Turns on an LED on for one second, then off for one second, repeatedly.
 
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


/*
 Fade
 
 This example shows how to fade an LED on pin 0
 using the analogWrite() function.
 
 This example code is in the public domain.
 */

int led = 0;           // the pin that the LED is attached to
int brightness = 0;    // how bright the LED is
int fadeAmount = 5;    // how many points to fade the LED by

// the setup routine runs once when you press reset:
void setup()  { 
  // declare pin 9 to be an output:
  pinMode(led, OUTPUT);
} 

// the loop routine runs over and over again forever:
void loop()  { 
  // set the brightness of pin 9:
  analogWrite(led, brightness);    

  // change the brightness for next time through the loop:
  brightness = brightness + fadeAmount;

  // reverse the direction of the fading at the ends of the fade: 
  if (brightness == 0 || brightness == 255) {
    fadeAmount = -fadeAmount ; 
  }     
  // wait for 30 milliseconds to see the dimming effect    
  delay(30);                            
}


