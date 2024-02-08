#include <stddef.h>
#include <gtk/gtk.h>
#include <stdio.h>
#include <math.h>
#include "gnuplot/gnuplot.h"
#include <string.h>

void charge_cond_graph(gnuplot_ctrl *h, double u0, double E, double R, double C, int n){
    double X[n];
    double Y[n];
    for (int i = 0; i < n; i++){
        X[i] = i;
        Y[i] = (u0-E)*exp(-i/(R*C)) + E;
    }
    gnuplot_cmd(h, "set term wxt persist");
    gnuplot_setterm(h, "wxt", 1920, 1080);
    gnuplot_plot_coordinates(h, X, Y, n, "Réponse échelon de tension (circuit RC)");
    gnuplot_close(h);
}

static void
print_hello(GtkWidget *widget,
            gpointer data) {
    g_print("Hello World\n");
}

static void show_graph (GtkWidget *widget,
            gpointer data) {
    double u0, E, R, C;
    scanf("%lf", &u0);
    scanf("%lf", &E);
    scanf("%lf", &R);
    scanf("%lf", &C);
    gnuplot_ctrl *h;
    h = gnuplot_init();
    charge_cond_graph(h, u0, E, R, C, 50);
}

static void
activate(GtkApplication *app,
         gpointer user_data) {
    GtkWidget *window;
    GtkWidget *button;
    GtkWidget *button_box;



    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Window");
    gtk_window_set_default_size(GTK_WINDOW(window), 1920, 1080);

    button_box = gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL);
    gtk_container_add(GTK_CONTAINER(window), button_box);

    button = gtk_button_new_with_label("Hello World");
    g_signal_connect(button, "clicked", G_CALLBACK(show_graph), NULL);
   // g_signal_connect_swapped(button, "clicked", G_CALLBACK(gtk_widget_destroy), window);
    gtk_container_add(GTK_CONTAINER(button_box), button);

    gtk_widget_show_all(window);
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
