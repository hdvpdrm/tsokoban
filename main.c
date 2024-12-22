#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include"level.h"
#include"game.h"

#define LEVEL_PATH "levels/Level%d"

int parse_arguments(int argc, char** argv);
void print_help(void);
int main(int argc, char** argv)
{
  //get the level number
  int result = parse_arguments(argc, argv);
  if(result == -1 || result == -2)
    {
      print_help();
      return 0;
    }

  //compute name of file that contains level
  int size = snprintf(NULL,0,LEVEL_PATH,result);//get the size of the string
  char filename[size+1];
  snprintf(filename,sizeof filename,LEVEL_PATH,result);

  if(!read_level(&level,filename,&level_width,&level_height))
    {
      printf("tsokoban error: failed to read '%s' file",filename);
      return -1;
    }
  find_char_and_fpoints(); //get the position of character
  
  init_game();
  run_game();
  free_game();

  return 0;
}
int parse_arguments(int argc, char** argv)
{
  if(argc == 1) return 1; //start game from first level

  if(argc == 2)
    {
      //return help
      if(strcmp(argv[1],"-h") == 0     ||
	 strcmp(argv[1],"--help") == 0 ||
	 !is_numeric(argv[1]))
	{
	  return -2;
	}
      
      //return level if everything is ok
      return atoi(argv[1]);
    }

  return -2;
}
void print_help(void)
{
  printf("tsokoban: simple ncurses based sokoban.\n\n"
	 "tsokoban [-h] [--help] - print this message.\n"
	 "tsokoban n - run game and play nth level.\n"
	 "tsokoban - run game and start at the first level.\n");
}
