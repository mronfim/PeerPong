//
//  ball.c
//  PeerPong
//
//  Created by Matheus Barella Ronfim on 4/11/16.
//  Copyright © 2016 Matheus Barella Ronfim. All rights reserved.
//

#include "ball.h"

#define MIN_BALL_SPEED 200
#define MAX_BALL_SPEED 400

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

Vector2f* getNewVel(Ball* ball, SDL_Rect rect)
{
    // new velocity vector to be returned.
    Vector2f* newVel = vec2f_new( ball->vel->x * -1.6, 0 );

    // distance from the middle of the paddle
    // to the ball, vertically.
    float distance = ball->pos->y - (rect.y + rect.h / 2);

    // if distance is negative, ball hit top half
    if (distance < 0)
    {
        // make the ball move towards the top of the screen
        newVel->y = MAX_BALL_SPEED * (distance / (rect.h / 2));
    }

    // else if distance is positive, ball hit bottom half
    else if (distance > 0)
    {
        // make the ball move towards the bottom of the screen
        newVel->y = MAX_BALL_SPEED * (distance / (rect.h / 2));
    }

    // otherwise, the ball hit right in the center of the paddle
    else
    {
        // make the ball move horizontally
        newVel->y = 0;
    }

    return newVel;
}

void updateBall(Ball* ball, Paddle* paddle, Paddle* paddle2, float dt)
{
    ball->pos->x += ball->vel->x * dt;
    ball->pos->y += ball->vel->y * dt;
    
    // if ball hits left paddle
    if (checkCollision(ball, paddle->collider))
    {
        ball->pos->x -= ball->vel->x * dt;
        Vector2f* newVal = getNewVel(ball, paddle->collider);
        free(ball->vel);
        ball->vel = newVal;
    }

    // if ball hits right paddle
    if (checkCollision(ball, paddle2->collider))
    {
        ball->pos->x -= ball->vel->x * dt;
        Vector2f* newVal = getNewVel(ball, paddle2->collider);
        free(ball->vel);
        ball->vel = newVal;
    }

    // check if ball hits top or bottom
    if (ball->pos->y - ball->r < 0)
    {
        ball->pos->y = ball->r;
        ball->vel->y *= -1.5;
    }
    else if (ball->pos->y + ball->r > 600)
    {
        ball->pos->y = 600 - ball->r;
        ball->vel->y *= -1.5;
    }

    // check if ball goes off the screen left or right
    if (ball->pos->x + ball->r < 0 || ball->pos->x - ball->r > 800)
    {
        ball->pos->x = 400;
        ball->pos->y = 300;
        ball->vel->x = -200;
        ball->vel->y = 0;
    }

    if (ball->vel->x > MAX_BALL_SPEED)
            ball->vel->x = MAX_BALL_SPEED;
        else if (ball->vel->x < -MAX_BALL_SPEED)
            ball->vel->x = -MAX_BALL_SPEED;

        if (ball->vel->y > MAX_BALL_SPEED)
            ball->vel->y = MAX_BALL_SPEED;
        else if (ball->vel->y < -MAX_BALL_SPEED)
            ball->vel->y = -MAX_BALL_SPEED;
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