all: stpi.c frame.c button.c lightBand.c display.c
	gcc -o stpi stpi.c button.c frame.c lightBand.c display.c -lwiringPi -Wall `pkg-config --cflags gtk+-2.0` `pkg-config --libs gtk+-2.0`
