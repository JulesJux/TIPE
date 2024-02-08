Commande de compilation : \
gcc -Wall `pkg-config --cflags gtk+-3.0` -o gui -g gnuplot/gnuplot.c charge_condensateur_gtk.c `pkg-config --libs gtk+-3.0` -lm

