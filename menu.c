//
//  menu.c
//  PeerPong
//
//  Created by Matheus Barella Ronfim on 4/12/16.
//  Copyright © 2016 Matheus Barella Ronfim. All rights reserved.
//

#include "menu.h"
#include <string.h>

Menu* newMenu()
{
	Menu* menu = (Menu *) malloc(sizeof(Menu));
	return menu;
}

void destroyMenu(Menu** menu)
{
	free(*menu);
}

void menu_move_selector(Menu* menu, int offset)
{
	menu->options[menu->selected].selected = 0;

	menu->selected += offset;
	if (menu->selected > menu->num_options)
		menu->selected = menu->num_options;

	else if (menu->selected < 0)
		menu->selected = 0;

	menu->options[menu->selected].selected = 1;
}

char* menu_get_selected(Menu* menu)
{
	return menu->options[menu->selected].text;
}

void draw_option(Window* window, MenuItem item)
{
	if (item.selected)
		writeToScreen(window, item.text, item.x, item.y, item.fontSize, &(item.font), item.highlight);
	else
		writeToScreen(window, item.text, item.x, item.y, item.fontSize, &(item.font), item.color);
}

void menu_draw(Window* window, Menu* menu)
{
	// draw title to screen
	writeToScreen(window, menu->title.text, menu->title.x, menu->title.y, menu->title.fontSize, &(menu->title.font), menu->title.color);

	// draw each option
	int i;
	for (i = 0; i < menu->num_options; i++)
		draw_option(window, menu->options[i]);
}