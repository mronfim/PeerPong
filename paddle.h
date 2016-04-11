//
//  paddle.h
//  PeerPong
//
//  Created by Matheus Barella Ronfim on 4/11/16.
//  Copyright © 2016 Matheus Barella Ronfim. All rights reserved.
//

#ifndef paddle_h
#define paddle_h

#include <stdio.h>
#include "core.h"
#include "vector.h"

typedef struct Paddle {
    Vector2f* pos;
    Vector2f* vel;
    int w;
    int h;
    SDL_Color baseColor;
    SDL_Color borderColor;
    SDL_Rect collider;
} Paddle;

Paddle* newPaddle(int x, int y, int w, int h, SDL_Color baseColor, SDL_Color borderColor);
void destroyPaddle(Paddle** paddle);
void updatePaddle(Paddle* paddle, float dt);
void renderPaddle(Window* window, Paddle* paddle);

#endif /* paddle_h */
