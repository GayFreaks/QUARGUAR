#include <gtk/gtk.h>

static void generate_qr(GtkWidget *widget, gpointer data) {
    g_print ("Hello World\n");
}

static void save_qr(GtkWidget *widget, gpointer data) {
    g_print ("Hello World\n");
}

static void activate (GtkApplication *app, gpointer user_data) {
    GtkWidget *window;
    GtkWidget *h_layout;
    GtkWidget *frame;
    GtkImage *frameImage;
    GtkWidget *v_layout;
    GtkWidget *title;
    GtkWidget *entry;
    GtkEntry *entryEntry;
    GtkWidget *button_box;
    GtkWidget *gen_button;
    GtkWidget *save_button;

    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW (window), "Window");
    gtk_window_set_default_size(GTK_WINDOW (window), 100, 100);
    gtk_window_set_resizable(GTK_WINDOW (window), false);

    h_layout = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);

    // Replace with surface later
    frame = gtk_image_new();
    gtk_widget_set_size_request(frame, 150, 150);

    v_layout = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);

    title = gtk_label_new("Input data below:");

    entry = gtk_entry_new();
    entryEntry = GTK_ENTRY(entry);
    gtk_entry_set_text(entryEntry, "some data");

    button_box = gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL);
    
    save_button = gtk_button_new_with_label("Save");
    g_signal_connect(save_button, "clicked", G_CALLBACK (save_qr), NULL);

    gen_button = gtk_button_new_with_label("Generate");
    g_signal_connect(gen_button, "clicked", G_CALLBACK (generate_qr), NULL);

    gtk_container_add(GTK_CONTAINER (window), h_layout);
    gtk_container_add(GTK_CONTAINER (h_layout), v_layout);
    gtk_container_add(GTK_CONTAINER (h_layout), frame);
    gtk_container_add(GTK_CONTAINER (v_layout), title);
    gtk_container_add(GTK_CONTAINER (v_layout), entry);
    gtk_box_pack_end(GTK_BOX(v_layout), button_box, false, false, 0);
    gtk_container_add(GTK_CONTAINER (button_box), save_button);
    gtk_container_add(GTK_CONTAINER (button_box), gen_button);

    gtk_widget_show_all(window);
}

int main (int argc, char **argv) {
    GtkApplication *app;
    int status;

    app = gtk_application_new("org.gtk.example", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(app, "activate", G_CALLBACK (activate), NULL);
    status = g_application_run(G_APPLICATION (app), argc, argv);
    g_object_unref(app);

    return status;
}
