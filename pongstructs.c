
#include "pongstructs.h"



Paddle* newPaddle(int x, int y, int w, int h, SDL_Color baseColor, SDL_Color borderColor)
{
    Paddle* paddle = (Paddle *)malloc(sizeof(Paddle));
    paddle->pos = vec2f_new((float)x, (float)y);
    paddle->vel = vec2f_new(0.f, 0.f);
    paddle->w = w;
    paddle->h = h;
    paddle->baseColor = baseColor;
    paddle->borderColor = borderColor;
    paddle->collider.x = x;
    paddle->collider.y = y;
    paddle->collider.w = w;
    paddle->collider.h = h;
    return paddle;
    
}

void destroyPaddle(Paddle** paddle)
{
    free((*paddle)->pos);
    free((*paddle)->vel);
    free(*paddle);
}




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