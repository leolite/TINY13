//还没想好怎么调节PWM长度
/*
  TCCR0B |= (0 << CS02) | (0 << CS01) | (1 << CS00); // Prescaler: 1 ==> Preiod: 27us Freq: 37 kHz
  TCCR0B |= (0 << CS02) | (1 << CS01) | (0 << CS00); // Prescaler: 8 ==> Preiod: 0.2ms Freq: 4.6 kHz
  TCCR0B |= (0 << CS02) | (1 << CS01) | (1 << CS00); // Prescaler: 16  ==> Preiod: 1.7ms Freq: 579Hz
*/


//Author: Leo
//Date: 2015.03.12
//IDE Ver.: 1.0.3
//website: github.com/leolite
//MCU: ATMEL ATTINY13
//Programmer: usbtinyisp(@Ladyada https://learn.adafruit.com/usbtinyisp/drivers)
//hardware core: core13(@smeezekitty http://sourceforge.net/projects/ard-core13/)

/*

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


int speakerPin = 0; //PWM0

int overflowValueCTC =123; //50%



void setup(){
  pinMode(speakerPin, OUTPUT);   
  // Initialize the timer
  setup_timer();
}

void loop() {
}


// TIMER0 -- Only one in attiny13
void setup_timer(void) {
  //timer 1:
  TCCR0A = 0;// set entire TCCR1A register to 0
  TCCR0B = 0;// same for TCCR1B

  // Set up the timer 
  TCCR0A |= (1 << WGM01)| (1 << WGM00);  // Mode: fast PWM
  TCCR0B |= (0 << CS02) | (1 << CS01) | (1 << CS00); // Prescaler: 1

  //Enable PWM
  TCCR0A |= (1 << COM0A1); //比较匹配发生时OC0A 取反
  //TCCR0A |= (1 << COM0B1); //比较匹配发生时OC0B 取反

  // Initialize the count
  TCNT0 = 0;

  // Initialize the compare value
  OCR0A = overflowValueCTC;

  // Enable compare interrupt
  //TIMSK0 |= (1 << OCIE0A);

  // Enable global interrupts
  sei();
}



