//#include "pitches.h"
//not tested

// Notes
const int NOTE_C  = 239;
const int NOTE_CS = 225;
const int NOTE_D  = 213;
const int NOTE_DS = 201;
const int NOTE_E  = 190;
const int NOTE_F  = 179;
const int NOTE_FS = 169;
const int NOTE_G  = 159;
const int NOTE_GS = 150;
const int NOTE_A  = 142;
const int NOTE_AS = 134;
const int NOTE_B  = 127;

int Speaker = 8;

void setup() {
  pinMode(Speaker, OUTPUT);
}



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


void loop()
{
  playTune();
  delay(300);
}

void TinyTone(unsigned char divisor, unsigned char octave, unsigned long duration)
{
  TCCR1 = 0x90 | (8-octave); // for 1MHz clock
  // TCCR1 = 0x90 | (11-octave); // for 8MHz clock
  OCR1C = divisor-1;         // set the OCR
  delay(duration);
  TCCR1 = 0x90;              // stop the counter
}

// Play a scale
void playTune(void)
{
  for (int thisNote = 0; thisNote < 9; thisNote++) {
    TinyTone(melody[thisNote], noteDurations[thisNote], noteDurations[thisNote]);
  }
}


// TIMER0 -- Only one in attiny13
void setup_timer(void) {
  //timer 1:
  TCCR0A = 0;// set entire TCCR1A register to 0
  TCCR0B = 0;// same for TCCR1B

  // Set up the timer 
  TCCR0A |= (1 << WGM01);  // Mode: CTC
  TCCR0B |= (1 << CS01); // Prescaler: 

  // Initialize the count
  TCNT0 = 0;

  // Initialize the compare value
  OCR0A = overflowValueCTC;

  // Enable compare interrupt
  TIMSK0 |= (1 << OCIE0A);

  // Enable global interrupts
  sei();
}


