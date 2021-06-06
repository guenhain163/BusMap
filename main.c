/* GTK definitions */
#define _GNU_SOURCE
#include <gtk-3.0/gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "sqlite3.h"

typedef struct userData
{
    int B_ID;
    char B_user[1000];
    char B_pass[1000];
    char B_email[1000];
    char B_name[1000];
}USERDATA;

// Make them global
USERDATA UserData;
static gint timer = 0;

GtkWidget  *window;
GtkBuilder *builder;

GtkWidget  *buttonState;
GtkWidget  *topPage;
GtkWidget  *menuBar;
GtkWidget  *menuBar_name;
GtkWidget  *menuBar_email;

GtkWidget  *sw_noti;
GtkWidget  *sw_util;
GtkWidget  *sw_feed;

GtkWidget  *stackNoti;
GtkWidget  *stackUtil;
GtkWidget  *stackFeed;
GtkWidget  *stackMain;
GtkWidget  *stackIntro;
GtkWidget  *stackLogin;

GtkWidget  *bt_avt_home;
GtkWidget  *bt_avt_info;
GtkWidget  *bt_noti;
GtkWidget  *bt_sett;
GtkWidget  *bt_search;
GtkWidget  *bt_edit;
GtkWidget  *bt_add;
GtkWidget  *bt_feedback;
GtkWidget  *bt_evaluate;
GtkWidget  *bt_appinfo;
GtkWidget  *bt_close;
GtkWidget  *bt_login_intro;
GtkWidget  *bt_signup_intro;
GtkWidget  *bt_forgot_login;
GtkWidget  *bt_return;
GtkWidget  *bt_return_main;
GtkWidget  *bt_logout;

GtkWidget  *pg_main;
GtkWidget  *pg_editInfo;
GtkWidget  *pg_noti;
GtkWidget  *pg_sett;
GtkWidget  *pg_search;
GtkWidget  *pg_edit;
GtkWidget  *pg_add;
GtkWidget  *pg_feedback;
GtkWidget  *pg_evaluate;
GtkWidget  *pg_appinfo;
GtkWidget  *pg_intro;
GtkWidget  *pg_login_signup;
GtkWidget  *pg_login;
GtkWidget  *pg_signup;
GtkWidget  *pg_wellcome;
GtkWidget  *pg_forgot;

GtkWidget  *login_user;
GtkWidget  *login_pass;
GtkWidget  *login_error;
GtkWidget  *login_error;
GtkWidget  *pg_wcl_name;

GtkWidget  *signup_user;
GtkWidget  *signup_pass;
GtkWidget  *signup_repass;
GtkWidget  *signup_email;
GtkWidget  *signup_error;

// Page Search
GtkWidget  *s_search;
GtkWidget  *s_btn_search;
GtkTreeView  *s_table;
GtkListStore  *list_search;
GtkLayout  *s_layout;

GtkWidget  *fixed1;
GtkWidget  *fixed4;

static void load_css(void);
static int callback(void *NotUsed, int argc, char **argv, char **azColName);
int statusLogin();
int checkLogin();
int load_main();
void load_data();

