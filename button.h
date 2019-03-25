#ifndef WIRINGPI_H
#define WIRINGPI_H
#include <wiringPi.h>
#endif

#define SHIFT_L 2
#define SHIFT_R 3
#define DSR 0 
#define DELAY 20
#define COMM_PERIOD 100

extern int fd;

typedef struct
{
	unsigned int shiftl;
	unsigned int shiftr;
	unsigned int dsr;
	int shiftTime;
	int dsrTime;
} buttons;

extern int buttonSetup();
extern int buttonScan(buttons *buttons);
extern int sendButtonData(int fd, buttons *buttons);


