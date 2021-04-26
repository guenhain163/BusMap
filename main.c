#include <stdlib.h>
#include <gtk-3.0/gtk/gtk.h>

// called when window is closed
// void on_window_main_destroy()
// {
//     gtk_main_quit();
// }

// Make them global

GtkWidget  *window;
GtkWidget  *fixed1;
GtkWidget  *togglebutton;
GtkWidget  *sw_page;
GtkWidget  *fixed2;
GtkWidget  *stack1;
GtkBuilder *builder;

int main(int argc, char *argv[])
{
    gtk_init (&argc, &argv); // init Gtk
    
//------------------------------------------------------------------------
// Establish contact with sml code used to adjust widget settings
//------------------------------------------------------------------------

    builder = gtk_builder_new();
    gtk_builder_add_from_file (builder, "window_main.glade", NULL);

    window = GTK_WIDGET(gtk_builder_get_object(builder, "window_main"));

    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    gtk_builder_connect_signals(builder, NULL);

    fixed1 = GTK_WIDGET(gtk_builder_get_object(builder, "fixed1"));
    togglebutton = GTK_WIDGET(gtk_builder_get_object(builder, "togglebutton"));
    sw_page = GTK_WIDGET(gtk_builder_get_object(builder, "sw_page"));
    fixed2 = GTK_WIDGET(gtk_builder_get_object(builder, "fixed2"));
    stack1 = GTK_WIDGET(gtk_builder_get_object(builder, "stack1"));

    g_object_unref(builder);

    gtk_widget_hide(sw_page);
    gtk_widget_show(window);

    gtk_main();

    return EXIT_SUCCESS;
}

void on_togglebuttonState_toggled (GtkToggleButton *togglebutton, GtkWidget *sw_page)
{
	gboolean button_state;
	
	button_state = gtk_toggle_button_get_active(togglebutton);
	
	if (button_state) {
		// button is active
        gtk_widget_show(sw_page);
	}
	else {
		// button is inactive
        gtk_widget_hide(sw_page);
	}
}
