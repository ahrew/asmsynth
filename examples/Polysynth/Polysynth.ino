// asmsyntharoo polyphony test
// for arduino nano
// breadboard this shit
// midi IN interface as described here https://diyelectromusic.wordpress.com/2020/08/12/arduino-midi-interfaces/
// note: remove rx pin while uploading code, or it won't work
// output jack on d11, through a resistor, then split between a 30-300nf cap going to ground and output
// low pass filter. for some reason, the oscillators are faintly heard when volume is at 0, the filter helps tune this out

#include <asmsyntharoo.h>
#include <MIDI.h>
MIDI_CREATE_DEFAULT_INSTANCE();

// declare variables
bool didMyOneTimeAction = false;
unsigned int notesPlaying;

void handleNoteOn(byte channel, byte pitch, byte velocity) {
  // total wave volume can't exceed 255. this is going to get ugly
  // square waves are counted twice. not going to handle square waves today
   // add 1 to counter notesPlaying for every note on
  if (notesPlaying == 0) {
    wave01_frequency(keyboard(pitch));
    wave01_volume(200);  // for some reason, when only one wave is playing at 255, it's quite a bit louder than multiple voices that add up to 255
  } else if (notesPlaying == 1) {
    wave02_frequency(keyboard(pitch));
    wave01_volume(127);
    wave02_volume(127);
  } else if (notesPlaying == 2) {
    wave03_frequency(keyboard(pitch));
    wave01_volume(85);
    wave02_volume(85);
    wave03_volume(85);
  } else if (notesPlaying == 3) {
    wave04_frequency(keyboard(pitch));
    wave01_volume(63);
    wave02_volume(63);
    wave03_volume(63);
    wave04_volume(63);
  } else if (notesPlaying == 4) {
    wave05_frequency(keyboard(pitch));
    wave01_volume(51);
    wave02_volume(51);
    wave03_volume(51);
    wave04_volume(51);
    wave05_volume(51);
  }else if (notesPlaying == 5) {
    wave06_frequency(keyboard(pitch));
    wave01_volume(42);
    wave02_volume(42);
    wave03_volume(42);
    wave04_volume(42);
    wave05_volume(42);
    wave06_volume(42);
  }else if (notesPlaying == 6) {
    wave07_frequency(keyboard(pitch));
    wave01_volume(36);
    wave02_volume(36);
    wave03_volume(36);
    wave04_volume(36);
    wave05_volume(36);
    wave06_volume(36);
    wave07_volume(36);
  }
  notesPlaying++;
}

void handleNoteOff(byte channel, byte pitch, byte velocity) {
  notesPlaying--;
  if (notesPlaying <= 0) {
    wave01_volume(0);
    notesPlaying = 0;
  } else if (notesPlaying == 1) {
    wave01_volume(200);
    wave02_volume(0);
  } else if (notesPlaying == 2) {
    wave01_volume(127);
    wave02_volume(127);
    wave03_volume(0);
  } else if (notesPlaying == 3) {
    wave01_volume(85);
    wave02_volume(85);
    wave03_volume(85);    
    wave04_volume(0);
  } else if (notesPlaying == 4) {
    wave01_volume(63);
    wave02_volume(63);
    wave03_volume(63);
    wave04_volume(63);    
    wave05_volume(0);
  } else if (notesPlaying == 5) {
    wave01_volume(51);
    wave02_volume(51);
    wave03_volume(51);
    wave04_volume(51);
    wave05_volume(51);
    wave06_volume(0);
  } else if (notesPlaying == 6) {
    wave01_volume(42);
    wave02_volume(42);
    wave03_volume(42);
    wave04_volume(42);
    wave05_volume(42);
    wave06_volume(42);
    wave07_volume(0);
  };
}

void setup() // runs once
{
	// asmsyntharoo setup
  synthSetup();	//configure asmsyntharoo config
	volume(255);	//set the master volume to maximum value

  // MIDI setup, initiates note on/off functions and declares midi channel
  MIDI.setHandleNoteOn(handleNoteOn);
  MIDI.setHandleNoteOff(handleNoteOff);
  MIDI.begin(MIDI_CHANNEL_OMNI);  // use MIDI_CHANNEL_OMNI for all channels, otherwise pick 1-16
}

void loop ()
{
  MIDI.read(); // yup. this is the entire loop.
}

// interrupt made to run once alongside the setup. it's a weird holdover from the original asmsynth library
// only define waves and their shape here, otherwise things lock up
start_interrupt
	if (didMyOneTimeAction == false) {
  wave01();
	sawWave();
	wave02();
	sawWave();
  wave03();
	sawWave();
	wave04();
	sawWave();
  wave05();
	sawWave();
	wave06();
	sawWave();
  }
end_interrupt