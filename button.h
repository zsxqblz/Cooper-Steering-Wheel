#ifndef WIRINGPI_H
#define WIRINGPI_H
#include <wiringPi.h>
#endif

#define SHIFT_L 2
#define SHIFT_R 3
#define DSR 4
#define DELAY 50

extern int fd;

typedef struct
{
	unsigned int shiftl;
	unsigned int shigtr;
	unsigned int dsr;
	int shiftTime;
	int dsrTime;
	int shiftTimeOld;
	int dsrTimeOld;
} buttons;

extern int buttonSetup();
extern int buttonScan(buttons *buttons);
extern int sendButtonData(int fd, buttons *buttons)


