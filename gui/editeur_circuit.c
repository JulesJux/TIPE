#include "editeur_circuit.h"

static void
activate(GtkApplication *app,
         gpointer user_data) {
    GtkBuilder* builder = gtk_builder_new();
    gtk_builder_add_from_file(builder, "editeur_circuit.ui", NULL);

    GObject* window = gtk_builder_get_object(builder, "window");
    gtk_window_set_title(GTK_WINDOW(window), "TIPE");
    gtk_window_set_application(GTK_WINDOW(window), app);
    gtk_window_set_default_size(GTK_WINDOW(window), 1920, 1080);

    GObject *resistance_image = gtk_builder_get_object(builder, "resistance_img");
    gtk_image_set_pixel_size((GtkImage*) resistance_image, 200);
    GObject *condensateur_image = gtk_builder_get_object(builder, "cond_img");
    gtk_image_set_pixel_size((GtkImage*) condensateur_image, 200);

    GObject *drop_grid = gtk_builder_get_object(builder, "drop_grid");

    // TODO : https://www.youtube.com/watch?v=u4YoV-hHu-k&list=PLX7apYUne7u5iHBqNPhSVF1kDJSJshtUD&index=32

    gtk_widget_set_visible(GTK_WIDGET(window), TRUE);
    g_object_unref(builder);
}


int main(int argc, char **argv) {
    GtkApplication* app = gtk_application_new("org.gtk.example", G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
    int status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);

    return status;
}
