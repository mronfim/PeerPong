//
//  vector.h
//  PeerPong
//
//  Created by Matheus Barella Ronfim on 4/11/16.
//  Copyright © 2016 Matheus Barella Ronfim. All rights reserved.
//

#ifndef vector_h
#define vector_h

#include <stdio.h>

typedef struct Vector2 {
    int x;
    int y;
} Vector2;

typedef struct Vector2f {
    float x;
    float y;
} Vector2f;

Vector2* vec2_new(int x, int y);
void vec2_multi(Vector2* v, int scalar);
void vec2_div(Vector2* u, int scalar);
Vector2* vec2_add(Vector2* u, Vector2* v);
Vector2* vec2_sub(Vector2* u, Vector2* v);
float vec2_dot(Vector2* u, Vector2* v);
void vec2_norm(Vector2* u);

Vector2f* vec2f_new(float x, float y);
void vec2f_multi(Vector2f* u, float scalar);
void vec2f_div(Vector2f* u, float scalar);
Vector2f* vec2f_add(Vector2f* u, Vector2f* v);
Vector2f* vec2f_sub(Vector2f* u, Vector2f* v);
float vec2f_dot(Vector2f* u, Vector2f* v);
void vec2f_norm(Vector2f* u);

#endif /* vector_h */
