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
        
        Font font = {"DISMIS", "PeerPong/res/fonts/DIMIS___.TTF"};
        Texture* ball = loadTexture(window, "PeerPong/res/img/ball.png");
        
        while (!quit)
        {
            while (SDL_PollEvent(&e))
            {
                if (e.type == SDL_QUIT)
                    quit = 1;
            }
            
            clearScreen(window, getColor(0, 0, 0, 255));
            writeToScreen(window, "PeerPong", 100, 50, 50, &font, getColor(255, 255, 255, 255));
            drawTexture(window, ball, 300, 300);
            SDL_RenderPresent(window->renderer);
        }
    }
    
    quitSDL();
    
    return 0;
}
