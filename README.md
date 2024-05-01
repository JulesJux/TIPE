Commande de compilation : \
gcc -Wall `pkg-config --cflags gtk4` -o gui -g gnuplot/gnuplot.c charge_condensateur.c `pkg-config --libs gtk4` -lm \
\
Compilation avec cmake : \
cmake . \
make


