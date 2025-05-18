# CABINATOR Tweakable Cab Simulator

aaah C++ how inconvenient for you to drop by.  Of course by "inconvenient" I mean COMPLETELY CONVENIENT!

This is a simple Cabinet Simulator for putting after an amp effect VST.  Tweak and play with the four filters to make a variety of different sounds.

## HOW TO
There are four filters to shape the sound of the cabinet.
- **BASS:** a simple variable highpass filter set between 25Hz and 200Hz
- **TREBLE:** a simple variable lowpass filter set between 5000Hz and 2000Hz
- **MIDS:** two parametric EQ controls both with variable gain between -24 and 24dB.  The first has a variable frequency of 200-500Hz and the second 1000-2000Hz.

## NERD SPACE
There are plenty of cab sims out there but because they are based on impulse responses they are fixed.  They model a specific speaker (in fact a specific *recording* of a speaker) 
which is all fine and good but it means you have to faff around with lots of files to find the right sound.

Instead I figured filters with variable frequencies and gain was the way to go.  This means you can mess around with the knobs to get the sound you want without having to fix
your mind in "fender/marshall/etc" space or whatever (which, lets be honest, is very limiting).

There is some frequency information visualised as part of the UI but I wanted to make this as beginner-friendly as possible so there is very little in the way of information about 
what is going on.  Just play around till it sounds good and forget about everything else.

Self-destruct switch not included.
