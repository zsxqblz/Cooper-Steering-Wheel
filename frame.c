#include <frame.h>

frame decodeFrame(char *arr)
{
	frame frame;
	frame.goodFrame = 1;

	//check and extract rpm information
	if(arr[RPM_POSITION] == RPM_H)
	{
		//rpm = upper8Bits * 256 + lower8Bits
		frame.rpm = (unsigned int)arr[RPM_POSITION + 1] * (1 << 8) + (unsigned int)arr[RPM_POSITION + 2];
		
		//boundary value chack
		if(frame.rpm > 12000)
		{
			frame.goodFrame = 0;
			return frame;
		}
	}
	else
	{
		frame.goodFrame = 0;
		return frame;
	}

	//check and extract gear number
	if(arr[GEAR_POSITION] == GEAR_H)
	{
		frame.gearNum = (unsigned int)arr[GEARPOSITION + 1];

		//boundary value check, gearNum should be bigger than 6
		if(frame.gearNum > 6)
		{
			frame.goodFrame = 0;
			return frame;
		}
	}
	else
	{
		frame.goodFrame = 0;
		return frame;
	}
	
	return frame;
}
