#pragma once

struct Vector2
{
    int x;
    int y;
    Vector2(int x,int y);

    static Vector2 Direction(Vector2 a,Vector2 b);
};