/* Main program */
int main(int argc, char *argv[])
{

    gtk_init (&argc, &argv); // init Gtk

//------------------------------------------------------------------------
// Establish contact with sml code used to adjust widget settings
//------------------------------------------------------------------------

    /* Load the Glade window description.  */
    builder = gtk_builder_new();
    gtk_builder_add_from_file (builder, "window_main_1.glade", NULL);

    window = GTK_WIDGET(gtk_builder_get_object(builder, "window_main"));

    buttonState = GTK_WIDGET(gtk_builder_get_object(builder, "buttonState"));
    topPage = GTK_WIDGET(gtk_builder_get_object(builder, "topPage"));
    menuBar = GTK_WIDGET(gtk_builder_get_object(builder, "menuBar"));
    menuBar_name = GTK_WIDGET(gtk_builder_get_object(builder, "menuBar_name"));
    menuBar_email = GTK_WIDGET(gtk_builder_get_object(builder, "menuBar_email"));

    sw_noti = GTK_WIDGET(gtk_builder_get_object(builder, "sw_noti"));
    sw_util = GTK_WIDGET(gtk_builder_get_object(builder, "sw_util"));
    sw_feed = GTK_WIDGET(gtk_builder_get_object(builder, "sw_feed"));

    stackNoti = GTK_WIDGET(gtk_builder_get_object(builder, "stackNoti"));
    stackUtil = GTK_WIDGET(gtk_builder_get_object(builder, "stackUtil"));
    stackFeed = GTK_WIDGET(gtk_builder_get_object(builder, "stackFeed"));
    stackMain = GTK_WIDGET(gtk_builder_get_object(builder, "stackMain"));
    stackIntro = GTK_WIDGET(gtk_builder_get_object(builder, "stackIntro"));
    stackLogin = GTK_WIDGET(gtk_builder_get_object(builder, "stackLogin"));

    bt_avt_info = GTK_WIDGET(gtk_builder_get_object(builder, "bt_avt_info"));
    bt_close = GTK_WIDGET(gtk_builder_get_object(builder, "bt_close"));
    bt_avt_home = GTK_WIDGET(gtk_builder_get_object(builder, "bt_avt_home"));
    bt_noti = GTK_WIDGET(gtk_builder_get_object(builder, "bt_noti"));
    bt_sett = GTK_WIDGET(gtk_builder_get_object(builder, "bt_sett"));
    bt_search = GTK_WIDGET(gtk_builder_get_object(builder, "bt_search"));
    bt_edit = GTK_WIDGET(gtk_builder_get_object(builder, "bt_edit"));
    bt_add = GTK_WIDGET(gtk_builder_get_object(builder, "bt_add"));
    bt_feedback = GTK_WIDGET(gtk_builder_get_object(builder, "bt_feedback"));
    bt_evaluate = GTK_WIDGET(gtk_builder_get_object(builder, "bt_evaluate"));
    bt_appinfo = GTK_WIDGET(gtk_builder_get_object(builder, "bt_appinfo"));
    bt_login_intro = GTK_WIDGET(gtk_builder_get_object(builder, "bt_login_intro"));
    bt_signup_intro = GTK_WIDGET(gtk_builder_get_object(builder, "bt_signup_intro"));
    bt_forgot_login = GTK_WIDGET(gtk_builder_get_object(builder, "bt_forgot_login"));
    bt_return = GTK_WIDGET(gtk_builder_get_object(builder, "bt_return"));
    bt_return_main = GTK_WIDGET(gtk_builder_get_object(builder, "bt_return_main"));
    bt_logout = GTK_WIDGET(gtk_builder_get_object(builder, "bt_logout"));

    pg_main = GTK_WIDGET(gtk_builder_get_object(builder, "pg_main"));
    pg_editInfo = GTK_WIDGET(gtk_builder_get_object(builder, "pg_editInfo"));
    pg_noti = GTK_WIDGET(gtk_builder_get_object(builder, "pg_noti"));
    pg_sett = GTK_WIDGET(gtk_builder_get_object(builder, "pg_sett"));
    pg_search = GTK_WIDGET(gtk_builder_get_object(builder, "pg_search"));
    pg_edit = GTK_WIDGET(gtk_builder_get_object(builder, "pg_edit"));
    pg_add = GTK_WIDGET(gtk_builder_get_object(builder, "pg_add"));
    pg_feedback = GTK_WIDGET(gtk_builder_get_object(builder, "pg_feedback"));
    pg_evaluate = GTK_WIDGET(gtk_builder_get_object(builder, "pg_evaluate"));
    pg_appinfo = GTK_WIDGET(gtk_builder_get_object(builder, "pg_appinfo"));
    pg_intro = GTK_WIDGET(gtk_builder_get_object(builder, "pg_intro"));
    pg_login_signup = GTK_WIDGET(gtk_builder_get_object(builder, "pg_login_signup"));
    pg_login = GTK_WIDGET(gtk_builder_get_object(builder, "pg_login"));
    pg_signup = GTK_WIDGET(gtk_builder_get_object(builder, "pg_signup"));
    pg_wellcome = GTK_WIDGET(gtk_builder_get_object(builder, "pg_wellcome"));
    pg_forgot = GTK_WIDGET(gtk_builder_get_object(builder, "pg_forgot"));

    // Page signin
    login_user = GTK_WIDGET(gtk_builder_get_object(builder, "login_user"));
    login_pass = GTK_WIDGET(gtk_builder_get_object(builder, "login_pass"));
    login_error = GTK_WIDGET(gtk_builder_get_object(builder, "login_error"));
    login_error = GTK_WIDGET(gtk_builder_get_object(builder, "login_error"));
    pg_wcl_name = GTK_WIDGET(gtk_builder_get_object(builder, "pg_wcl_name"));

    // Page signup
    signup_user =  GTK_WIDGET(gtk_builder_get_object(builder, "signup_user"));
    signup_pass =  GTK_WIDGET(gtk_builder_get_object(builder, "signup_pass"));
    signup_repass =  GTK_WIDGET(gtk_builder_get_object(builder, "signup_repass"));
    signup_email =  GTK_WIDGET(gtk_builder_get_object(builder, "signup_email"));
    signup_error =  GTK_WIDGET(gtk_builder_get_object(builder, "signup_error"));

    // Page search
    s_search = GTK_WIDGET(gtk_builder_get_object(builder, "s_search"));
    s_btn_search = GTK_WIDGET(gtk_builder_get_object(builder, "s_btn_search"));
    s_table = GTK_TREE_VIEW(gtk_builder_get_object(builder, "s_table"));
    list_search = GTK_LIST_STORE(gtk_builder_get_object(builder, "list_search"));
    s_layout = GTK_LAYOUT(gtk_builder_get_object(builder, "s_layout"));

    // Screen
    fixed1 = GTK_WIDGET(gtk_builder_get_object(builder, "fixed1"));
    fixed4 = GTK_WIDGET(gtk_builder_get_object(builder, "fixed4"));

    load_css(); // Load file css

    gtk_builder_connect_signals(builder, NULL);
    g_object_unref(builder);

    
    gtk_widget_hide(bt_logout);
    gtk_widget_hide(topPage);
    gtk_widget_hide(menuBar); // Hide the menuBar
    gtk_widget_hide(bt_close);
    gtk_widget_hide(stackNoti);
    gtk_widget_hide(stackUtil);
    gtk_widget_hide(stackFeed);
    gtk_widget_hide(stackLogin);
    gtk_widget_hide(fixed1);
    

    gtk_widget_show(window); // Show the window

    timer = g_timeout_add(2000, checkLogin, NULL);

    gtk_main(); //Run the event loop

    /* We have quit.  Free storage and exit. */
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    g_slice_free(GtkWidget, window);

    return EXIT_SUCCESS;
}

