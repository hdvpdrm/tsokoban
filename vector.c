#include"vector.h"

Vector2i vector2d_create(int x, int y)
{
    Vector2i vec;
    vec.x = x;
    vec.y = y;
    return vec;
}

Vector2i vector2d_add(Vector2i vec1, Vector2i vec2)
{
    Vector2i result;
    result.x = vec1.x + vec2.x;
    result.y = vec1.y + vec2.y;
    return result;
}
