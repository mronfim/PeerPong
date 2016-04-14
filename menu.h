//
//  menu.h
//  PeerPong
//
//  Created by Matheus Barella Ronfim on 4/12/16.
//  Copyright © 2016 Matheus Barella Ronfim. All rights reserved.
//

#ifndef MENU_H
#define MENU_H

#include "core.h"


typedef struct MenuItem {
	int x;
	int y;
	char text[24];
	Font font;
	int fontSize;
	SDL_Color color;
	SDL_Color highlight;
	int selected;
} MenuItem;

typedef struct Title {
	int x;
	int y;
	char text[24];
	SDL_Color color;
	int fontSize;
	Font font;
} Title;

typedef struct Menu {
	Title title;
	MenuItem options[10];
	int num_options;
	int selected;
	int active;
} Menu;


Menu* newMenu();
void destroyMenu(Menu** menu);

void menu_move_selector(Menu* menu, int offset);
char* menu_get_selected(Menu* menu);

void menu_draw(Window* window, Menu* menu);

#endif