void load_data()
{
    if (strcmp(UserData.B_user, "") != 0 && UserData.B_ID > 0)
    {
        //printf("ID = %d\nUsername = %s\nPassword = %s\nEmail = %s\nName = %s\n", UserData.B_ID, UserData.B_user, UserData.B_pass, UserData.B_email, UserData.B_name);
        gtk_label_set_text(GTK_LABEL(menuBar_name), (const gchar *)(UserData.B_name));
        gtk_label_set_text(GTK_LABEL(menuBar_email), (const gchar *)(UserData.B_email));
    }
    else
    {
        checkLogin();
    }
}

/* When the window is closed, the application exits.  */
void on_window_main_destroy()
{
    gtk_main_quit();
}

static void load_css(void) {
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
    gtk_widget_show(stackMain);
    gtk_stack_set_visible_child(GTK_STACK(stackMain), pg_main);
}

void on_bt_avt_info_clicked()
{
    gtk_widget_hide(menuBar);
    gtk_widget_hide(bt_close);
    gtk_widget_hide(stackUtil);
    gtk_widget_hide(stackFeed);
    gtk_widget_hide(stackNoti);
    gtk_widget_show(stackMain);
    gtk_widget_show(topPage);
    gtk_widget_show(bt_logout);
    gtk_stack_set_visible_child(GTK_STACK(stackMain), pg_editInfo);
}

