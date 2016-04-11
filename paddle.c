//
//  paddle.c
//  PeerPong
//
//  Created by Matheus Barella Ronfim on 4/11/16.
//  Copyright © 2016 Matheus Barella Ronfim. All rights reserved.
//

#include "paddle.h"

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

void updatePaddle(Paddle* paddle, float dt)
{
    // TODO: Add movement and collision detection
}

void renderPaddle(Window* window, Paddle* paddle)
{
    fillSDLRect(window, paddle->collider, paddle->baseColor);
    drawSDLRect(window, paddle->collider, paddle->borderColor);
}



































