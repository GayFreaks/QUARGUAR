#include <cairo.h>
#include <gtk/gtk.h>
#include <string>
#include <iostream>
#include <sstream>
#include "qrcodegen.hpp"

static std::string toSvgString(const qrcodegen::QrCode &qr, int border) {
	if (border < 0)
		throw std::domain_error("Border must be non-negative");
	if (border > INT_MAX / 2 || border * 2 > INT_MAX - qr.getSize())
		throw std::overflow_error("Border too large");
	
	std::ostringstream sb;
	sb << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
	sb << "<!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 1.1//EN\" \"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\">\n";
	sb << "<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\" viewBox=\"0 0 ";
	sb << (qr.getSize() + border * 2) << " " << (qr.getSize() + border * 2) << "\" stroke=\"none\">\n";
	sb << "\t<rect width=\"100%\" height=\"100%\" fill=\"#FFFFFF\"/>\n";
	sb << "\t<path d=\"";
	for (int y = 0; y < qr.getSize(); y++) {
		for (int x = 0; x < qr.getSize(); x++) {
			if (qr.getModule(x, y)) {
				if (x != 0 || y != 0)
					sb << " ";
				sb << "M" << (x + border) << "," << (y + border) << "h1v1h-1z";
			}
		}
	}
	sb << "\" fill=\"#000000\"/>\n";
	sb << "</svg>\n";
	return sb.str();
}

static void generate_qr(GtkWidget *widget, gpointer data) {
    qrcodegen::QrCode qr0 = qrcodegen::QrCode::encodeText("Hello, world!", qrcodegen::QrCode::Ecc::MEDIUM);
    std::string svg = toSvgString(qr0, 4);  // See QrCodeGeneratorDemo
    std::cout << svg << "\n";
}

static void save_qr(GtkWidget *widget, gpointer data) {
    g_print ("Hello World\n");
}

static cairo_surface_t *imageSurface;

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

    frame = gtk_image_new_from_surface(imageSurface);
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
