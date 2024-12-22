#ifndef GAME_H
#define GAME_H
#include<ncurses.h>
#include<stdlib.h>

//width and height of terminal
static int width, height;

//offset for drawing
static int qw, qh;

//level_width and level_height is the sizes of level
extern int level_width, level_height;
extern char* level;

extern int char_x, char_y;

void init_game(void);
void free_game(void);
void draw_game(void);
void run_game(void);

void find_char(void);
void draw_map(void);

bool can_move(int y, int x); //direction values
void _move(char key);
void move_char(int y, int x);
#endif
