//Servo test ok! also like a fade LED

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

// Notes
const int NOTE_C  = 143;
const int NOTE_CS = 135;
const int NOTE_D  = 127;
const int NOTE_DS = 120;
const int NOTE_E  = 113;
const int NOTE_F  = 107;
const int NOTE_FS = 101;
const int NOTE_G  = 95;
const int NOTE_GS = 90;
const int NOTE_A  = 85;
const int NOTE_AS = 80;
const int NOTE_B  = 75;

// notes in the melody:
int melody[] = {
  NOTE_C,
  NOTE_D,
  NOTE_E,
  NOTE_F,
  NOTE_G,
  NOTE_A,
  NOTE_B,
  NOTE_C,
};

int noteDurations[] = {
  4,4,4,4,4,4,4,5
};

int speakerPin = 3;
int speakerStatus = 0;
int tinyToneAct = 0;
//int durationLimit = 0;

int overflowValueCTC =71;



void setup(){
  pinMode(speakerPin, OUTPUT);   
  // Initialize the timer
  setup_timer();
}

void loop() {
  for (int thisNote = 0; thisNote < 9; thisNote++) {
    tinyTone(melody[thisNote]);
    delay(200);
    noTinyTone();
  }
  delay(1000);
}


// TIMER0 -- Only one in attiny13
void setup_timer(void) {
  //timer 1:
  TCCR0A = 0;// set entire TCCR1A register to 0
  TCCR0B = 0;// same for TCCR1B

  // Set up the timer 
  TCCR0A |= (1 << WGM01);  // Mode: CTC
  TCCR0B |= (1 << CS02) | (0 << CS01) | (0 << CS00); // Prescaler: 256

  // Initialize the count
  TCNT0 = 0;

  // Initialize the compare value
  OCR0A = overflowValueCTC;

  // Enable compare interrupt
  TIMSK0 |= (1 << OCIE0A);

  // Enable global interrupts
  sei();
}

//timer 1 interrupt
ISR (TIM0_COMPA_vect) {
  if(tinyToneAct == 1){
    speakerStatus = ~speakerStatus;
    digitalWrite(speakerPin, speakerStatus);
  }
  else{
    digitalWrite(speakerPin, LOW);
  }
}

void tinyTone(int freq){
  OCR0A = freq;
  tinyToneAct = 1;
}
void noTinyTone(){
  tinyToneAct = 0;
  speakerStatus = 0;
}




