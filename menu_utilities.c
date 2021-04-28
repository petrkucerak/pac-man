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

bool run_init_game_menu(fb_data *frame_buff, unsigned char *lcd_mem_base, font_descriptor_t *font)
{
  printf("run init game menu\n");

  welcome_screen(frame_buff);
  lcd_from_fb(frame_buff, lcd_mem_base);
  printf("background set\n");

  char text[] = "HLAVNI MENU";
  draw_text_center(frame_buff, text, 0, 0, 10, font, 0x1f);

  return true;

}

void welcome_screen(fb_data *frame_buff)
{
  set_background(frame_buff, 0);
  for(int i=0; i<frame_buff->width*frame_buff->height; ++i){
    if(i%30<15) frame_buff->fb[i] = 0x1f;
  }
}
