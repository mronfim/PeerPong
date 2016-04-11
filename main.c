//
//  main.c
//  PeerPong
//
//  Created by Matheus Barella Ronfim on 4/10/16.
//  Copyright © 2016 Matheus Barella Ronfim. All rights reserved.
//

#include <stdio.h>
#include "core.h"

int main(int argc, const char * argv[])
{
    if (!initSDL())
        return 1;
    
    Window* window = NULL;
    if ((window = newWindow("PeerPong", 640, 480)) != NULL)
    {
        int quit = 0;
        SDL_Event e;
        
        Font dimis = {"DISMIS", "PeerPong/res/fonts/DIMIS___.TTF"};
        Font arcadepi = {"ARCADEPI", "PeerPong/res/fonts/ARCADEPI.TTF"};
        Texture* ball = loadTexture(window, "PeerPong/res/img/ball_15.png");
        
        while (!quit)
        {
            while (SDL_PollEvent(&e))
            {
                if (e.type == SDL_QUIT)
                    quit = 1;
            }
            
            clearScreen(window, getColor(0, 0, 0, 255));
            fillRect(window, 30, 100, 20, 100, getColor(0, 0, 155, 255));
            drawRect(window, 30, 100, 20, 100, getColor(0, 0, 255, 255));
            drawTexture(window, ball, 300, 300);
            SDL_RenderPresent(window->renderer);
        }
    }
    
    quitSDL();
    
    return 0;
}
