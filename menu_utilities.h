/*******************************************************************
  Program to draw text to frame buffer on MicroZed
  based MZ_APO board designed by Petr Porazil at PiKRON

  menu_utilites.h      - functions for settings game

  (C) Copyright 2021 by Petr Kucera
      e-mail:   kucerp28@fel.cvut.cz
      license:  any combination of GPL, LGPL, MPL or BSD licenses

 *******************************************************************/
#include <stdbool.h>
#include "data_structures.h"
#include "font_types.h"

#ifndef MENU_UTILITIES_H
#define MENU_UTILITIES_H

bool run_init_game_menu(fb_data *frame_buff, unsigned char *lcd_mem_base, font_descriptor_t *font);

/**
 * function to drow menu with settings to fb_data
 * (for propagate changes need to render data from buffer)
 */
void draw_menu(fb_data *frame_buff, font_descriptor_t *font, game_init_data_t game_data);

/**
 * function draw sub menu and update count of lives
 */
game_init_data_t sub_menu_lives(fb_data *frame_buff, unsigned char *lcd_mem_base, font_descriptor_t *font, game_init_data_t game_data);
game_init_data_t sub_menu_map(fb_data *frame_buff, unsigned char *lcd_mem_base, font_descriptor_t *font, game_init_data_t game_data);

/**
 * function draw sub menu and update count of ghosts
 */
game_init_data_t sub_menu_ghosts(fb_data *frame_buff, unsigned char *lcd_mem_base, font_descriptor_t *font, game_init_data_t game_data);

#endif
