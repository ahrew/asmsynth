// asmsyntharoo midi note input
// for arduino nano
// breadboard this shit
// button on d12
// output jack on d11, through a resistor, then split between a 30-300nf cap going to ground and output
// low pass filter. for some reason, the oscillators are faintly heard when volume is at 0, the filter helps tune this out

#include <asmsyntharoo.h>
#include <MIDI.h>
MIDI_CREATE_DEFAULT_INSTANCE();

// declare variables
bool didMyOneTimeAction = false;

void handleNoteOn(byte channel, byte pitch, byte velocity)
{
    // Do whatever you want when a note is pressed.
    wave01_volume(64);
    wave02_volume(127);
    digitalWrite(LED_BUILTIN,HIGH);
    wave01_frequency(keyboard (pitch)); // sets the oscillators to a random note each restart
    wave02_frequency(keyboard (pitch)); //
    // Try to keep your callbacks short (no delays ect)
    // otherwise it would slow down the loop() and have a bad impact
    // on real-time performance.
}

void handleNoteOff(byte channel, byte pitch, byte velocity)
{
    // Do something when the note is released.
    // Note that NoteOn messages with 0 velocity are interpreted as NoteOffs.
    wave01_volume(0);
    wave02_volume(0);
    digitalWrite(LED_BUILTIN,LOW);
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