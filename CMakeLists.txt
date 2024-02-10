cmake_minimum_required(VERSION 3.27)
project(TIPE C)

set(CMAKE_C_STANDARD 11)

add_executable(TIPE charge_condensateur_gtk.c
        gnuplot/gnuplot.c)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK4 REQUIRED gtk4)

include_directories(${GTK4_INCLUDE_DIRS})
link_directories(${GTK4_LIBRARY_DIRS})
add_definitions(${GTK4_CFLAGS_OTHER})

target_link_libraries(TIPE ${GTK4_LIBRARIES} m)