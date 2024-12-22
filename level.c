#include"level.h"

bool is_numeric(char* str)
{
  for(int i = 0;i<strlen(str);++i)
    {
      if(str[i] == '\n' && i == strlen(str)-1)continue;//skip the last char
      if(!isdigit(str[i]))return false;
    }

  return true;
}
bool parse_dim_val(int* val, char* line)
{
  if(!is_numeric(line))
    {
      printf("tsokoban error: failed to read dimension value!\n");
      return false;
    }
  *val = atoi(line);
  return true;
}
void replaces_fillers(char* line)
{
  for(int i = 0;i<strlen(line);++i)
    {
      if(line[i] == '+')line[i] = ' ';
    }
}

bool read_level(char** output, char* filename, int* _width, int* _height)
{
  FILE* level = fopen(filename,"r");
  if(!level) return false;

  char* line = NULL;
  size_t len = 0;
  ssize_t read;

  int width = 0;
  int height = 0;
  
  int counter = 0;

  int output_a = 0;
  while( (read = getline(&line,&len,level)) != -1)
    {
      if(counter == 0) if(!parse_dim_val(&width,line)) return false;       //get width
      if(counter == 1) if(!parse_dim_val(&height,line)) return false;      //get height

      if(*output == NULL && counter > 1)
	{
	  //create buffer with map
	  *output = (char*)malloc(height*width + width);
	  if(!output) return false;       
	}

      //fill map
      if(counter > 1)
	{
	  replaces_fillers(line);
	  for(int n = 0;n<width;++n)
	    {
	      (*output)[output_a+n] = line[n];
	    }
	  output_a += width;
	  
	}

      ++counter;
    }

  *_width = width;
  *_height = height;
  fclose(level);
  return true;
}
