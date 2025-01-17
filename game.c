#include"game.h"

int level_width         = 0;
int level_height        = 0;
char* level             = NULL;
size_t fpoints_size     = 0;
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

  qw = (width/2) - level_width/2;
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
	
      if(_move(getch()))break;
      update_fpoints();

      count_boxes();

      if(box_counter == fpoints_size)
	{
	  clear();
	  refresh();

	  int max_y, max_x;
	  getmaxyx(stdscr, max_y, max_x);
	  
	  int center_y = max_y / 2;
	  int center_x = max_x / 2;
	  move(center_y, center_x);
	  
	  printw("You win in %d turns!\n",turn_counter);
	  getch();
	  break;
	}
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
	      add_fpoint(x,y);
	    }
	}
    }
}
void add_fpoint(int x, int y)
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
void draw_map(void)
{  
  for(int y = 0;y<level_height;++y)
    {
      for(int x = 0;x<level_width;++x)
	{
	  mvaddch(qw+x,qh+y,ELEMENT(x,y));
	}
    }

    mvprintw(qw+level_width-1,qh-3,"TURN:%d\tBOXES:%d/%d",turn_counter,box_counter,fpoints_size);
}
bool _move(char option)
{
  Vector2i old_cpos = char_pos;
  
  Vector2i oldbox_pos = vector2d_create(-1,-1);
  Vector2i newbox_pos = vector2d_create(-1,-1);
  if(option == 'w')
    {
      __move(UP,&oldbox_pos,&newbox_pos);
      
      if(!VEQ(old_cpos,char_pos))
	save_action(-1,0,oldbox_pos,newbox_pos);
    }
  if(option == 'a')
    {
      __move(LEFT,&oldbox_pos,&newbox_pos);

      if(!VEQ(old_cpos,char_pos))
	save_action(0,-1,oldbox_pos,newbox_pos);
    }
  if(option == 'd')
    {
      __move(RIGHT,&oldbox_pos,&newbox_pos);

      if(!VEQ(old_cpos,char_pos))
	save_action(0,1,oldbox_pos,newbox_pos);
    }
  if(option == 's')
    {
      __move(DOWN,&oldbox_pos,&newbox_pos);

      if(!VEQ(old_cpos,char_pos))
	save_action(1,0,oldbox_pos,newbox_pos);
    }
  if(option == 'z')
    {
      undo();
    }
  if(option == 'q')
    {
      return true;
    }

  return false;
}
void __move(Vector2i dir,Vector2i* oldbox_pos, Vector2i* newbox_pos)
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

	  *oldbox_pos = vector2d_sub(next_pos,dir);
	  newbox_pos->x = next_pos.x;
	  newbox_pos->y = next_pos.y;
	}
      else if(IS_FPOINT(next_pos.x,next_pos.y))
	{
	  ELEMENT(next_pos.x,next_pos.y) = '$';
	  char_pos =  move_el(dir,char_pos,'@');

	  *oldbox_pos = vector2d_sub(next_pos,dir);
	  newbox_pos->x = next_pos.x;
	  newbox_pos->y = next_pos.y;
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
  
  return nv.x > 0            &&
         nv.y > 0            &&
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
      if(ELEMENT(x,y) != '.' &&
	 ELEMENT(x,y) != '@' &&
	 ELEMENT(x,y) != '$')
	{
	  ELEMENT(x,y) = '.';
	}
    }
}
void count_boxes(void)
{
  int counter = 0;
  for(size_t i = 0;i<fpoints_size;++i)
    {
      int x = finish_points[i].x;
      int y = finish_points[i].y;
      if(ELEMENT(x,y) == '$') ++counter;	    
    }

  int diff = box_counter - counter;
  box_counter-=diff;
}
void save_action(int x, int y,Vector2i oldbox_pos, Vector2i newbox_pos)
{
    if (actions_list_counter == 0)
      {
        actions_list.data.dir.x = x;
        actions_list.data.dir.y = y;

	vector2d_fill(&actions_list.box.oldbox_pos,&oldbox_pos);
	vector2d_fill(&actions_list.box.newbox_pos,&newbox_pos);
	
        actions_list.prev = NULL;
        last_action = &actions_list;
    }
    else
      {
        last_action->next = (struct Action*)malloc(sizeof(struct Action));
        if (!last_action->next)
	  {
            printf("Error: failed to save action!\n");
            exit(-1);
        }

        last_action->next->data.dir.x = x;
        last_action->next->data.dir.y = y;
	vector2d_fill(&last_action->box.oldbox_pos,&oldbox_pos);
	vector2d_fill(&last_action->box.newbox_pos,&newbox_pos);

	
        last_action->next->prev = last_action;
        last_action = last_action->next;
    }
    actions_list_counter++;
}

// Function to undo the last action
void undo(void)
{
    if (actions_list_counter > 0 && last_action != NULL)
      {
        // Update character position based on the last action
	ELEMENT(char_pos.x,char_pos.y) = ' ';
        char_pos.x -= last_action->data.dir.x;
        char_pos.y -= last_action->data.dir.y;
	ELEMENT(char_pos.x,char_pos.y) = '@';

	// Update box
	if(last_action->box.oldbox_pos.x > 0)
	  {
	    int oldx = last_action->box.oldbox_pos.x;
	    int oldy = last_action->box.oldbox_pos.y;

	    int newx = last_action->box.newbox_pos.x;
	    int newy = last_action->box.newbox_pos.y;
	    
	    ELEMENT(newx,newy) = ' ';
	    ELEMENT(oldx,oldy) = '$';
	  }

	
        // Free the last action and update the list
        struct Action* prev_action = last_action->prev;
        if (last_action != &actions_list)
	  {
            free(last_action);
	  }
        last_action = prev_action;
        last_action = prev_action;

	if (last_action) {
            last_action->next = NULL;
        } else {
            // If there are no more actions, reset the actions_list
            actions_list.next = NULL;
            actions_list.prev = NULL;
        }
        actions_list_counter--;
	turn_counter--;
    }
}

