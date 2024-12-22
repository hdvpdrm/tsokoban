#ifndef LEVEL_H
#define LEVEL_H
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<ctype.h>
#include<string.h>

bool is_numeric(char* str);

bool parse_dim_val(int* val, char* line);
void replaces_fillers(char* line);
bool read_level(char** output, char* filename, int* _width, int* _height);

#endif //LEVEL_H
