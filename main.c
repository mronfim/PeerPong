//
//  main.c
//  PeerPong
//
//  Created by Matheus Barella Ronfim on 4/10/16.
//  Copyright © 2016 Matheus Barella Ronfim. All rights reserved.
//

#include <stdio.h>
#include "core.h"
#include "paddle.h"
#include "ball.h"
#include "timer.h"


// CONSTANTS
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const int SCREEN_FPS = 30;
const int SCREEN_TICKS_PER_FRAME = 1000.0 / SCREEN_FPS;


// VARIABLES
Window* window = NULL;
Font dimis = {"DISMIS", "res/fonts/DIMIS___.TTF"};
Font arcadepi = {"ARCADEPI", "res/fonts/ARCADEPI.TTF"};
Paddle* paddle = NULL;
Paddle* paddle2 = NULL;
Ball* ball = NULL;

int quit = 0;



// FUNCTION HEADERS
void handleInput(SDL_Event e);
void update(double dt);
void render();




int main(int argc, const char * argv[])
{
    if (!initSDL())
        return 1;
    
    if ((window = newWindow("PeerPong", WINDOW_WIDTH, WINDOW_HEIGHT)) != NULL)
    {
        SDL_Event e;
        
        paddle = newPaddle(30, 50, 25, 100, getColor(155, 0, 0, 255), getColor(255, 0, 0, 255));
        paddle2 = newPaddle(700, 0, 25, 600, getColor(0, 0, 155, 255), getColor(0, 0, 255, 255));
        ball = newBall(WINDOW_WIDTH/2, WINDOW_HEIGHT/2, 5, loadTexture(window, "res/img/ball_10.png"));
        ball->vel->y = -50;
        
        Timer* FPSTimer = newTimer();
        startTimer(FPSTimer);
        
        double accumulator = 0.0;
        double fpsTime = 0;
        int fps = 0, ticks = 0;
        
        while (!quit)
        {
            double frameTime = getTimerTicks(FPSTimer);
            accumulator += frameTime;
            fpsTime += frameTime;
            startTimer(FPSTimer);
            
            handleInput(e);
            
            // update
            while (accumulator >= SCREEN_TICKS_PER_FRAME)
            {
                update(SCREEN_TICKS_PER_FRAME / 1000.0);
                accumulator -= SCREEN_TICKS_PER_FRAME;
                ticks++;
            }
            
            // render
            render();
            fps++;
            
            
            // print fps and ticks per second
            // if (fpsTime >= 1000)
            // {
            //     printf("FPS: %d, TICKS: %d\n", fps, ticks);
            //     fpsTime = fps = ticks = 0;
            // }
        }
        
        destroyTimer(&FPSTimer);
        destroyPaddle(&paddle);
        destroyPaddle(&paddle2);
        destroyBall(&ball);
        freeWindow(&window);
    }
    
    quitSDL();
    
    return 0;
}


void handleInput(SDL_Event e)
{
    while (SDL_PollEvent(&e))
    {
        if (e.type == SDL_QUIT)
            quit = 1;
    }
    
    paddleInput(paddle, e);
}


void update(double dt)
{
    updatePaddle(paddle, dt);
    updateBall(ball, paddle, paddle2, dt);
}


void render()
{
    clearScreen(window, getColor(0, 0, 0, 255));
    renderPaddle(window, paddle);
    renderPaddle(window, paddle2);
    renderBall(window, ball);
    SDL_RenderPresent(window->renderer);
}