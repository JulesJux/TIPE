cmake_minimum_required(VERSION 3.22)
project(TIPE C)

set(CMAKE_C_STANDARD 11)

add_executable(TIPE charge_condensateur.c
        ../gnuplot/gnuplot.c
        charge_condensateur.h
        #editeur_circuit.ui
        #editeur_circuit.c
        #editeur_circuit.h
)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK4 REQUIRED gtk4)

include_directories(${GTK4_INCLUDE_DIRS})
link_directories(${GTK4_LIBRARY_DIRS})
add_definitions(${GTK4_CFLAGS_OTHER})
target_link_libraries(TIPE ${GTK4_LIBRARIES} m)
