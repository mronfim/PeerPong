//
//  vector.c
//  PeerPong
//
//  Created by Matheus Barella Ronfim on 4/11/16.
//  Copyright © 2016 Matheus Barella Ronfim. All rights reserved.
//

#include "vector.h"
#include <stdlib.h>
#include <math.h>


Vector2* vec2_new(int x, int y)
{
    Vector2* result = (Vector2 *)malloc(sizeof(Vector2));
    result->x = x;
    result->y = y;
    return result;
}

void vec2_multi(Vector2* u, int scalar)
{
    u->x *= scalar;
    u->y *= scalar;
}

void vec2_div(Vector2* u, int scalar)
{
    u->x /= scalar;
    u->y /= scalar;
}

Vector2* vec2_add(Vector2* u, Vector2* v)
{
    int x = u->x + v->x;
    int y = u->y + v->y;
    return vec2_new(x, y);
}

Vector2* vec2_sub(Vector2* u, Vector2* v)
{
    int x = u->x - v->x;
    int y = u->y - v->y;
    return vec2_new(x, y);
}

float vec2_dot(Vector2* u, Vector2* v)
{
    return (u->x * v->x) + (u->y * v->y);
}

void vec2_norm(Vector2* u)
{
    float length = sqrtf( powf(u->x, 2.f) + powf(u->y, 2.f) );
    vec2_div(u, length);
}

Vector2f* vec2f_new(float x, float y)
{
    Vector2f* result = (Vector2f *)malloc(sizeof(Vector2f));
    result->x = x;
    result->y = y;
    return result;
}

void vec2f_multi(Vector2f* u, float scalar)
{
    u->x *= scalar;
    u->y *= scalar;
}

void vec2f_div(Vector2f* u, float scalar)
{
    u->x /= scalar;
    u->y /= scalar;
}

Vector2f* vec2f_add(Vector2f* u, Vector2f* v)
{
    float x = u->x + v->x;
    float y = u->y + v->y;
    return vec2f_new(x, y);
}

Vector2f* vec2f_sub(Vector2f* u, Vector2f* v)
{
    float x = u->x - v->x;
    float y = u->y - v->y;
    return vec2f_new(x, y);
}

float vec2f_dot(Vector2f* u, Vector2f* v)
{
    return (u->x * v->x) + (u->y * v->y);
}

void vec2f_norm(Vector2f* u)
{
    float length = sqrtf( powf(u->x, 2.f) + powf(u->y, 2.f) );
    vec2f_div(u, length);
}




































