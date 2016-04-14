
#include "pongfunctions.h"


#define PADDLE_SPEED 250
#define PADDLE_AI_SPEED 320
#define MIN_BALL_SPEED 200
#define MAX_BALL_SPEED 400


void paddleInput(Paddle* paddle, SDL_Event e)
{
    if (e.type == SDL_KEYDOWN)
    {
        switch (e.key.keysym.sym)
        {
            case SDLK_UP:
                paddle->vel->y = -PADDLE_SPEED;
                break;
            case SDLK_DOWN:
                paddle->vel->y = PADDLE_SPEED;
                break;
        }
    }
    
    else if (e.type == SDL_KEYUP)
    {
        switch (e.key.keysym.sym)
        {
            case SDLK_UP:
                paddle->vel->y = 0;
                break;
            case SDLK_DOWN:
                paddle->vel->y = 0;
                break;
        }
    }
}

void updatePaddle(Paddle* paddle, float dt)
{
    paddle->pos->y += paddle->vel->y * dt;
    paddle->collider.y = paddle->pos->y;
}

void renderPaddle(Window* window, Paddle* paddle)
{
    fillSDLRect(window, paddle->collider, paddle->baseColor);
    drawSDLRect(window, paddle->collider, paddle->borderColor);
}

void updateAI(Paddle* paddle, struct Ball* ball, float dt)
{
    // distance from ball to the center of the paddle, in y axis
    int distance = (int)(ball->pos->y) - (int)(paddle->pos->y + paddle->h/2);

    // if distance is negative, move up
    if (distance < 0)
        paddle->vel->y = -PADDLE_AI_SPEED;
    // if distance is positive, move down
    else if (distance > 0)
        paddle->vel->y = PADDLE_AI_SPEED;
    // if distance is zero, stop moving
    else
        paddle->vel->y = 0.f;

    // update position
    paddle->pos->y += paddle->vel->y * dt;

    if ( paddle->pos->y + paddle->h/2 > ball->pos->y && paddle->vel->y > 0 )
        paddle->pos->y = ball->pos->y - paddle->h/2;
    else if ( paddle->pos->y + paddle->h/2 < ball->pos->y && paddle->vel->y < 0 )
        paddle->pos->y = ball->pos->y - paddle->h/2;

    paddle->collider.y = paddle->pos->y;
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
        if (ball->pos->x + ball->r < 0)
            paddle2->score++;
        else if (ball->pos->x + ball->r > 800)
            paddle->score++;

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


    free(ball->trail[8]);

    int i;
    for (i = 8; i > 0; i--)
    {
        ball->trail[i] = ball->trail[i-1];
    }
    ball->trail[0] = vec2f_new( ball->pos->x, ball->pos->y );
}

void renderBall(Window* window, Ball* ball)
{
    int width = ball->r;

    int i;
    for (i = 1; i < 4; i += 1)
    {
        int size = width * (1.0 / i);
        SDL_Rect r = { ball->trail[i]->x - size/2, ball->trail[i]->y - size/2, size, size };
        fillSDLRect(window, r, getColor(150, 150, 150, 255));
    }

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
        return 1;
    }
    
    return 0;
}