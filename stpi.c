#include <stdio.h>
#include <string.h>
#include <errno.h>

#ifndef WIRINGPI_H
#define WIRINGPI_H
#include <wiringPi.h>
#endif
#include <wiringSerial.h>
#include "frame.h"
#include "lightBand.h"
#include "button.h"

#define SERIALPORT "/dev/ttyS0"
#define BAUDRATE 19200

int fd;

int main()
{
	int time;
	char buffer[100];
	char *bufferptr = buffer;
	char frameStr[FRAME_LENGTH];
	frame frame;
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
				for(int i = 1; i <= 5; i++)
					frameStr[i - 1] = *(bufferptr - i);
				bufferptr = buffer; //ptr goes back to the top of the buffer
				decodeFrame(frameStr, &frame);
			}

		}

		//receive input from button and send data
		if(buttonScan(&buttons) > 0)
			fprintf(stderr, "scan buttons failed");
		else if(sendButtonData(fd, &buttons) > 0)
			fprintf(stderr, "send data failed");

		lightBandUpdate(frame.rpm);
		
		
	}
	
	return 0;
}	
