#ifndef pongstructs_h
#define pongstructs_h


#include <stdio.h>
#include "core.h"
#include "vector.h"
#include "timer.h"


// --- PADDLE ---

typedef struct Paddle {
    Vector2f* pos;
    Vector2f* vel;
    int w;
    int h;
    SDL_Color baseColor;
    SDL_Color borderColor;
    SDL_Rect collider;
    int score;
} Paddle;

Paddle* newPaddle(int x, int y, int w, int h, SDL_Color baseColor, SDL_Color borderColor);
void destroyPaddle(Paddle** paddle);



// --- BALL ---

typedef struct Ball {
    Vector2f* pos;
    Vector2f* vel;
    int r;
    Texture* texture;
} Ball;

Ball* newBall(int x, int y, int r, Texture* texture);
void destroyBall(Ball** ball);


#endif