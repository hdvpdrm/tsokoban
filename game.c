#include"game.h"

int level_width = 0;
int level_height = 0;
char* level = NULL;
size_t fpoints_size = 0;
Vector2i* finish_points = NULL;
Vector2i char_pos;


void init_game(void)
{
  initscr();
  cbreak();
  noecho();
  curs_set(0);
  keypad(stdscr, TRUE);
  
  getmaxyx(stdscr,width,height);

  qw = (width/2)-10;
  qh = (height/2)-10;

}
void free_game(void)
{
  endwin();
  free(finish_points);
  free(level);
}
void run_game(void)
{
  while(1)
    {
      draw_map();
      refresh();
	
      _move(getch());
      update_fpoints();
    }

}
void find_char_and_fpoints(void)
{
  for(int y = 0;y<level_height;++y)
    {
      for(int x = 0;x<level_width;++x)
	{
	  if(ELEMENT(x,y) == '@')
	    {
	      char_pos.x = x;
	      char_pos.y = y;
	    }
	  else if(ELEMENT(x,y) == '.')
	    {	      
	      if(finish_points == NULL)
		{
		  finish_points = (Vector2i*)malloc(sizeof(Vector2i));
		  if(!finish_points)
		    {
		      printf("tsokoban error: failed to allocate memory!");
		      exit(-3);
		    }
		  finish_points[0].x = x;
		  finish_points[0].y = y;
		  ++fpoints_size;
		}
	      else
		{
		  ++fpoints_size;
		  finish_points = realloc(finish_points,sizeof(Vector2i)*fpoints_size);
		  if(!finish_points)
		    {
		      printf("tsokoban error: failed to allocate memory!");
		      exit(-3);
		    }
		  finish_points[fpoints_size-1].x = x;
		  finish_points[fpoints_size-1].y = y;
		}	     
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

  mvprintw(qw+level_width-1,qh,"TURN:%d",turn_counter);
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

  ++turn_counter;
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

void update_fpoints(void)
{
  for(size_t i = 0;i<fpoints_size;++i)
    {
      int x = finish_points[i].x;
      int y = finish_points[i].y;
      if(ELEMENT(x,y) != '.' && ELEMENT(x,y) != '@')
	{
	  ELEMENT(x,y) = '.';
	}
    }
}
