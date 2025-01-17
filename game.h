#ifndef GAME_H
#define GAME_H
#include<ncurses.h>
#include<ctype.h>
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include"vector.h"
#include"action.h"

//width and height of terminal
static int width, height;

//offset for drawing
static int qw, qh;

static int turn_counter = 0;
static int box_counter  = 0;

static struct Action actions_list = {.next=NULL, .prev=NULL};
static struct Action* last_action = NULL;
static size_t actions_list_counter = 0;

//level_width and level_height is the sizes of level
extern int level_width, level_height;
extern char* level;
extern Vector2i char_pos;
extern size_t fpoints_size;
extern Vector2i* finish_points;


#define ELEMENT(x,y)  level[y*level_width+x]
#define IS_BOX(x,y)   ELEMENT(x,y) == '$'
#define IS_FREE(x,y)  isspace(ELEMENT(x,y))
#define IS_FPOINT(x,y)ELEMENT(x,y) == '.'

void init_game(void);
void free_game(void);

void run_game(void);
void run_programmed_game(char** command_file);

void find_char_and_fpoints(void);
void add_fpoint(int x, int y);
void draw_map(void);

bool _move(char option);
void __move(Vector2i dir, Vector2i* oldbox_pos, Vector2i* newbox_pos);
Vector2i move_el(Vector2i dir, Vector2i el_pos, char el);
bool can_move(Vector2i dir, Vector2i el_pos);

void update_fpoints(void);
void count_boxes(void);

void save_action(int x, int y,Vector2i oldbox_pos, Vector2i newbox_pos);
void undo(void);
#endif