void on_bt_noti_clicked ()
{
    gtk_widget_hide(menuBar);
    gtk_widget_hide(bt_close);
    gtk_widget_hide(stackMain);
    gtk_widget_hide(stackUtil);
    gtk_widget_hide(stackFeed);
    gtk_widget_show(topPage);
    gtk_widget_show(stackNoti);
    gtk_stack_set_visible_child(GTK_STACK(stackNoti), pg_noti);
}

void on_bt_sett_clicked ()
{
    gtk_widget_hide(menuBar);
    gtk_widget_hide(bt_close);
    gtk_widget_hide(stackMain);
    gtk_widget_hide(stackUtil);
    gtk_widget_hide(stackFeed);
    gtk_widget_show(topPage);
    gtk_widget_show(stackNoti);
    gtk_stack_set_visible_child(GTK_STACK(stackNoti), pg_sett);
}

void on_bt_search_clicked ()
{
    gtk_widget_hide(menuBar);
    gtk_widget_hide(bt_close);
    gtk_widget_hide(stackMain);
    gtk_widget_hide(stackNoti);
    gtk_widget_hide(stackFeed);
    gtk_widget_show(topPage);
    gtk_widget_show(stackUtil);
    gtk_stack_set_visible_child(GTK_STACK(stackUtil), pg_search);
}

void on_bt_edit_clicked ()
{
    gtk_widget_hide(menuBar);
    gtk_widget_hide(bt_close);
    gtk_widget_hide(stackMain);
    gtk_widget_hide(stackNoti);
    gtk_widget_hide(stackFeed);
    gtk_widget_show(topPage);
    gtk_widget_show(stackUtil);
    gtk_stack_set_visible_child(GTK_STACK(stackUtil), pg_edit);
}

void on_bt_add_clicked ()
{
    gtk_widget_hide(menuBar);
    gtk_widget_hide(bt_close);
    gtk_widget_hide(stackMain);
    gtk_widget_hide(stackNoti);
    gtk_widget_hide(stackFeed);
    gtk_widget_show(topPage);
    gtk_widget_show(stackUtil);
    gtk_stack_set_visible_child(GTK_STACK(stackUtil), pg_add);
}

void on_bt_feedback_clicked ()
{
    gtk_widget_hide(menuBar);
    gtk_widget_hide(bt_close);
    gtk_widget_hide(stackMain);
    gtk_widget_hide(stackUtil);
    gtk_widget_hide(stackNoti);
    gtk_widget_show(topPage);
    gtk_widget_show(stackFeed);
    gtk_stack_set_visible_child(GTK_STACK(stackFeed), pg_feedback);
}

void on_bt_appinfo_clicked ()
{
    gtk_widget_hide(menuBar);
    gtk_widget_hide(bt_close);
    gtk_widget_hide(stackMain);
    gtk_widget_hide(stackUtil);
    gtk_widget_hide(stackNoti);
    gtk_widget_show(topPage);
    gtk_widget_show(stackFeed);
    gtk_stack_set_visible_child(GTK_STACK(stackFeed), pg_appinfo);
}

void on_bt_evaluate_clicked ()
{
    gtk_widget_hide(menuBar);
    gtk_widget_hide(bt_close);
    gtk_widget_hide(stackMain);
    gtk_widget_hide(stackUtil);
    gtk_widget_hide(stackNoti);
    gtk_widget_show(topPage);
    gtk_widget_show(stackFeed);
    gtk_stack_set_visible_child(GTK_STACK(stackFeed), pg_evaluate);
}

void on_bt_return_main_clicked()
{
    gtk_widget_hide(menuBar);
    gtk_widget_hide(bt_close);
    gtk_widget_hide(stackMain);
    gtk_widget_hide(stackUtil);
    gtk_widget_hide(stackNoti);
    gtk_widget_hide(stackFeed);
    gtk_widget_hide(topPage);
    gtk_widget_hide(bt_logout);
    gtk_widget_show(stackMain);
    gtk_stack_set_visible_child(GTK_STACK(stackMain), pg_main);
}

