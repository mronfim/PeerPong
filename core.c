//
//  core.c
//  PeerPong
//
//  Created by Matheus Barella Ronfim on 4/10/16.
//  Copyright © 2016 Matheus Barella Ronfim. All rights reserved.
//

#include "core.h"


// SDL Functions ////////////////////////////////////////////

int initSDL()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        printf("Unable to initialize SDL! SDL Error: %s\n", SDL_GetError());
        return FALSE;
    }
    
    if (TTF_Init() < 0)
        printf("Unable to initialize TTF! TTF Error: %s\n", TTF_GetError());
    
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
        printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
    
    return TRUE;
}

void quitSDL()
{
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
}

Window* newWindow(char* title, int width, int height)
{
    Window* window = (Window *) malloc(sizeof(Window));
    
    window->width = width;
    window->height = height;
    window->window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
    if (window->window == NULL)
    {
        printf("Failed to create Window! SDL_Error: %s\n", SDL_GetError());
        free(window);
        return NULL;
    }
    
    window->surface = SDL_GetWindowSurface(window->window);
    window->renderer = SDL_GetRenderer(window->window);
    
    return window;
}

void freeWindow(Window** windowAddr)
{
    Window* window = *windowAddr;
    
    SDL_FreeSurface(window->surface);
    SDL_DestroyWindow(window->window);
    
    window->window = NULL;
    window->surface = NULL;
    
    free(*windowAddr);
    *windowAddr = NULL;
}

// Drawing Functions ////////////////////////////////////////

SDL_Color getColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
    SDL_Color c = {r,g,b,a};
    return c;
}

void drawRect(Window* window, int x, int y, int w, int h, SDL_Color c)
{
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;
    
    SDL_SetRenderDrawColor(window->renderer, c.r, c.g, c.b, c.a);
    SDL_RenderDrawRect(window->renderer, &rect);
}

void drawSDLRect(Window* window, SDL_Rect r, SDL_Color c)
{
    drawRect(window, r.x, r.y, r.w, r.h, c);
}

void fillRect(Window* window, int x, int y, int w, int h, SDL_Color c)
{
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;
    
    SDL_SetRenderDrawColor(window->renderer, c.r, c.g, c.b, c.a);
    SDL_RenderFillRect(window->renderer, &rect);
}

void fillSDLRect(Window* window, SDL_Rect r, SDL_Color c)
{
    fillRect(window, r.x, r.y, r.w, r.h, c);
}

void writeToScreen(Window* window, char* text, int x, int y, int size, Font* font, SDL_Color c)
{
    TTF_Font* f = TTF_OpenFont(font->path, size);
    if (f == NULL)
    {
        printf("Could not load font. TTF_Error: %s\n", TTF_GetError());
        return;
    }
    
    SDL_Surface* surface = TTF_RenderText_Solid(f, text, c);
    if (surface == NULL)
    {
        printf("Could not creature text surface");
        return;
    }
    
    SDL_Texture* t = SDL_CreateTextureFromSurface(window->renderer, surface);
    SDL_Rect rect = {x, y, surface->w, surface->h};
    
    SDL_RenderCopy(window->renderer, t, NULL, &rect);
    
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(t);
    TTF_CloseFont(f);
}

void clearScreen(Window* window, SDL_Color c)
{
    SDL_SetRenderDrawColor(window->renderer, c.r, c.g, c.b, c.a);
    SDL_RenderClear(window->renderer);
}

Texture* loadTexture(Window* window, char* path)
{
    SDL_Texture* newtexture = NULL;
    SDL_Surface* loadedSurface = IMG_Load(path);
    if (loadedSurface == NULL)
        printf("Unable to load image %s! SDL_image Error: %s\n", path, IMG_GetError());
    else
    {
        newtexture = SDL_CreateTextureFromSurface(window->renderer, loadedSurface);
        if (newtexture == NULL)
            printf("Unable to create texture from %s! SDL Error: %s\n", path, SDL_GetError());
        SDL_FreeSurface(loadedSurface);
    }
    
    SDL_Rect* r = (SDL_Rect *) malloc(sizeof(SDL_Rect));
    r->x = 0;
    r->y = 0;
    r->w = loadedSurface->w;
    r->h = loadedSurface->h;
    
    Texture* t = (Texture *) malloc(sizeof(Texture));
    t->texture = newtexture;
    t->rect = r;
    return t;
}

void drawTexture(Window* window, Texture* t, int x, int y)
{
    SDL_Rect r = {x, y, t->rect->w, t->rect->h};
    SDL_RenderCopy(window->renderer, t->texture, NULL, &r);
}

void deleteTexture(Texture** texture)
{
    free((*texture)->texture);
    free((*texture)->rect);
    free(*texture);
}





































