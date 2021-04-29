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

#define HEIGHT_M frame_buff->height

bool run_init_game_menu(fb_data *frame_buff, unsigned char *lcd_mem_base, font_descriptor_t *font)
{
  // init game menu
  set_background(frame_buff, 0);
  draw_text_center(frame_buff, "HLAVNI MENU", frame_buff->width / 2, HEIGHT_M / 2, 5, font, 0xffff);
  lcd_from_fb(frame_buff, lcd_mem_base);

  sleep(4);

  // menu with context
  game_init_data_t game = {.pacman_lives = 3, .ghost_nr = 3, .map = &map_circles};
  draw_menu(frame_buff, font, game);
  lcd_from_fb(frame_buff, lcd_mem_base);

  // listen symbol
  char read;
  while (true)
  {
    read = getchar();
    if (read == 's')
      break;
    if (read == 'l')
    {
      game = sub_menu_lives(frame_buff, lcd_mem_base, font, game);
    }
    if (read == 'm')
    {
      game = sub_menu_map(frame_buff, lcd_mem_base, font, game);
    }
    if (read == 'g')
    {
      game = sub_menu_ghosts(frame_buff, lcd_mem_base, font, game);
    }

    draw_menu(frame_buff, font, game);
    lcd_from_fb(frame_buff, lcd_mem_base);
  }

  return true;
}

void draw_menu(fb_data *frame_buff, font_descriptor_t *font, game_init_data_t game_data)
{
  // menu with context
  set_background(frame_buff, 0);
  draw_text_center(frame_buff, "HLAVNI MENU", frame_buff->width / 2, HEIGHT_M / 10, 3, font, 0xffff);

  char string_tmp[40];
  sprintf(string_tmp, "pocet zivotu: %d [l]", game_data.pacman_lives);
  draw_text_center(frame_buff, string_tmp, frame_buff->width / 2, HEIGHT_M / 2 - HEIGHT_M / 7, 2, font, 0xffff);

  sprintf(string_tmp, "mapa: %s [m]", game_data.map->name);
  draw_text_center(frame_buff, string_tmp, frame_buff->width / 2, HEIGHT_M / 2, 2, font, 0xffff);

  sprintf(string_tmp, "pocet duchu: %d [g]", game_data.ghost_nr);
  draw_text_center(frame_buff, string_tmp, frame_buff->width / 2, HEIGHT_M / 2 + HEIGHT_M / 7, 2, font, 0xffff);

  draw_text_center(frame_buff, "SPUSIT HRU: [s]", frame_buff->width / 2, HEIGHT_M - HEIGHT_M / 10, 2, font, 0xffff);
}

game_init_data_t sub_menu_lives(fb_data *frame_buff, unsigned char *lcd_mem_base, font_descriptor_t *font, game_init_data_t game_data)
{
  char c;
  while (true)
  {
    // set buffer
    set_background(frame_buff, 0);
    draw_text_center(frame_buff, "NASTAVENI ZIVOTU", frame_buff->width / 2, HEIGHT_M / 10, 3, font, 0xffff);
    draw_text_center(frame_buff, "aktualni pocet zivotu", frame_buff->width / 2, HEIGHT_M / 2 - HEIGHT_M / 7, 2, font, 0xffff);

    char string_tmp[40];
    sprintf(string_tmp, "%d", game_data.pacman_lives);
    draw_text_center(frame_buff, string_tmp, frame_buff->width / 2, HEIGHT_M / 2, 3, font, 0xffff);

    draw_text_center(frame_buff, "zmackni cislo (max 4)", frame_buff->width / 2, HEIGHT_M / 2 + HEIGHT_M / 7, 2, font, 0xffff);
    draw_text_center(frame_buff, "POTVRDIT: [s]", frame_buff->width / 2, HEIGHT_M - HEIGHT_M / 10, 2, font, 0xffff);
    
    // update display
    lcd_from_fb(frame_buff, lcd_mem_base);

    // listen orders
    c = getchar();
    if(c == 's') return game_data;
    if(c > 48 && c < 53){
      game_data.pacman_lives = c - 48;
    }
  }
}

game_init_data_t sub_menu_map(fb_data *frame_buff, unsigned char *lcd_mem_base, font_descriptor_t *font, game_init_data_t game_data)
{

  return game_data;
}

game_init_data_t sub_menu_ghosts(fb_data *frame_buff, unsigned char *lcd_mem_base, font_descriptor_t *font, game_init_data_t game_data)
{

  return game_data;
}
