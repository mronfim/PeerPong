//
//  ball.c
//  PeerPong
//
//  Created by Matheus Barella Ronfim on 4/11/16.
//  Copyright © 2016 Matheus Barella Ronfim. All rights reserved.
//

#include "ball.h"


Ball* newBall(int x, int y, int r, Texture* texture)
{
    Ball* ball = (Ball *) malloc(sizeof(Ball));
    ball->pos = vec2f_new( (float)x, (float)y );
    ball->vel = vec2f_new( 0.f, 0.f );
    ball->r = r;
    ball->texture = texture;
    return ball;
}

void destroyBall(Ball** ball)
{
    free((*ball)->pos);
    free((*ball)->vel);
    deleteTexture(&(*ball)->texture);
    free(*ball);
}

void updateBall(Ball* ball, float dt)
{
    // TODO: update ball
}

void renderBall(Window* window, Ball* ball)
{
    drawTexture(window, ball->texture, ball->pos->x, ball->pos->y);
}

int checkCollision(Ball* ball, SDL_Rect rect)
{
    return 0;
}