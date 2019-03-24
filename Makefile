all: stpi.c frame.c button.c lightBand.c
	gcc -o stpi stpi.c button.c frame.c lightBand.c -lwiringPi -Wall
