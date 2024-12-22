#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<stdbool.h>

int parse_arguments(int argc, char** argv);
bool is_numeric(char* str);
void print_help(void);
int main(int argc, char** argv)
{
  int result = parse_arguments(argc, argv);
  if(result == -1 || result == -2)
    {
      print_help();
      return 0;
    }

  return 0;
}
int parse_arguments(int argc, char** argv)
{
  if(argc == 1) return 0; //start game from 0 level

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
bool is_numeric(char* str)
{
  for(int i = 0;i<strlen(str);++i)
    {
      if(!isdigit(str[i]))return false;
    }

  return true;
}
void print_help(void)
{
  printf("tsokoban: simple ncurses based sokoban.\n\n"
	 "tsokoban [-h] [--help] - print this message.\n"
	 "tsokoban n - run game and play nth level.\n"
	 "tsokoban - run game and start at the first level.\n");
}
