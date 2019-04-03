#define RPM_H 'r'
#define GEAR_H 'g'
#define RPM_POSITION 0
#define GEAR_POSITION 3
#define FRAME_LENGTH 5

typedef struct
{
	unsigned int rpm;
	unsigned short gearNum;
	short tps;
	unsigned short goodFrame;
} frame;

extern int decodeFrame(char *arr, frame *frame);
