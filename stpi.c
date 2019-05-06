#ifndef STDIO_H
#define STDIO_H
#include <stdio.h>
#endif
#include <string.h>
#include <errno.h>

#ifndef WIRINGPI_H
#define WIRINGPI_H
#include <wiringPi.h>
#endif
#include <wiringSerial.h>
#ifndef FRAME_H
#define FRAME_H
#include "frame.h"
#endif
#include "lightBand.h"
#include "button.h"
#include "display.h"

#define SERIALPORT "/dev/ttyS0"
#define BAUDRATE 57600

int fd;

int main(int argc, char **argv)
{
	int nextTime;
	char buffer[100];
	char *bufferptr = buffer;
	//char frameStr[FRAME_LENGTH];
	frame frame;
	frame.rpm = 0;
	buttons buttons;
	
	if((fd = serialOpen(SERIALPORT, BAUDRATE)) < 0)
	{
		fprintf (stderr, "Unable to open serial device: %s\n", strerror (errno)) ;
		return 1;
	}

	if(wiringPiSetup() == -1)
	{
		fprintf (stdout, "Unable to start wiringPi: %s\n", strerror (errno)) ;
		return 1;
	}
	// initialize pins for buttons
	buttonSetup();
	// initialize pins for lightband
	lightBandInit();
	// initialize screen and obtain the pointers to labels
	windowPtrs wptrs = displayInit(argc, argv);
	nextTime = millis() + COMM_PERIOD;

	//main program cycle
	for(;;)
	{
		//receive from serial
		while(serialDataAvail(fd))
		{
			*bufferptr = serialGetchar(fd);
			bufferptr++;
			//\n indicates the end of a frame
			if(*(bufferptr - 1) == '\n')
			{
				//for(int i = 1; i <= FRAME_LENGTH; i++)
				//	frameStr[FRAME_LENGTH - i] = *(bufferptr - i - 1);
				bufferptr = buffer; //ptr goes back to the top of the buffer
				//printf(frameStr);
				//if(decodeFrame(frameStr, &frame) == 1)
				//	fprintf(stderr, "bad\n");
				int errorCode = decodeFrame(buffer, &frame);
				if(errorCode > 0)
					fprintf(stderr, "bad frame: %d\n", errorCode);
			}
		}

		//receive input from button and send data
		if(millis() > nextTime)
		{
			if(buttonScan(&buttons) < 0)
				fprintf(stderr, "scan buttons failed");
			else if(sendButtonData(fd, &buttons) < 0)
				fprintf(stderr, "send data failed");

			lightBandUpdate(frame.rpm);
			nextTime = millis() + COMM_PERIOD;
		}

		//update display
		displayUpdate(frame, wptrs);
	}
	
	return 0;
}	
