//
//  ball.h
//  PeerPong
//
//  Created by Matheus Barella Ronfim on 4/11/16.
//  Copyright © 2016 Matheus Barella Ronfim. All rights reserved.
//

#ifndef ball_h
#define ball_h

#include <stdio.h>
#include "core.h"
#include "vector.h"
#include "paddle.h"
#include "timer.h"

typedef struct Ball {
    Vector2f* pos;
    Vector2f* vel;
    int r;
    Texture* texture;
} Ball;

Ball* newBall(int x, int y, int r, Texture* texture);
void destroyBall(Ball** ball);
void updateBall(Ball* ball, Paddle* paddle, float dt);
void renderBall(Window* window, Ball* ball);
int checkCollision(Ball* ball, SDL_Rect rect);
int horizDist(Ball* ball, SDL_Rect rect);
int vertDist(Ball* ball, SDL_Rect rect);

#endif /* ball_h */
