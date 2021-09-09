#include "math.h"

Vector2::Vector2(int x, int y)
{
    Vector2::x = x;
    Vector2::y = y;
}
Vector2 Vector2::Direction(Vector2 a, Vector2 b)
{
    return Vector2(b.x-a.x,b.y-a.y);
}