void on_bt_logout_clicked()
{    
    FILE *f = fopen("session.txt", "w");
    if(!f)
        printf("Error!");
    else
        printf("Logout successfully.\n\n");
    fclose(f);
    
    on_window_main_destroy();
}

static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
    NotUsed = 0;
    // for(int i = 0; i < argc; i++){
    //     printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    // }
    // printf("\n");

    if(argc <= 5)
    {
        UserData.B_ID = (int)(*argv[0]) - 48;
        strcpy(UserData.B_user, argv[1] ? argv[1] : "NULL");
        strcpy(UserData.B_pass, argv[2] ? argv[2] : "NULL");
        strcpy(UserData.B_email, argv[3] ? argv[3] : "NULL");
        strcpy(UserData.B_name, argv[4] ? argv[4] : "NULL");
    }

    return 0;
}

int statusLogin()
{
    char pass[1000], *sql, *zErrMsg = 0;
    int ID, rc;
    sqlite3 *db;
    FILE *f = fopen("session.txt", "r");

    if (f == NULL)
    {
        return 0;
    }
    else
    {
        fscanf(f, "%d%*c\n", &ID);
        fscanf(f, "%s%*c\n", pass);
    }

    fclose(f);

    if(ID == 0 || !pass)
        return 0;

    /* Open database */
    rc = sqlite3_open("bus.db", &db);
    if(rc){
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 0;
    }
    else
    {
        fprintf(stderr, "Opened database successfully\n");
    }

    /* Create SQL statement */
    asprintf(&sql, "SELECT * FROM User WHERE (ID = '%d') AND (Password = '%s')", ID, pass);
    
    /* Execute SQL statement */
    rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
    if (rc != SQLITE_OK){
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        sqlite3_close(db);
        return 0;
    }

    sqlite3_close(db);

    if (strcmp(UserData.B_user, "") == 0 || UserData.B_ID <= 0)
        return 0;
    else
        return 1;
}

int checkLogin()
{
    int n = statusLogin();
    if (n == 0 || UserData.B_ID <= 0)
    {
        g_source_remove(timer);
        gtk_widget_hide(stackIntro);
        gtk_widget_show(stackLogin);
        gtk_stack_set_visible_child(GTK_STACK(stackLogin), pg_login_signup);
    }
    else
    {
        load_main();
    }

    return 1;
}

void on_bt_login_intro_clicked ()
{
    gtk_stack_set_visible_child(GTK_STACK(stackLogin), pg_login);
    gtk_widget_hide(pg_login_signup);
}

void on_bt_signup_intro_clicked ()
{
    gtk_stack_set_visible_child(GTK_STACK(stackLogin), pg_signup);
    gtk_widget_hide(pg_login_signup);
}

void on_bt_signup_login_clicked ()
{    
    gtk_stack_set_visible_child(GTK_STACK(stackLogin), pg_signup);
}

void on_bt_login_signup_clicked ()
{
    gtk_stack_set_visible_child(GTK_STACK(stackLogin), pg_login);
}

void on_bt_forgot_login_clicked ()
{
    gtk_stack_set_visible_child(GTK_STACK(stackLogin), pg_forgot);
}

void on_bt_return_clicked ()
{
    gtk_widget_show(pg_login_signup);
    gtk_stack_set_visible_child(GTK_STACK(stackLogin), pg_login_signup);
}

