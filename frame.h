#define RPM_H 'r'
#define TPS_H 't'
#define GEAR_H 'g'
#define RPM_POSITION 0
#define TPS_POSITION 5
#define GEAR_POSITION 6
#define FRAME_LENGTH 8

typedef struct
{
	unsigned int rpm;
	short tps;
	unsigned short gearNum;
	unsigned short goodFrame;
} frame;

extern int decodeFrame(char *arr, frame *frame);
