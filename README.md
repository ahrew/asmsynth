# asmsyntharoo
fork of asmsynth by ezasm  
i created this fork because there is a variable 'channel' in both MIDI and asmsynth libraries, caused compile errors  

TO DO:  
- Implement sinWave and noise() in asmsyntharoo.c assembly code  
- build Monosynth program with note counter  
- figure out how to get polyphony
- dissect asmysynth examples to figure out how they used voice and stop functions

IDEAS FOR PROJECTS:  
- design prototype stripboard with socket for nano, midi input circuit, and onboard fx (5v fuzz? lol)  
- breadboard pt2399 based effect powered by nano 5v rail  
- octave up/down switch/button  
- ability to change waveforms via rotary encoder or switch

original readme:  
This is audio library and allows you to generate up to 32 voices at the same time. It also allows you to create background music by executing two programs asynchronously.
In addition, the H bridge is supported, so you can use it as a speaker amplifier or control the motors.