/* Login function checks */
void on_bt_login_clicked ()
{
    char user[1000], pass[100];

    strcpy(user, gtk_entry_get_text(GTK_ENTRY(login_user))); // Get the data from the username box
    strcpy(pass, gtk_entry_get_text(GTK_ENTRY(login_pass))); // Get the data from the password box


    if(strcmp(user, "") == 0 || strcmp(pass, "") == 0) // In case you do not enter an account or password
    {
        gtk_label_set_text(GTK_LABEL(login_error), "Enter your username and password.");
    }
    else
    {
        char *sql, *zErrMsg = 0;
        int rc;
        sqlite3 *db;

        /* Open file */
        FILE *f = fopen("session.txt", "w");
        if (f == NULL) // If error
        {
            fprintf(stderr, "Can't open File!\n");
        }

        /* Open database */
        rc = sqlite3_open("bus.db", &db);
        if (rc) // If error
        {
            fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        }

        /* Create SQL statement */
        asprintf(&sql, "SELECT * FROM User WHERE (Username = '%s') AND (Password = '%s')", user, pass);
        
        /* Execute SQL statement */
        rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
        if (rc != SQLITE_OK)
        {
            sqlite3_free(zErrMsg);
            sqlite3_close(db);
        }

        /* If the login is successful, go to the main screen, otherwise the error will be reported */
        if(UserData.B_ID <= 0) // Error
        {
            gtk_label_set_text(GTK_LABEL(login_error), "Username or password is incorrect.");
        }
        else // Successful
        {
            fprintf(f, "%d\n%s", UserData.B_ID, UserData.B_pass);
            gtk_label_set_text(GTK_LABEL(pg_wcl_name), (const gchar*)(UserData.B_name));
            gtk_stack_set_visible_child(GTK_STACK(stackLogin), pg_wellcome);
            timer = g_timeout_add(2000, load_main, NULL);
        }
        
        sqlite3_close(db);
        fclose(f);
    }
}

int load_main()
{
    gtk_widget_hide(fixed4);
    gtk_widget_show(fixed1);
    load_data();
    g_source_remove(timer);
    return 1;
}

void on_bt_signup_clicked()
{
    char su_user[100], su_pass[100], su_repass[100], su_email[100];

    gtk_label_set_text(GTK_LABEL(signup_error), "");
    strcpy(su_user, gtk_entry_get_text(GTK_ENTRY(signup_user)));
    strcpy(su_pass, gtk_entry_get_text(GTK_ENTRY(signup_pass)));
    strcpy(su_repass, gtk_entry_get_text(GTK_ENTRY(signup_repass)));
    strcpy(su_email, gtk_entry_get_text(GTK_ENTRY(signup_email)));

    if(strcmp(su_user, "") == 0 || strcmp(su_pass, "") == 0 || strcmp(su_repass, "") == 0 || strcmp(su_email, "") == 0)
    {
        gtk_label_set_text(GTK_LABEL(signup_error), "Please fill in the required information.");
    }
    else
    if (strcmp(su_pass, su_repass) != 0)
    {
        gtk_label_set_text(GTK_LABEL(signup_error), "The password confirmation does not match.");
    }
    else
    {
        char *sql, *zErrMsg = 0;
        int rc;
        sqlite3 *db;

        /* Open database */
        rc = sqlite3_open("bus.db", &db);
        if (rc) // If error
        {
            fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
            exit(0);
        }

        /* Create SQL statement */
        asprintf(&sql, "SELECT * FROM User WHERE (Username = '%s')", su_user);
        
        /* Execute SQL statement */
        rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
        if (rc != SQLITE_OK)
        {
            fprintf(stderr, "Failed to select data\n");
            fprintf(stderr, "SQL error: %s\n", zErrMsg);
            sqlite3_free(zErrMsg);
            sqlite3_close(db);
            exit(0);
        }

        if(strcmp(UserData.B_user, "") != 0 && UserData.B_ID > 0)
        {
            gtk_label_set_text(GTK_LABEL(signup_error), "Username already exists.");
        }
        else
        {
            /* Open file */
            FILE *f = fopen("session.txt", "w");
            if (f == NULL) // If error
            {
                fprintf(stderr, "Can't open File!\n");
            }

            asprintf(&sql, "INSERT INTO User(Username, Password, Email, Name)" \
                "VALUES('%s', '%s', '%s', 'Guy');", su_user, su_pass, su_email);
            
            rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
            if (rc != SQLITE_OK)
            {
                fprintf(stderr, "Failed to select data\n");
                fprintf(stderr, "SQL error: %s\n", zErrMsg);
                sqlite3_free(zErrMsg);
                sqlite3_close(db);
                fclose(f);
                exit(0);
            }
            
            /* Create SQL statement */
            asprintf(&sql, "SELECT * FROM User WHERE (Username = '%s') AND (Password = '%s')", su_user, su_pass);
            
            /* Execute SQL statement */
            rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
            if (rc != SQLITE_OK)
            {
                fprintf(stderr, "Failed to select data\n");
                fprintf(stderr, "SQL error: %s\n", zErrMsg);
                sqlite3_free(zErrMsg);
                sqlite3_close(db);
                fclose(f);
                exit(0);
            }

            fprintf(f, "%d\n%s", UserData.B_ID, UserData.B_pass);
            gtk_label_set_text(GTK_LABEL(pg_wcl_name), (const gchar *)(UserData.B_name));
            gtk_stack_set_visible_child(GTK_STACK(stackLogin), pg_wellcome);
            timer = g_timeout_add(2000, load_main, NULL);
            
            fclose(f);
        }
        
        sqlite3_close(db);
    }
}


