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

void welcome_screen(fb_data *frame_buff);

#endif
