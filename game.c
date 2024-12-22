#include"game.h"

int level_width = 0;
int level_height = 0;
char* level = NULL;

int char_x = -1;
int char_y = -1;

void init_game(void)
{
  initscr();
  cbreak();
  noecho();
  keypad(stdscr, TRUE);
  
  getmaxyx(stdscr,width,height);

  qw = (width/2)-5;
  qh = (height/2)-5;

}
void free_game(void)
{
  endwin();
}
void draw_game(void)
{

}

void run_game(void)
{
  while(1)
    {
      draw_map();
      refresh();
	
      draw_game();
      char option = getch();
      _move(option);
    }

}
void find_char(void)
{
  for(int y = 0;y<level_height;++y)
    {
      for(int x = 0;x<level_width;++x)
	{
	  if(level[y*level_width+x] == '@')
	    {
	      char_x = x;
	      char_y = y;
	      return;
	    }
	}
    }
}
void draw_map(void)
{  
  for(int y = 0;y<level_height;++y)
    {
      for(int x = 0;x<level_width;++x)
	{
	  mvaddch(qw+x,qh+y,level[y*level_width+x]);
	}
    }
}
bool can_move(int y, int x)
{
  int nx = char_x + x;
  int ny = char_y + y;
  if(nx < 0 ||
     ny < 0 ||
     nx > level_width ||
     ny > level_height)
    return false;
  
  if(level[ny*level_width+nx] == '#') return false;
  
  return true;
}
void _move(char key)
{
  if(key == 'h' || key == 'a')
    {
      if(can_move(-1,0))	
	move_char(-1,0);
    }
  if(key == 'l' || key == 'd')
    {
      if(can_move(1,0))
	move_char(1,0);
    }
  if(key == 'j' || key == 'w')
    {
      if(can_move(0,-1))
	move_char(0,-1);
    }
  if(key == 'k' || key == 's')
    {
      if(can_move(0,1))
	move_char(0,1);
    }
}
void move_char(int y, int x)
{
  level[char_y*level_width+char_x] = ' ';
  char_x+=x;
  char_y+=y;
  level[char_y*level_width+char_x] = '@';
}
