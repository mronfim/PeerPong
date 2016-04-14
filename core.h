//
//  core.h
//  PeerPong
//
//  Created by Matheus Barella Ronfim on 4/10/16.
//  Copyright © 2016 Matheus Barella Ronfim. All rights reserved.
//

#ifndef core_h
#define core_h

#define TRUE    1
#define FALSE   0

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>

typedef struct Window {
    unsigned int    width;
    unsigned int    height;
    char*           title;
    SDL_Window*     window;
    SDL_Surface*    surface;
    SDL_Renderer*   renderer;
} Window;

typedef struct Font {
    char* name;
    char* path;
} Font;

typedef struct Texture {
    SDL_Texture* texture;
    SDL_Rect* rect;
} Texture;

// SDL Functions ////////////////////////////////////////////

int initSDL();
void quitSDL();
Window* newWindow(char* title, int width, int height);
void freeWindow(Window** windowAddr);

// Drawing Functions ////////////////////////////////////////

SDL_Color getColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
void drawRect(Window* window, int x, int y, int w, int h, SDL_Color c);
void drawSDLRect(Window* window, SDL_Rect r, SDL_Color c);
void fillRect(Window* window, int x, int y, int w, int h, SDL_Color c);
void fillSDLRect(Window* window, SDL_Rect r, SDL_Color c);
void writeToScreen(Window* window, char* text, int x, int y, int size, Font* font, SDL_Color c);
void clearScreen(Window* window, SDL_Color);
void drawTexture(Window* window, Texture* t, int x, int y);

Texture* loadTexture(Window* window, char* path);
void deleteTexture(Texture** texture);

int getFontWidth(Font font, char* string, int size);
int getFontHeight(Font font, char* string, int size);


#endif /* core_h */
