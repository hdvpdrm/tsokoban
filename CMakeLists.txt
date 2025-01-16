cmake_minimum_required(VERSION 3.10)
project(tsokoban)
set(CMAKE_C_STANDARD.99)

add_link_options(-lm -lncurses)

set(HEADERS level.h game.h vector.h action.h)
set(SOURCES main.c level.c game.c vector.c)
add_executable(tsokoban ${SOURCES} ${HEADERS})
