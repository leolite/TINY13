//tested ok ,but random...cycle long,,,what's this...

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




#include <stdlib.h>
#include <avr/io.h>
#include <util/delay.h>

#define DATA 0
#define CLOCK 1
#define LATCH 2


int d;
char n;
char i;
void setup(){
  // set DATA, LATCH and CLOCK pins to OUTPUT
  DDRB |= (1 << DATA);
  DDRB |= (1 << LATCH);
  DDRB |= (1 << CLOCK);
  PORTB = 0;
}

void loop() {
  for(;;) {
    // choose number of LEDs to light up.
    // n will be between 4 and 16
    n = 4 + (random() % 13);

    for(i=0;i<16;i++) {
      // for each LED, probability of it being lit
      // is n/16
      if ((random() % 16) <= n) {
        PORTB |= (1 << DATA);  // set DATA pin high
      } 
      else {
        PORTB &= ~(1 << DATA); // set DATA pin low
      }

      // toggle shift register clock pin
      PORTB |= (1 << CLOCK);
      _delay_ms(2);
      PORTB &= ~(1 << CLOCK);
    }

    // once we've shifted out all 16 values, toggle
    // the latch pin.
    PORTB |= (1 << LATCH);
    _delay_ms(2);
    PORTB &= ~(1 << LATCH);

    // delay random amount of time between
    // 100ms and 500ms
    d = 100 + (random() % 400);
    for(i=0;i<d;i++) {
      // _delay_ms function must be called with a
      // constant value, not a variable!
      _delay_ms(1);
    }

  }

}

