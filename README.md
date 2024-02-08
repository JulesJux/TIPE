Commande de compilation : 
gcc -Wall `pkg-config --cflags gtk+-3.0` -o gui -g ../gnuplot_i/gnuplot_i.c  hello-world-gtk.c `pkg-config --libs gtk+-3.0` -lm

