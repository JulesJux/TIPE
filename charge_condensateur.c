#include "charge_condensateur.h"

void charge_cond(gnuplot_ctrl *h, char *u0, char *E, char *R, char *C) {
    char cmd[TAILLE_MAX] = {};
    strcat(cmd, "plot (");
    strcat(cmd, u0);
    strcat(cmd, "-");
    strcat(cmd, E);
    strcat(cmd, ")*exp(-x/(");
    strcat(cmd, R);
    strcat(cmd, "*");
    strcat(cmd, C);
    strcat(cmd, "))+");
    strcat(cmd, E); //plot (Uc(0)-E)exp(-x/RC) + E

    gnuplot_setterm(h, "wxt", 720, 480);
    gnuplot_cmd(h, cmd);
    gnuplot_close(h);
}

static void show_graph(GtkWidget *widget,
                       gpointer data) {
    const datas *d = (datas *) data;
    const gchar *text_gen_tension_entry = gtk_entry_buffer_get_text(d->gen_tension_entry_buffer);
    const gchar *text_capa_entry = gtk_entry_buffer_get_text(d->capa_entry_buffer);
    const gchar *text_res_entry = gtk_entry_buffer_get_text(d->res_entry_buffer);

    g_print(text_gen_tension_entry);
    g_print(text_capa_entry);
    g_print(text_res_entry);

    gnuplot_ctrl *h = gnuplot_init();
    charge_cond(h, "0", (char *) text_gen_tension_entry, (char *) text_res_entry, (char *) text_capa_entry);
}

static void
activate(GtkApplication *app,
         gpointer user_data) {
    builder = gtk_builder_new();
    gtk_builder_add_from_file(builder, "tipe.ui", NULL);

    window = gtk_builder_get_object(builder, "window");
    gtk_window_set_title(GTK_WINDOW(window), "Window");
    gtk_window_set_application(GTK_WINDOW(window), app);
    gtk_window_set_default_size(GTK_WINDOW(window), 1920, 1080);

    button = gtk_builder_get_object(builder, "button1");
    gen_tension_entry_buffer = gtk_builder_get_object(builder, "gen_tension_entry_buffer");
    capa_entry_buffer = gtk_builder_get_object(builder, "capa_entry_buffer");
    res_entry_buffer = gtk_builder_get_object(builder, "res_entry_buffer");

    static datas buffer_data;
    buffer_data.gen_tension_entry_buffer = gen_tension_entry_buffer;
    buffer_data.capa_entry_buffer = capa_entry_buffer;
    buffer_data.res_entry_buffer = res_entry_buffer;

    g_signal_connect(button, "clicked", G_CALLBACK (show_graph), &buffer_data);

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
