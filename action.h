#ifndef ACTION_H
#define ACTION_H
#include<stdlib.h>
#include"vector.h"

typedef struct
{
  Vector2i dir;
} ActionData;

typedef struct
{
  Vector2i oldbox_pos;
  Vector2i newbox_pos;
} BoxData;

struct Action
{
  ActionData data;
  BoxData box;
  struct Action* next;
  struct Action* prev;
};

#endif
