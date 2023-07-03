# asmsynth
originally by ezasm  
background:  
I already built and am quite happy with the Peter Zimon SFM, but was bummed by it being a monosynth.
i discovered this project through youtube, while searching for arduino polyphony solutions
the first method i found involved using one arduino nano for each voice, which didn't seem economical, even though nano clones are only ~$5 each
this library seemed like a quick and dirty way to get polyphony out of an arduino nano, and after testing the example programs, i attempted to create a test program for midi integration
i created this fork because there is a variable 'channel' in both MIDI and asmsynth libraries, which is causing compile errors  

maybe dig into the code and implement sine wave and noise like ezasm planned in the documentation? could be a tall order, i know nothing about assembly.  

original readme:
This is audio library and allows you to generate up to 32 voices at the same time. It also allows you to create background music by executing two programs asynchronously.
In addition, the H bridge is supported, so you can use it as a speaker amplifier or control the motors.
