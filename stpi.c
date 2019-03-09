#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <wiringPi.h>
#include <wiringSerial.h>
#include "frame.h"
#include "lightBand.h"

#define SERIALPORT "/dev/ttyS0"
#define BAUDRATE 19200

int main()
{
	int serialFd;
	int time;
	char buffer[100];
	char *bufferptr = buffer;
	char frameStr[FRAME_LENGTH];

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
		while(serialDataAvail(serialFd))
		{
			bufferptr++ = serialGetchar(serialFd);
			//\n indicates the end of a frame
			if(*(bufferptr - 1) == '\n')
			{
				for(int i = 1; i <= 5; i++)
					frameStr[i - 1] = *(bufferptr - i);
				bufferptr = buffer; //ptr goes back to the top of the buffer
				frame = decodeFrame(frameStr);
			}

		}

		//receive input from buttom
		

		//TODO: lightBandUpdate(frame.rpm);

		
	}
	
	return 0;
}	
