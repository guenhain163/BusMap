/* GTK definitions */
#include <gtk-3.0/gtk/gtk.h>

// Make them global
GtkWidget  *window;
GtkWidget  *fixed1;
GtkWidget  *buttonState;
GtkWidget  *menuBar;
GtkWidget  *sw_noti;
GtkWidget  *sw_util;
GtkWidget  *sw_feed;
GtkWidget  *fixed2;
GtkWidget  *stackNoti;
GtkWidget  *stackUtil;
GtkWidget  *stackFeed;
GtkWidget  *bt_avt_home;
GtkWidget  *bt_noti;
GtkWidget  *bt_search;
GtkWidget  *bt_find;
GtkWidget  *bt_feedback;
GtkWidget  *bt_evaluate;
GtkWidget  *bt_appinfo;
GtkWidget  *bt_avt_info;
GtkWidget  *bt_close;
GtkWidget  *pg_main;
GtkWidget  *pg_noti;
GtkWidget  *pg_search;
GtkWidget  *pg_find;
GtkWidget  *pg_feedback;
GtkWidget  *pg_evaluate;
GtkWidget  *pg_appinfo;
GtkBuilder *builder;


static void load_css(void){
    GtkCssProvider *provider;
    GdkDisplay *display;
    GdkScreen *screen;

    const gchar *css_style_file = "gtk-bright.css";
    GFile *css_fp = g_file_new_for_path(css_style_file);
    GError *error = 0;

    provider = gtk_css_provider_new();
    display = gdk_display_get_default();
   screen = gdk_display_get_default_screen(display);

    gtk_style_context_add_provider_for_screen(screen,
        GTK_STYLE_PROVIDER(provider),GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
    gtk_css_provider_load_from_file(provider,css_fp,&error);
    g_object_unref(provider);
}

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
    buttonState = GTK_WIDGET(gtk_builder_get_object(builder, "buttonState"));
    menuBar = GTK_WIDGET(gtk_builder_get_object(builder, "menuBar"));
    fixed2 = GTK_WIDGET(gtk_builder_get_object(builder, "fixed2"));

    sw_noti = GTK_WIDGET(gtk_builder_get_object(builder, "sw_noti"));
    sw_util = GTK_WIDGET(gtk_builder_get_object(builder, "sw_util"));
    sw_feed = GTK_WIDGET(gtk_builder_get_object(builder, "sw_feed"));

    stackNoti = GTK_WIDGET(gtk_builder_get_object(builder, "stackNoti"));
    stackUtil = GTK_WIDGET(gtk_builder_get_object(builder, "stackUtil"));
    stackFeed = GTK_WIDGET(gtk_builder_get_object(builder, "stackFeed"));

    bt_noti = GTK_WIDGET(gtk_builder_get_object(builder, "bt_noti"));
    bt_search = GTK_WIDGET(gtk_builder_get_object(builder, "bt_search"));
    bt_find = GTK_WIDGET(gtk_builder_get_object(builder, "bt_find"));
    bt_feedback = GTK_WIDGET(gtk_builder_get_object(builder, "bt_feedback"));
    bt_evaluate = GTK_WIDGET(gtk_builder_get_object(builder, "bt_evaluate"));
    bt_appinfo = GTK_WIDGET(gtk_builder_get_object(builder, "bt_appinfo"));

    pg_main = GTK_WIDGET(gtk_builder_get_object(builder, "pg_main"));
    pg_noti = GTK_WIDGET(gtk_builder_get_object(builder, "pg_noti"));
    pg_search = GTK_WIDGET(gtk_builder_get_object(builder, "pg_search"));
    pg_find = GTK_WIDGET(gtk_builder_get_object(builder, "pg_find"));
    pg_feedback = GTK_WIDGET(gtk_builder_get_object(builder, "pg_feedback"));
    pg_evaluate = GTK_WIDGET(gtk_builder_get_object(builder, "pg_evaluate"));
    pg_appinfo = GTK_WIDGET(gtk_builder_get_object(builder, "pg_appinfo"));

    bt_avt_info = GTK_WIDGET(gtk_builder_get_object(builder, "bt_avt_info"));
    bt_close = GTK_WIDGET(gtk_builder_get_object(builder, "bt_close"));
    bt_avt_home = GTK_WIDGET(gtk_builder_get_object(builder, "bt_avt_home"));

    load_css(); // Load file css

    gtk_builder_connect_signals(builder, NULL);
    g_object_unref(builder);

    gtk_widget_hide(menuBar); // Hide the menuBar
    gtk_widget_hide(bt_close);
    gtk_widget_hide(stackNoti);
    gtk_widget_hide(stackUtil);
    gtk_widget_hide(stackFeed);
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

/* When you clicked the button, the menu bar shows or hides. */
void on_buttonState_clicked (GtkWidget *buttonState, GtkWidget *menuBar)
{
    gtk_widget_show(menuBar);
    gtk_widget_show(bt_close);
}

void on_bt_close_clicked (GtkWidget *bt_close)
{
    gtk_widget_hide(bt_close);
    gtk_widget_hide(menuBar);
}

void on_bt_avt_home_clicked()
{
    gtk_widget_hide(menuBar);
    gtk_widget_hide(bt_close);
    gtk_widget_hide(stackUtil);
    gtk_widget_hide(stackFeed);
    gtk_widget_hide(stackNoti);
    gtk_widget_show(pg_main);
}

void on_bt_noti_clicked ()
{
    gtk_widget_hide(menuBar);
    gtk_widget_hide(bt_close);
    gtk_widget_hide(pg_main);
    gtk_widget_hide(stackUtil);
    gtk_widget_hide(stackFeed);
    gtk_widget_show(stackNoti);
    gtk_stack_set_visible_child(GTK_STACK(stackNoti), pg_noti);
}

void on_bt_search_clicked ()
{
    gtk_widget_hide(menuBar);
    gtk_widget_hide(bt_close);
    gtk_widget_hide(pg_main);
    gtk_widget_hide(stackNoti);
    gtk_widget_hide(stackFeed);
    gtk_widget_show(stackUtil);
    gtk_stack_set_visible_child(GTK_STACK(stackUtil), pg_search);
}

void on_bt_find_clicked ()
{
    gtk_widget_hide(menuBar);
    gtk_widget_hide(bt_close);
    gtk_widget_hide(pg_main);
    gtk_widget_hide(stackNoti);
    gtk_widget_hide(stackFeed);
    gtk_widget_show(stackUtil);
    gtk_stack_set_visible_child(GTK_STACK(stackUtil), pg_find);
}

void on_bt_feedback_clicked ()
{
    gtk_widget_hide(menuBar);
    gtk_widget_hide(bt_close);
    gtk_widget_hide(pg_main);
    gtk_widget_hide(stackUtil);
    gtk_widget_hide(stackNoti);
    gtk_widget_show(stackFeed);
    gtk_stack_set_visible_child(GTK_STACK(stackFeed), pg_feedback);
}

void on_bt_appinfo_clicked ()
{
    gtk_widget_hide(menuBar);
    gtk_widget_hide(bt_close);
    gtk_widget_hide(pg_main);
    gtk_widget_hide(stackUtil);
    gtk_widget_hide(stackNoti);
    gtk_widget_show(stackFeed);
    gtk_stack_set_visible_child(GTK_STACK(stackFeed), pg_appinfo);
}

void on_bt_evaluate_clicked ()
{
    gtk_widget_hide(menuBar);
    gtk_widget_hide(bt_close);
    gtk_widget_hide(pg_main);
    gtk_widget_hide(stackUtil);
    gtk_widget_hide(stackNoti);
    gtk_widget_show(stackFeed);
    gtk_stack_set_visible_child(GTK_STACK(stackFeed), pg_evaluate);
}

