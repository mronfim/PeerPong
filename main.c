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
#include "timer.h"


// CONSTANTS
const int SCREEN_FPS = 30;
const int SCREEN_TICKS_PER_FRAME = 1000.0 / SCREEN_FPS;



// VARIABLES
Window* window = NULL;
Font dimis = {"DISMIS", "PeerPong/res/fonts/DIMIS___.TTF"};
Font arcadepi = {"ARCADEPI", "PeerPong/res/fonts/ARCADEPI.TTF"};
Texture* ball = NULL;
Paddle* paddle = NULL;

int quit = 0;



// FUNCTION HEADERS
void handleInput(SDL_Event e);
void update(double dt);
void render();




int main(int argc, const char * argv[])
{
    if (!initSDL())
        return 1;
    
    if ((window = newWindow("PeerPong", 640, 480)) != NULL)
    {
        SDL_Event e;
        
        ball = loadTexture(window, "PeerPong/res/img/ball_15.png");
        paddle = newPaddle(30, 50, 20, 80, getColor(155, 0, 0, 255), getColor(255, 0, 0, 255));
        
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
            if (fpsTime >= 1000)
            {
                printf("FPS: %d, TICKS: %d\n", fps, ticks);
                fpsTime = fps = ticks = 0;
            }
        }
        
        destroyTimer(&FPSTimer);
        destroyPaddle(&paddle);
        freeWindow(&window);
        deleteTexture(&ball);
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
}


void render()
{
    clearScreen(window, getColor(0, 0, 0, 255));
    renderPaddle(window, paddle);
    drawTexture(window, ball, 300, 300);
    SDL_RenderPresent(window->renderer);
}