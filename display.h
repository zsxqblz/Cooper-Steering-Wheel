#include <gtk/gtk.h>
#ifndef STDIO_H
#define STDIO_H
#include <stdio.h>
#endif

#ifndef FRAME_H
#define FRAME_H
#include "frame.h"
#endif

#define FONT_SIZE 30
#define SCREEN_LENGTH 650
#define SCREEN_HEIGHT 460

typedef struct
{
	GtkWidget *window;
	GtkWidget *label_rpm;
	GtkWidget *label_gearNum;
	GtkWidget *label_tps;
	char rpm_buffer[6];
	char gearNum_buffer[2];
	char tps_buffer[4];
} windowPtrs; 

extern windowPtrs displayInit(int argc, char **argv);
extern void displayUpdate(frame frame, windowPtrs ptrs);
