#include "display.h"

/* Modify the size of fonts in the widget
 * GtkWidget *widget: the widget to Modify
 * int size: font size to set
 */
void set_widget_font_size(GtkWidget *widget, int size) 
{
        PangoFontDescription *font;
        gint fontSize = size;
        font = pango_font_description_from_string("Sans"); 
        pango_font_description_set_size(font, fontSize*PANGO_SCALE);
        gtk_widget_modify_font(GTK_WIDGET(widget), font); 
        pango_font_description_free(font);
}
/* Initialize the screen display
 * int argc: just pass it from main
 * char **argv: just pass it from main
 * return: the struct containing all pointers to labels
 */
windowPtrs displayInit(int argc, char **argv)
{
	windowPtrs ptrs; // the structue to return
	GtkWidget *window;
	gtk_init(&argc, &argv);
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

	// the table to organize rpm, gear#, and tps, with title on the 1st ro and value on the 2nd row
	GtkWidget *table = gtk_table_new(3,2,TRUE);
	gtk_container_add(GTK_CONTAINER(window), table);

	// add rpm title
	GtkWidget *label_rpm_title = gtk_label_new("RPM:");
	set_widget_font_size(label_rpm_title, FONT_SIZE);
	gtk_table_attach_defaults(GTK_TABLE(table), label_rpm_title, 0,1,0,1);

	// add rpm value
	GtkWidget *label_rpm = gtk_label_new("0");
	set_widget_font_size(label_rpm, FONT_SIZE);
	gtk_table_attach_defaults(GTK_TABLE(table), label_rpm, 0,1,1,2);

	// add gear# title
	GtkWidget *label_gearNum_title = gtk_label_new("Gear #:");
	set_widget_font_size(label_gearNum_title, FONT_SIZE);
	gtk_table_attach_defaults(GTK_TABLE(table), label_gearNum_title, 1,2,0,1);

	// add gear# value
	GtkWidget *label_gearNum = gtk_label_new("0");
	set_widget_font_size(label_gearNum, FONT_SIZE);
	gtk_table_attach_defaults(GTK_TABLE(table), label_gearNum, 1,2,1,2);

	// add tps title
	GtkWidget *label_tps_title = gtk_label_new("TPS:");
	set_widget_font_size(label_tps_title, FONT_SIZE);
	gtk_table_attach_defaults(GTK_TABLE(table), label_tps_title, 2,3,0,1);

	// add tps value
	GtkWidget *label_tps = gtk_label_new("0");
	set_widget_font_size(label_tps, FONT_SIZE);
	gtk_table_attach_defaults(GTK_TABLE(table), label_tps, 2,3,1,2);

	gtk_widget_set_size_request(GTK_WIDGET(window), SCREEN_LENGTH, SCREEN_HEIGHT);
	gtk_widget_realize (window);
	gtk_window_fullscreen(window);
	gtk_widget_show_all(window);

	//store label pointers to windowPtrs structure
	ptrs.window = window;
	ptrs.label_rpm = label_rpm;
	ptrs.label_gearNum = label_gearNum;
	ptrs.label_tps = label_tps;
	return ptrs;
}

/* Update the label value and refresh the display
 * frame frame: the frame ftructure containing all values
 * windowPtrs ptrs: all the pointers to labels
 */
void displayUpdate(frame frame, windowPtrs ptrs)
{
	sprintf(ptrs.rpm_buffer, "%d", frame.rpm); //convert int to string
	gtk_label_set_text(ptrs.label_rpm, ptrs.rpm_buffer); //update rpm label 
	sprintf(ptrs.gearNum_buffer, "%d", frame.gearNum);
	gtk_label_set_text(ptrs.label_gearNum, ptrs.gearNum_buffer); //update gear# label 
	sprintf(ptrs.tps_buffer, "%d", frame.tps);
	gtk_label_set_text(ptrs.label_tps, ptrs.tps_buffer); //update tps label 
	gtk_main_iteration(); //gtk main loop iterate once
}
