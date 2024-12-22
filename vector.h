#ifndef VECTOR_H
#define VECTOR_H

typedef struct
{
    int x;
    int y;
} Vector2i;

Vector2i vector2d_create(int x, int y);
Vector2i vector2d_add(Vector2i vec1, Vector2i vec2);

#define RIGHT    (Vector2i){0, 1}
#define LEFT  (Vector2i){0, -1}
#define UP  (Vector2i){-1, 0}
#define DOWN (Vector2i){1, 0}

#endif
