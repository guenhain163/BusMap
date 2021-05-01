/* GTK definitions */
#include <gtk-3.0/gtk/gtk.h>

// Make them global
GtkWidget  *window;
GtkWidget  *fixed1;
GtkWidget  *buttonMenu;
GtkWidget  *menuBar;
GtkWidget  *sw_noti;
GtkWidget  *sw_util;
GtkWidget  *sw_feed;
GtkWidget  *fixed2;
GtkWidget  *stackNoti;
GtkWidget  *stackUtil;
GtkWidget  *stackFeed;
GtkBuilder *builder;

/* Main program */
int main(int argc, char *argv[])
{
    gtk_init (&argc, &argv); // init Gtk

//------------------------------------------------------------------------
// Establish contact with sml code used to adjust widget settings
//------------------------------------------------------------------------

    /* Load the Glade window description.  */
    builder = gtk_builder_new();
    gtk_builder_add_from_file (builder, "window_main.glade", NULL);

    window = GTK_WIDGET(gtk_builder_get_object(builder, "window_main"));
    fixed1 = GTK_WIDGET(gtk_builder_get_object(builder, "fixed1"));
    buttonMenu = GTK_WIDGET(gtk_builder_get_object(builder, "buttonMenu"));
    menuBar = GTK_WIDGET(gtk_builder_get_object(builder, "menuBar"));
    fixed2 = GTK_WIDGET(gtk_builder_get_object(builder, "fixed2"));

    sw_noti = GTK_WIDGET(gtk_builder_get_object(builder, "sw_noti"));
    sw_util = GTK_WIDGET(gtk_builder_get_object(builder, "sw_util"));
    sw_feed = GTK_WIDGET(gtk_builder_get_object(builder, "sw_feed"));

    stackNoti = GTK_WIDGET(gtk_builder_get_object(builder, "stackNoti"));
    stackUtil = GTK_WIDGET(gtk_builder_get_object(builder, "stackUtil"));
    stackFeed = GTK_WIDGET(gtk_builder_get_object(builder, "stackFeed"));

    gtk_builder_connect_signals(builder, NULL);
    g_object_unref(builder);

    gtk_widget_hide(menuBar); // Hide the menuBar
    gtk_widget_show(window); // Show the window

    gtk_main(); //Run the event loop

    /* We have quit.  Free storage and exit. */
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    g_slice_free(GtkWidget, window);

    return EXIT_SUCCESS;
}

/* When the window is closed, the application exits.  */
void on_window_main_destroy()
{
    gtk_main_quit();
}

void on_buttonMenu_clicked (GtkButton *buttonMenu)
{
    gtk_widget_show(menuBar);
}

void on_togglebuttonState_toggled (GtkToggleButton *togglebutton, GtkWidget *sw_page)
{
	gboolean button_state;
	
	button_state = gtk_toggle_button_get_active(togglebutton);
	
	if (button_state) {
		// button is active
        gtk_widget_show(menuBar);
	}
	else {
		// button is inactive
        gtk_widget_hide(menuBar);
	}
}