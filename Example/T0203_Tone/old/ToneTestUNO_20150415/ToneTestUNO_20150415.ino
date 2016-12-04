//#include "pitches.h"
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

void loop() {
  // no need to repeat the melody.
  play();//Play the music.
  delay(300);//Pause for a while.
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


void play()
{
  for (int thisNote = 0; thisNote < 9; thisNote++) {

    // to calculate the note duration, take one second 
    // divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000/noteDurations[thisNote];
    tone(Speaker, melody[thisNote],noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(Speaker);
  }
}



