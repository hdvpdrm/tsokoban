#ifndef GAME_H
#define GAME_H
#include<ncurses.h>
#include<ctype.h>
#include"vector.h"

//width and height of terminal
static int width, height;

//offset for drawing
static int qw, qh;

//level_width and level_height is the sizes of level
extern int level_width, level_height;
extern char* level;

extern Vector2i char_pos;


#define ELEMENT(x,y) level[y*level_width+x]
#define IS_BOX(x,y)  ELEMENT(x,y) == '$'
#define IS_FREE(x,y) isspace(ELEMENT(x,y))


void init_game(void);
void free_game(void);
void run_game(void);

void find_char(void);
void draw_map(void);

void _move(char option);
void __move(Vector2i dir);
Vector2i move_el(Vector2i dir, Vector2i el_pos, char el);
bool can_move(Vector2i dir, Vector2i el_pos);
#endif
