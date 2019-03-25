#include "button.h"

int buttonSetup()
{
	pinMode(SHIFT_L, INPUT);
	pinMode(SHIFT_R, INPUT);
	pinMode(DSR, INPUT);
	pullUpDnControl(SHIFT_L, PUD_UP);
	pullUpDnControl(SHIFT_R, PUD_UP);
	pullUpDnControl(DSR, PUD_UP);
	return 0;
}

int buttonScan(buttons *buttons)
{
	buttons->shiftl = 0;
	buttons->shiftr = 0;
	buttons->dsr = 0;

	if(digitalRead(SHIFT_L) == 0)
	{
		delay(DELAY);
		if(digitalRead(SHIFT_L) == 0)
			buttons->shiftl = 1;
	}
	
	if(digitalRead(SHIFT_R) == 0)
	{
		delay(DELAY);
		if(digitalRead(SHIFT_R) == 0)
			buttons->shiftr = 1;
	}
	
	if(digitalRead(DSR) == 0)
	{
		delay(DELAY);
		if(digitalRead(DSR) == 0)
			buttons->dsr = 1;
	}

	return 0;
}

int sendButtonData(int fd, buttons *buttons)
{
	char str[5];
	str[1] = 'b';
	str[2] = buttons->shiftl?'1':'0';
	str[3] = buttons->shiftr?'1':'0';
	str[4] = buttons->dsr?'1':'0';
	str[5] = '\n';
	serialPrintf(fd,str);
	return 0;
}
