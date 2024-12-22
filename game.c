#include"game.h"

int level_width = 0;
int level_height = 0;
char* level = NULL;

Vector2i char_pos;

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
void run_game(void)
{
  while(1)
    {
      draw_map();
      refresh();
	
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
	  if(ELEMENT(x,y) == '@')
	    {
	      char_pos.x = x;
	      char_pos.y = y;
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
	  mvaddch(qw+x,qh+y,ELEMENT(x,y));
	}
    }
}
void _move(char option)
{
  if(option == 'w')
    {
      __move(UP);
    }
  if(option == 'a')
    {
      __move(LEFT);
    }
  if(option == 'd')
    {
      __move(RIGHT);
    }
  if(option == 's')
    {
      __move(DOWN);
    }
}
void __move(Vector2i dir)
{
  if(!can_move(dir,char_pos)) return;

  Vector2i next_pos = vector2d_add(char_pos,dir);
  if(IS_BOX(next_pos.x,next_pos.y))
    {
      next_pos = vector2d_add(next_pos,dir);
      if(IS_FREE(next_pos.x,next_pos.y))
	{
	  ELEMENT(next_pos.x,next_pos.y) = '$';
	  char_pos =  move_el(dir,char_pos,'@');
	}
    }
  else
    {  
      char_pos = move_el(dir,char_pos,'@');
    }
}
Vector2i move_el(Vector2i dir, Vector2i el_pos, char el)
{
  ELEMENT(el_pos.x,el_pos.y) = ' ';
  Vector2i np = vector2d_add(el_pos,dir);
  ELEMENT(np.x,np.y) = el;
  return np;
}
bool can_move(Vector2i dir, Vector2i el_pos)
{
  Vector2i nv = vector2d_add(el_pos,dir);
  return nv.x > 0 &&
         nv.y > 0 &&
         nv.x < level_width  &&
         nv.y < level_height &&
    ELEMENT(nv.x,nv.y) != '#';
}
