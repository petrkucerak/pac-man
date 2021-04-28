/*******************************************************************
  Program to draw text to frame buffer on MicroZed
  based MZ_APO board designed by Petr Porazil at PiKRON

  menu_utilites.c      - functions for settings game

  (C) Copyright 2021 by Petr Kucera
      e-mail:   kucerp28@fel.cvut.cz
      license:  any combination of GPL, LGPL, MPL or BSD licenses

 *******************************************************************/

#include <stdio.h>
#include "menu_utilities.h"
#include "data_structures.h"
#include "draw_shapes.h"
#include "update_peripherals.h"
#include "text_fb.h"
#include <unistd.h>

bool run_init_game_menu(fb_data *frame_buff, unsigned char *lcd_mem_base, font_descriptor_t *font)
{
  // init game menu
  set_background(frame_buff, 0);
  draw_text_center(frame_buff, "HLAVNI MENU", frame_buff->width/2, frame_buff->height/2, 5, font, 0xffff);
  lcd_from_fb(frame_buff, lcd_mem_base);

  sleep(4);

  // menu with context
  set_background(frame_buff, 0);
  draw_text_center(frame_buff, "HLAVNI MENU", frame_buff->width/2, frame_buff->height/100, 2, font, 0xffff);
  draw_text_center(frame_buff, "pocet zivotu ... 4 [L]\nmapa ... 1 [M]\npocet duchu ... 8 [G]", frame_buff->width/2, frame_buff->height/2, 1, font, 0xffff);
  draw_text_center(frame_buff, "SPUSIT HRU ... ENTER", frame_buff->width/2, frame_buff->height - frame_buff->height/100, 1, font, 0xffff);

  lcd_from_fb(frame_buff, lcd_mem_base);

  return true;
}
