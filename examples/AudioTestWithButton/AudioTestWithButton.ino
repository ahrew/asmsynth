// asmsyntharoo audio test program
// for arduino nano
// breadboard this shit
// button on d12
// output jack on d11, through a resistor, then split between a 30-300nf cap going to ground and output
// low pass filter. for some reason, the oscillators are faintly heard when volume is at 0, the filter helps tune this out
// when you press the button, it opens the volume up on wave01 and wave02

#include <asmsyntharoo.h>

// declare variables
bool didMyOneTimeAction = false;
const int buttonPin = 12;  // the number of the pushbutton pin
int buttonState = 0;  // variable for reading the pushbutton status

void setup() // runs once
{
	synthSetup();	//configure the microcontroller
	volume(255);	//set the master volume to maximum value
  pinMode(12, INPUT_PULLUP); // setup for the pushbutton
}

void loop ()
{
	delay (10); // experiment with this! the less latency in the loop, the better! 
  wave01_frequency(keyboard (random (45, 93))); // sets the oscillators to a random note each loop.
  wave02_frequency(keyboard (random (33, 81))); // sounds like galaga. or turkeys.

  buttonState = digitalRead(buttonPin);
  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (buttonState == LOW) {
    // turn osc 1 and 2 on:
    wave01_volume(64);
    wave02_volume(127);
    digitalWrite(LED_BUILTIN,HIGH);
  } else {
    // turn osc 1 and 2 off:
    wave01_volume(0);
    wave02_volume(0);
    digitalWrite(LED_BUILTIN,LOW);
  }  
}

// interrupt runs once alongside the setup. it's a weird holdover from the original asmsynth library
// only define waves and their shape here, otherwise things lock up
start_interrupt

	if (didMyOneTimeAction == false) {
  wave01();
	squareWave();
	wave02();
	triangleWave();
  }
end_interrupt