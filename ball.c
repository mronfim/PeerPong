//
//  ball.c
//  PeerPong
//
//  Created by Matheus Barella Ronfim on 4/11/16.
//  Copyright © 2016 Matheus Barella Ronfim. All rights reserved.
//

#include "ball.h"

#define MIN_BALL_SPEED 200

Ball* newBall(int x, int y, int r, Texture* texture)
{
    Ball* ball = (Ball *) malloc(sizeof(Ball));
    ball->pos = vec2f_new( (float)x, (float)y );
    ball->vel = vec2f_new( -MIN_BALL_SPEED, 0 );
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

void updateBall(Ball* ball, Paddle* paddle, float dt)
{
    ball->pos->x += ball->vel->x * dt;
    ball->pos->y += ball->vel->y * dt;
    
    printf("Paddle x: %d, Paddle y: %d\n", paddle->collider.x, paddle->collider.y);
    
    if (checkCollision(ball, paddle->collider))
    {
        ball->pos->x -= ball->vel->x * dt;
        ball->vel->x *= -1.5;
        ball->pos->x += ball->vel->x * dt;
    }
}

void renderBall(Window* window, Ball* ball)
{
    drawTexture(window, ball->texture, ball->pos->x - ball->r, ball->pos->y - ball->r);
}

int checkCollision(Ball* ball, SDL_Rect rect)
{
    // closest point on collision box
    int cX, cY;
    
    // find closest x offset
    if ( (int)ball->pos->x < (int)rect.x )
        cX= rect.x;
    else if ( (int)ball->pos->x > rect.x + rect.w )
        cX = rect.x + rect.w;
    else
        cX = (int)ball->pos->x;
    
    // find closest y offset
    if ( (int)ball->pos->y < rect.y )
        cY = rect.y;
    else if ( (int)ball->pos->y > rect.y + rect.h )
        cY = rect.y + rect.h;
    else
        cY = (int)ball->pos->y;
    
    // if the closest point is inside the circle
    int deltaX = cX - (int)ball->pos->x;
    int deltaY = cY - (int)ball->pos->y;
    double distanceSquared = deltaX*deltaX + deltaY*deltaY;
    
    if (distanceSquared < (ball->r * ball->r))
    {
        printf("Collided\n");
        return 1;
    }
    
    return 0;
}

int horizDist(Ball* ball, SDL_Rect rect)
{
    return 0;
}

int vertDist(Ball* ball, SDL_Rect rect)
{
    return 0;
}