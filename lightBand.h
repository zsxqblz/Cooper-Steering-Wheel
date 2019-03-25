#ifndef WIRINGPI_H
#define WIRINGPI_H
#include <wiringPi.h>
#endif

#define RPM_1 2000
#define RPM_2 3000
#define RPM_3 4000
#define RPM_4 5000
#define RPM_5 6000
#define RPM_6 7000
#define RPM_7 8000
#define RPM_8 9000
#define RPM_9 10000

#define G1 21
#define G2 22
#define G3 23
#define G4 24
#define Y1 25
#define Y2 26
#define R1 27
#define R2 28

extern int lightBandInit();
extern int lightBandUpdate(int rpm);
extern int rpmTest(unsigned int rpm);
