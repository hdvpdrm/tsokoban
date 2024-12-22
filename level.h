#ifndef LEVEL_H
#define LEVEL_H
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<ctype.h>
#include<string.h>

bool is_numeric(char* str); //check whether passed string contains only digital characters

bool parse_dim_val(int* val, char* line); //get width and height of level
void replaces_fillers(char* line); //replace + with spaces
bool read_level(char** output, char* filename, int* _width, int* _height);

#endif //LEVEL_H
