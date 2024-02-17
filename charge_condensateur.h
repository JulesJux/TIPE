#ifndef CHARGE_CONDENSATEUR_H
#define CHARGE_CONDENSATEUR_H

#include <assert.h>
#include <gtk/gtk.h>
#include "gnuplot/gnuplot.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define TAILLE_MAX 50

int status;
GtkApplication *app;
GtkBuilder *builder;
GObject *window;

GObject *button;
GObject *gen_tension_entry_buffer;
GObject *capa_entry_buffer;
GObject *res_entry_buffer;

typedef struct data_s {
    GtkEntryBuffer *gen_tension_entry_buffer;
    GtkEntryBuffer *capa_entry_buffer;
    GtkEntryBuffer *res_entry_buffer;
} datas;

#endif //CHARGE_CONDENSATEUR_H
