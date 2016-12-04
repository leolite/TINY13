//Author: Leo
//Date: 2015.03.12
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



// TIMER0 -- Only one in attiny13
void setup_timer(void) {
  //timer 1:
  TCCR0A = 0;// set entire TCCR1A register to 0
  TCCR0B = 0;// same for TCCR1B

  // Set up the timer 
  TCCR0A |= (1 << WGM01);  // Mode: CTC
  TCCR0B |= (1 << CS00) | (1 << CS02); // Prescaler: 1024

//1024 = 280 us
//256 = 50us
//64 = 11us
//8 = 3us
//1 = 3us

  // Initialize the count
  TCNT0 = 0;

  // Initialize the compare value
  OCR0A = 255;

  // Enable compare interrupt
  TIMSK0 |= (1 << OCIE0A);

  // Enable global interrupts
  sei();
}

// Fire this ISR whenever a match occurs
ISR (TIM0_COMPA_vect) {
  // Toggle our port
  PORTB ^= (1 << PB1);
}

void setup(){
  // Connect the LED to pin PB0
  DDRB |= (1 << PB1);
  // Initialize the timer
  setup_timer();
}

void loop() {
}

