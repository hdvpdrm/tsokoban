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
  if(argc > 2) return -1; // incorrect number of arguments
  if(argc == 1) return -2; //show help

  if(strcmp(argv[1],"-h") ||
     strcmp(argv[1],"--help"))
    return -2;

  if(!is_numeric(argv[1]))
    return -2;

  return atoi(argv[1]);
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
