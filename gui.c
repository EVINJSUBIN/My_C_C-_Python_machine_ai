#include <gtk/gtk.h>

// Callback function to handle the login action
void on_login_clicked(GtkButton *button, gpointer user_data) {
    GtkWidget *username_entry = GTK_WIDGET(user_data);
    const gchar *username = gtk_entry_get_text(GTK_ENTRY(username_entry));
    
    // Here you can add code to verify the username and password
    if (g_strcmp0(username, "admin") == 0) {
        g_print("Login successful!\n");
    } else {
        g_print("Login failed!\n");
    }
}

// Create the login window and form
void activate(GtkApplication *app, gpointer user_data) {
    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *username_label;
    GtkWidget *username_entry;
    GtkWidget *password_label;
    GtkWidget *password_entry;
    GtkWidget *login_button;

    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Login");
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 200);

    grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grid);

    username_label = gtk_label_new("Username:");
    gtk_grid_attach(GTK_GRID(grid), username_label, 0, 0, 1, 1);

    username_entry = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), username_entry, 1, 0, 1, 1);

    password_label = gtk_label_new("Password:");
    gtk_grid_attach(GTK_GRID(grid), password_label, 0, 1, 1, 1);

    password_entry = gtk_entry_new();
    gtk_entry_set_visibility(GTK_ENTRY(password_entry), FALSE);
    gtk_grid_attach(GTK_GRID(grid), password_entry, 1, 1, 1, 1);

    login_button = gtk_button_new_with_label("Login");
    gtk_grid_attach(GTK_GRID(grid), login_button, 1, 2, 1, 1);

    g_signal_connect(login_button, "clicked", G_CALLBACK(on_login_clicked), username_entry);

    gtk_widget_show_all(window);
}

int main(int argc, char **argv) {
    GtkApplication *app;
    int status;

    app = gtk_application_new("com.example.login", G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
    status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);

    return status;
}
