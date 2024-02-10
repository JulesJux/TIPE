Commande de compilation : \
gcc -Wall `pkg-config --cflags gtk4` -o gui -g gnuplot/gnuplot.c charge_condensateur_gtk.c `pkg-config --libs gtk4` -lm