// PAGE SEARCH

int callback_table (void *model, int argc, char **argv, char **azColName){
    GtkTreeIter iter;
    
    // Print to Terminal Screen
    // int i = 0;
    // for(i; i < argc; i++)
    // {
    //     printf("%s = %s", azColName[i], argv[i] ? argv[i] : "NULL");
    // }

    // Add data to Liststore
    
    gtk_list_store_append(GTK_LIST_STORE(model), &iter);
    gtk_list_store_set(GTK_LIST_STORE(model), &iter, 0, argv[0], 1, argv[1], 2, argv[2], 3, argv[3], 4, argv[4], 5, argv[5], 6, argv[6], -1);
}

void on_s_search_icon_press (){
    gtk_entry_set_text(GTK_ENTRY(s_search), "");
}

void on_s_search_insert_text (){
    gtk_entry_set_icon_from_icon_name(GTK_ENTRY(s_search), GTK_ENTRY_ICON_SECONDARY, "edit-clear-symbolic");
    gtk_entry_set_icon_sensitive(GTK_ENTRY(s_search), GTK_ENTRY_ICON_SECONDARY, TRUE);
    gtk_entry_set_icon_activatable(GTK_ENTRY(s_search), GTK_ENTRY_ICON_SECONDARY, TRUE);
}

void on_s_btn_search_clicked (){
    char str[250];

    strcpy(str, gtk_entry_get_text(GTK_ENTRY(s_search)));

    if(strcmp(str, "") != 0)
    {
        char *sql, *zErrMsg = 0, s[1000];
        int rc;

        sqlite3 *db;

        /* Open database */
        rc = sqlite3_open("bus.db", &db);
        if (rc) // If error
        {
            fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
            exit(0);
        }

        strcpy(s, "%%");
        strcat(s, str);
        strcat(s, "%%");

        gtk_list_store_clear(list_search);
        // gtk_layout_set_size(s_layout, 1180, 80);
        /* Create SQL statement */
        asprintf(&sql, "SELECT ROW_NUMBER() OVER(ORDER BY ID), BusCode, RunTime, FirstStation, LastStation, Frequency, Fare FROM BusInfo WHERE BusCode LIKE '%s' OR FirstStation LIKE '%s' OR LastStation LIKE '%s'", s, s, s);
        
        /* Execute SQL statement */
        rc = sqlite3_exec(db, sql, callback_table, list_search, &zErrMsg);
        if (rc != SQLITE_OK)
        {
            fprintf(stderr, "Failed to select data\n");
            fprintf(stderr, "SQL error: %s\n", zErrMsg);
            sqlite3_free(zErrMsg);
            sqlite3_close(db);
            return;
        }

        //Set height Layout
        int rows = gtk_tree_model_iter_n_children(GTK_TREE_MODEL(list_search), NULL);
        gtk_layout_set_size(s_layout, 1180, 40 * rows + 10);
    }
}
