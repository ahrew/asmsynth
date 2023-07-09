// asmsyntharoo monosynth with midi input
// for arduino nano
// breadboard this shit
// midi IN interface as described here https://diyelectromusic.wordpress.com/2020/08/12/arduino-midi-interfaces/
// output jack on d11, through a resistor, then split between a 30-300nf cap going to ground and output
// low pass filter. for some reason, the oscillators are faintly heard when volume is at 0, the filter helps tune this out

#include <asmsyntharoo.h>
#include <MIDI.h>
MIDI_CREATE_DEFAULT_INSTANCE();

// declare variables
bool didMyOneTimeAction = false;
unsigned int notesPlaying;
int lastPitch, lastPitch2, lastPitch3, lastPitch4, lastPitch5;

void handleNoteOn(byte channel, byte pitch, byte velocity)
{
    wave01_volume(64); // square waves are counted twice
    wave02_volume(127);
    digitalWrite(LED_BUILTIN,HIGH);
    wave01_frequency(keyboard (pitch)); // sets both oscillators to the note you're playing
    wave02_frequency(keyboard (pitch)); //
    if (notesPlaying == 0) {
      lastPitch = pitch;
    } else if (notesPlaying == 1) {
      lastPitch2 = pitch;
    } else if (notesPlaying == 2) {
      lastPitch3 = pitch;
    }else if (notesPlaying == 3) {
      lastPitch4 = pitch;
    }else if (notesPlaying == 4) {
      lastPitch5 = pitch;
    };
    notesPlaying++;
    // Try to keep your callbacks short (no delays ect)
    // otherwise it would slow down the loop() and have a bad impact
    // on real-time performance.
}

void handleNoteOff(byte channel, byte pitch, byte velocity)
{
  notesPlaying--;
  if (notesPlaying <= 0) {
      wave01_volume(0);
      wave02_volume(0);
      digitalWrite(LED_BUILTIN,LOW);
      notesPlaying = 0;
  } else if (notesPlaying == 1) {
    wave01_frequency(keyboard (lastPitch)); // sets both oscillators to the last note
    wave02_frequency(keyboard (lastPitch)); //
  } else if (notesPlaying == 2) {
    wave01_frequency(keyboard (lastPitch2)); // sets both oscillators to the last note
    wave02_frequency(keyboard (lastPitch2)); //
  } else if (notesPlaying == 3) {
    wave01_frequency(keyboard (lastPitch3)); // sets both oscillators to the last note
    wave02_frequency(keyboard (lastPitch3)); //
  } else if (notesPlaying == 4) {
    wave01_frequency(keyboard (lastPitch4)); // sets both oscillators to the last note
    wave02_frequency(keyboard (lastPitch4)); //
  } else if (notesPlaying == 5) {
    wave01_frequency(keyboard (lastPitch5)); // sets both oscillators to the last note
    wave02_frequency(keyboard (lastPitch5)); //
  };
}

void setup() // runs once
{
	// asmsyntharoo setup
  synthSetup();	//configure the microcontroller
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
	squareWave();
	wave02();
	triangleWave();
  }
end_interrupt