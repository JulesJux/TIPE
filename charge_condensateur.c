#include "charge_condensateur.h"

void charge_cond(gnuplot_ctrl *h, const char *u0, const char *E, const char *R, const char *C) {
    assert(atoi(u0) < atoi(E) && atoi(u0) >= 0 && atoi(E) > 0 && atoi(R) > 0 && atoi(C) >= 0); //TODO : Transformer l'assert en message d'erreur
    char plot_cmd[TAILLE_MAX] = {};
    char xrange_cmd[TAILLE_MAX] = {};
    char xlabel_cmd[TAILLE_MAX] = "set xlabel 't (en secondes)' ";
    char ylabel_cmd[TAILLE_MAX] = "set ylabel 'Uc (en volts)' ";

    strcat(plot_cmd, "plot (");
    strcat(plot_cmd, u0);
    strcat(plot_cmd, "-");
    strcat(plot_cmd, E);
    strcat(plot_cmd, ")*exp(-x/(");
    strcat(plot_cmd, R);
    strcat(plot_cmd, "*");
    strcat(plot_cmd, C);
    strcat(plot_cmd, "))+");
    strcat(plot_cmd, E);
    strcat(plot_cmd, " title '' "); //plot (Uc(0)-E)exp(-x/RC) + E title ""

    strcat(xrange_cmd, "set xrange [0:5*");
    strcat(xrange_cmd, R);
    strcat(xrange_cmd, "*");
    strcat(xrange_cmd, C);
    strcat(xrange_cmd, "]"); //set xrange [0:5*RC]

    gnuplot_setterm(h, "wxt font 'NotoSans,12' ", 720, 480);
    gnuplot_cmd(h, xlabel_cmd);
    gnuplot_cmd(h, ylabel_cmd);
    gnuplot_cmd(h, xrange_cmd);
    gnuplot_cmd(h, plot_cmd); //  TODO : afficher tau
    gnuplot_close(h);
}

static void show_graph(GtkWidget *widget,
                       gpointer data) {
    const datas *d = (datas *) data;
    const gchar *text_gen_tension_entry = gtk_entry_buffer_get_text(d->gen_tension_entry_buffer);
    const gchar *text_capa_entry = gtk_entry_buffer_get_text(d->capa_entry_buffer);
    const gchar *text_res_entry = gtk_entry_buffer_get_text(d->res_entry_buffer);
    const gchar *text_charge_init_entry = gtk_entry_buffer_get_text(d->charge_init_entry_buffer);
   //DEBUG : g_print(text_gen_tension_entry);

    gnuplot_ctrl *h = gnuplot_init();
    charge_cond(h, (char *) text_charge_init_entry, (char *) text_gen_tension_entry, (char *) text_res_entry, (char *) text_capa_entry);
}

static void
activate(GtkApplication *app,
         gpointer user_data) {
    builder = gtk_builder_new();
    gtk_builder_add_from_file(builder, "tipe.ui", NULL);

    window = gtk_builder_get_object(builder, "window");
    gtk_window_set_title(GTK_WINDOW(window), "TIPE");
    gtk_window_set_application(GTK_WINDOW(window), app);
    gtk_window_set_default_size(GTK_WINDOW(window), 1920, 1080);

    button = gtk_builder_get_object(builder, "button1");
    gen_tension_entry_buffer = gtk_builder_get_object(builder, "gen_tension_entry_buffer");
    capa_entry_buffer = gtk_builder_get_object(builder, "capa_entry_buffer");
    res_entry_buffer = gtk_builder_get_object(builder, "res_entry_buffer");
    charge_init_entry_buffer = gtk_builder_get_object(builder, "charge_init_entry_buffer");

    GObject *resistance_image = gtk_builder_get_object(builder, "img");
    gtk_image_set_pixel_size((GtkImage*) resistance_image, 200);

    static datas buffer_data;
    buffer_data.gen_tension_entry_buffer = (GtkEntryBuffer*) gen_tension_entry_buffer;
    buffer_data.capa_entry_buffer = (GtkEntryBuffer*) capa_entry_buffer;
    buffer_data.res_entry_buffer = (GtkEntryBuffer*) res_entry_buffer;
    buffer_data.charge_init_entry_buffer = (GtkEntryBuffer*) charge_init_entry_buffer;

    g_signal_connect(button, "clicked", G_CALLBACK (show_graph), &buffer_data);
{
    builder = gtk_builder_new();
    gtk_builder_add_from_file(builder, "tipe.ui", NULL);

    window = gtk_builder_get_object(builder, "window");
    gtk_window_set_title(GTK_WINDOW(window), "TIPE");
    gtk_window_set_application(GTK_WINDOW(window), app);
    gtk_window_set_default_size(GTK_WINDOW(window), 1920, 1080);

    button = gtk_builder_get_object(builder, "button1");
    gen_tension_entry_buffer = gtk_builder_get_object(builder, "gen_tension_entry_buffer");
    capa_entry_buffer = gtk_builder_get_object(builder, "capa_entry_buffer");
    res_entry_buffer = gtk_builder_get_object(builder, "res_entry_buffer");
    charge_init_entry_buffer = gtk_builder_get_object(builder, "charge_init_entry_buffer");

    GObject *resistance_image = gtk_builder_get_object(builder, "img");
    gtk_image_set_pixel_size((GtkImage*) resistance_image, 200);

    static datas buffer_data;
    buffer_data.gen_tension_entry_buffer = (GtkEntryBuffer*) gen_tension_entry_buffer;
    buffer_data.capa_entry_buffer = (GtkEntryBuffer*) capa_entry_buffer;
    buffer_data.res_entry_buffer = (GtkEntryBuffer*) res_entry_buffer;
    buffer_data.charge_init_entry_buffer = (GtkEntryBuffer*) charge_init_entry_buffer;

    g_signal_connect(button, "clicked", G_CALLBACK (show_graph), &buffer_data);

    gtk_widget_set_visible(GTK_WIDGET(window), TRUE);
    g_object_unref(builder);
}

    gtk_widget_set_visible(GTK_WIDGET(window), TRUE);
    g_object_unref(builder);
}

int main(int argc, char **argv) {
    app = gtk_application_new("org.gtk.example", G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
    status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);

    return status;
}
