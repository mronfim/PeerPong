//
//  main.c
//  PeerPong
//
//  Created by Matheus Barella Ronfim on 4/10/16.
//  Copyright © 2016 Matheus Barella Ronfim. All rights reserved.
//

#include <stdio.h>
#include "core.h"
#include "pongstructs.h"
#include "pongfunctions.h"
#include "timer.h"
#include "menu.h"


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
SDL_Rect divider;

int quit = 0;


Menu* main_menu;


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
        
        paddle = newPaddle(30, 250, 25, 100, getColor(0, 0, 120, 255), getColor(0, 0, 255, 255));
        paddle2 = newPaddle(745, 250, 25, 100, getColor(120, 0, 0, 255), getColor(255, 0, 0, 255));
        ball = newBall(WINDOW_WIDTH/2, WINDOW_HEIGHT/2, 10, loadTexture(window, "res/img/ball.png"));
        ball->vel->y = -50;

        divider.x = 399;
        divider.y = 0;
        divider.w = 2;
        divider.h = 600;
        
        Timer* FPSTimer = newTimer();
        startTimer(FPSTimer);


        // main menu setup
        Title t = { 0, 100, "PeerPong", getColor(255, 255, 255, 255), 130, dimis };
        t.x = WINDOW_WIDTH/2 - getFontWidth(t.font, t.text, t.fontSize)/2;

        MenuItem item1 = { 325, 300, "SINGLE PLAYER", arcadepi, 40, getColor(255,255,255,255), getColor(255,0,0,255), 1 };
        item1.x = WINDOW_WIDTH/2 - getFontWidth(item1.font, item1.text, item1.fontSize)/2;

        MenuItem item2 = { 325, 350, "MULTIPLAYER", arcadepi, 40, getColor(255,255,255,255), getColor(255,0,0,255), 0 };
        item2.x = WINDOW_WIDTH/2 - getFontWidth(item2.font, item2.text, item2.fontSize)/2;

        MenuItem item3 = { 325, 400, "QUIT", arcadepi, 40, getColor(255,255,255,255), getColor(255,0,0,255), 0 };
        item3.x = WINDOW_WIDTH/2 - getFontWidth(item3.font, item3.text, item3.fontSize)/2;

        main_menu = newMenu();
        main_menu->title = t;
        main_menu->options[0] = item1;
        main_menu->options[1] = item2;
        main_menu->options[2] = item3;
        main_menu->num_options = 3;
        main_menu->selected = 0;
        main_menu->active = 1;

        
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
        
        destroyMenu(&main_menu);
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

        else if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
        {
            if (main_menu->active)
            {
                if (e.key.keysym.sym == SDLK_UP)
                    menu_move_selector(main_menu, -1);
                else if (e.key.keysym.sym == SDLK_DOWN)
                    menu_move_selector(main_menu,  1);
                else if (e.key.keysym.sym == SDLK_RETURN)
                {
                    char* options = menu_get_selected(main_menu);
                    if (strcmp( options, "SINGLE PLAYER" ) == 0)
                    {
                        main_menu->active = 0;
                    }
                    else if (strcmp( options, "QUIT" ) == 0)
                    {
                        quit = 1;
                    }
                }
            }
            else
            {
                if (e.key.keysym.sym == SDLK_ESCAPE)
                {
                    main_menu->active = 1;
                }
            }
        }
    }
    
    if (!main_menu->active)
    {
        paddleInput(paddle, e);
    }   
}


void update(double dt)
{
    if (!main_menu->active)
    {
        updatePaddle(paddle, dt);
        updateAI(paddle2, ball, dt);
        updateBall(ball, paddle, paddle2, dt);
    }
}


void render()
{
    clearScreen(window, getColor(0, 0, 0, 255));

    if (main_menu->active)
    {
        menu_draw(window, main_menu);
    }
    else
    {
        fillSDLRect(window, divider, getColor(255,255,255,255));
        renderPaddle(window, paddle);
        renderPaddle(window, paddle2);
        renderBall(window, ball);

        char score1buff[24];
        sprintf(score1buff, "%d", paddle->score);
        int width1 = getFontWidth(arcadepi, score1buff, 40);
        writeToScreen(window, score1buff, 370 - width1, 30, 40, &arcadepi, getColor(0, 0, 255, 0));

        char score2buff[24];
        sprintf(score2buff, "%d", paddle2->score);
        int width2 = getFontWidth(arcadepi, score2buff, 40);
        writeToScreen(window, score2buff, 430, 30, 40, &arcadepi, getColor(255, 0, 0, 0));
    }
    SDL_RenderPresent(window->renderer);
}