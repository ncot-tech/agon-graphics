# Agon Light 2 Graphics Demos

These are various random graphics demos that test out parts of the VDP. You will need the Console 8 versions of the Agon's operating system for these to work.

You'll need the "AGDev" C compiler already installed and working before this will be any use.

It's also highly recommended to have the fab-agon-emulator installed.

The "Tools" folder contains useful utilities, but they're designed for me and come with no documentation!

It's best if you poke around the source, and have a look at the code.

* Running "make" will compile things
* "make dist" will compile everything and build all the assets
* Running "make emulate" will also copy the code and assets into the fake SD card and start the emulator. It will also edit/create an autoexe.txt file in the fake SD card folder so your code starts immediately. Copy the autoexec.txt first if you've customised it.
* Running "make inst_sd" will do the same, but to a real SD card. You will need to edit the Makefile to set where your SD card is!
