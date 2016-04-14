#ifndef pongfunctions_h
#define pongfunctions_h

#include "pongstructs.h"

void paddleInput(Paddle* paddle, SDL_Event e);
void updatePaddle(Paddle* paddle, float dt);
void renderPaddle(Window* window, Paddle* paddle);

void updateAI(Paddle* paddle, struct Ball* ball, float dt);


void updateBall(Ball* ball, Paddle* paddle, Paddle* paddle2, float dt);
void renderBall(Window* window, Ball* ball);
int checkCollision(Ball* ball, SDL_Rect rect);

#endif
