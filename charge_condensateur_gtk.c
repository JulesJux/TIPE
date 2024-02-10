#include <assert.h>
#include <gtk-4.0/gtk/gtk.h>
#include "gnuplot/gnuplot.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define TAILLE_MAX 50

typedef struct data_s {
    GtkBuilder* builder;
    GtkEntryBuffer* buffer;
    GtkLabel* label;
} datas;

void charge_cond(gnuplot_ctrl *h, char* u0, char* E, char* R, char* C) {
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
    strcat(cmd, E);     //plot (Uc(0)-E)exp(-x/RC) + E

    gnuplot_setterm(h, "wxt", 720, 480);
    gnuplot_cmd(h, cmd);
    gnuplot_close(h);
}

static void show_graph (GtkWidget *widget,
            gpointer data) {
    datas* d = data;
    // gchar* text = gtk_entry_buffer_get_text(d->buffer);
    // gtk_label_set_text(d->label, text);

    char u0[TAILLE_MAX], E[TAILLE_MAX], R[TAILLE_MAX], C[TAILLE_MAX];
    scanf("%s", u0);
    scanf("%s", E);
    scanf("%s", R);
    scanf("%s", C);
    gnuplot_ctrl *h = gnuplot_init();
    charge_cond(h, u0, E, R, C);
}

static void
activate(GtkApplication *app,
         gpointer user_data) {


    GtkBuilder *builder = gtk_builder_new ();
    gtk_builder_add_from_file (builder, "tipe.ui", NULL);

    GObject *window = gtk_builder_get_object (builder, "window");
    gtk_window_set_title(GTK_WINDOW(window), "Window");
    gtk_window_set_application (GTK_WINDOW (window), app);
    gtk_window_set_default_size(GTK_WINDOW(window), 1920, 1080);
    GObject *buffer = gtk_builder_get_object(builder, "entry_buffer");
    GObject *label = gtk_builder_get_object(builder, "test");
    GObject *button = gtk_builder_get_object (builder, "button1");

    datas datass;
    datass.builder = builder;
    datass.buffer = buffer;
    datass.label = label;

    g_signal_connect(button, "clicked", G_CALLBACK (show_graph), &datass);

    //GObject *textEntry = gtk_builder_get_object(builder, "text_entry");
   // g_signal_connect_swapped(button, "clicked", G_CALLBACK(gtk_widget_destroy), window);
    gtk_widget_set_visible (GTK_WIDGET (window), TRUE);
    g_object_unref (builder);
}

int
main(int argc,
     char **argv) {
    GtkApplication *app;
    int status;
    app = gtk_application_new("org.gtk.example", G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
    status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);

    return status;
}
