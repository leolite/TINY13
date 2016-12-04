//tested ok
//  shiftOut(dataPin, clockPin, MSBFIRST, num);  

/*
 * ATtiny13 driving two 74HC595 shift registers
 *
 * Randomly turns on/off output pins of the shift
 * register ICs.
 * A random number of outputs are set high, then
 * a random time delay occurs.  Then the cycle
 *  repeats.
 *
 */
 


//Author: Leo
//Date: 2015.04.02
//IDE Ver.: 1.0.3
//website: github.com/leolite
//MCU: ATMEL ATTINY13
//Programmer: usbtinyisp(@Ladyada https://learn.adafruit.com/usbtinyisp/drivers)
//hardware core: core13(@smeezekitty http://sourceforge.net/projects/ard-core13/)

/*
  Blink without delay
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



//Pin connected to ST_CP of 74HC595
int latchPin = 2;
//Pin connected to SH_CP of 74HC595
int clockPin = 1;
////Pin connected to DS of 74HC595
int dataPin = 0;

void setup() {
  //set pins to output because they are addressed in the main loop
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  //Serial.begin(9600); 
}

void loop() {
  //count up routine
  int num = 1;
  for (int j = 0; j < 8; j++) {
    
    //ground latchPin and hold low for as long as you are transmitting
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, MSBFIRST, num);   
    //return the latch pin high to signal chip that it 
    //no longer needs to listen for information
    digitalWrite(latchPin, HIGH);
    //Serial.println(num,BIN);
    delay(400);
    num = num << 1;
  }
} 
