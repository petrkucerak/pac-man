/**
 * @file menu_utilities.c
 * @author Petr Kucera (kucerp28@fel.cvut.cz)
 * @brief Module for drawing menu, setting game settings and starting the game
 * @version 0.1
 * @date 2021-05-04
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <stdio.h>
#include "menu_utilities.h"
#include "map_template.h"
#include "data_structures.h"
#include "draw_shapes.h"
#include "update_peripherals.h"
#include "text_fb.h"
#include "game.h"
#include "final_score.h"
#include "config.h"
#include <unistd.h>

#define HEIGHT_M frame_buff->height

void run_init_game_menu(fb_data *frame_buff, unsigned char *lcd_mem_base,
                        font_descriptor_t *font, peripherals_data_t peripherals)
{
  // init game menu
  set_background(frame_buff, 0);
  draw_text_center(frame_buff, "PAC-MAN", frame_buff->width / 2, HEIGHT_M / 2, 5, font, 0xffff);
  lcd_from_fb(frame_buff, lcd_mem_base);
  sleep(2);
  bool play_game_again = true;
  game_init_data_t game = {.pacman_lives = 3, .ghost_nr = 3, .map = &map_circles};
  while (play_game_again)
  {
    // menu with context
    draw_menu(frame_buff, font, game);
    lcd_from_fb(frame_buff, lcd_mem_base);
    // listen symbol
    char read = ' ';
    while (read != 's' && read != 't' && read != 'S' && read != 'T')
    {
      // scan input
      pthread_mutex_lock(&mtx);
      pthread_cond_wait(&character_has_been_read, &mtx);
      read = read_thread_data.last_read;
      pthread_mutex_unlock(&mtx);
      if (read == 'l' || read == 'L')
      {
        game = sub_menu_lives(frame_buff, lcd_mem_base, font, game);
      }
      if (read == 'm' || read == 'M')
      {
        game = sub_menu_map(frame_buff, lcd_mem_base, font, game);
      }
      if (read == 'g' || read == 'G')
      {
        game = sub_menu_ghosts(frame_buff, lcd_mem_base, font, game);
      }
      // redraw menu
      draw_menu(frame_buff, font, game);
      lcd_from_fb(frame_buff, lcd_mem_base);
    }
    if (read != 't' && read != 'T')
    {
      // run game
      int game_score = run_game(&game, &peripherals);
      // draw packman score
      play_game_again = draw_final_score(game_score, frame_buff, lcd_mem_base, font);
    }
    else
    {
      play_game_again = false;
    }
  }
}

void draw_menu(fb_data *frame_buff, font_descriptor_t *font, game_init_data_t game_data)
{
  // menu with context
  set_background(frame_buff, 0);
  draw_text_center(frame_buff, "HLAVNI MENU", frame_buff->width / 2, HEIGHT_M / 10, 3, font, 0xffff);
  char string_tmp[40];
  snprintf(string_tmp, 40, "pocet zivotu: %d [L]", game_data.pacman_lives);
  draw_text_center(frame_buff, string_tmp, frame_buff->width / 2, HEIGHT_M / 2 - HEIGHT_M / 7, 2, font, 0xffff);
  snprintf(string_tmp, 40, "mapa: %s [M]", game_data.map->name);
  draw_text_center(frame_buff, string_tmp, frame_buff->width / 2, HEIGHT_M / 2, 2, font, 0xffff);
  snprintf(string_tmp, 40, "pocet duchu: %d [G]", game_data.ghost_nr);
  draw_text_center(frame_buff, string_tmp, frame_buff->width / 2, HEIGHT_M / 2 + HEIGHT_M / 7, 2, font, 0xffff);
  draw_text_center(frame_buff, "SPUSIT HRU: [S] KONEC HRY: [T]", frame_buff->width / 2, HEIGHT_M - HEIGHT_M / 10, 2, font, 0xffff);
}

game_init_data_t sub_menu_lives(fb_data *frame_buff, unsigned char *lcd_mem_base, font_descriptor_t *font, game_init_data_t game_data)
{
  char c = ' ';
  while (c != 'c' && c != 'C')
  {
    set_background(frame_buff, 0);
    draw_text_center(frame_buff, "NASTAVENI ZIVOTU", frame_buff->width / 2, HEIGHT_M / 10, 3, font, 0xffff);
    draw_text_center(frame_buff, "aktualni pocet zivotu", frame_buff->width / 2, HEIGHT_M / 2 - HEIGHT_M / 7, 2, font, 0xffff);
    char string_tmp[40];
    snprintf(string_tmp, 40, "%d", game_data.pacman_lives);
    draw_text_center(frame_buff, string_tmp, frame_buff->width / 2, HEIGHT_M / 2, 3, font, 0xffff);
    snprintf(string_tmp, 40, "zmackni cislo (max %c)", MAX_LIVES);
    draw_text_center(frame_buff, string_tmp, frame_buff->width / 2, HEIGHT_M / 2 + HEIGHT_M / 7, 2, font, 0xffff);
    draw_text_center(frame_buff, "POTVRDIT: [C]", frame_buff->width / 2, HEIGHT_M - HEIGHT_M / 10, 2, font, 0xffff);
    // update display
    lcd_from_fb(frame_buff, lcd_mem_base);
    // scan input
    pthread_mutex_lock(&mtx);
    pthread_cond_wait(&character_has_been_read, &mtx);
    c = read_thread_data.last_read;
    pthread_mutex_unlock(&mtx);
    // listen orders
    if (c > '0' && c <= MAX_LIVES)
    {
      game_data.pacman_lives = c - '0';
    }
  }
  return game_data;
}

game_init_data_t sub_menu_map(fb_data *frame_buff, unsigned char *lcd_mem_base, font_descriptor_t *font, game_init_data_t game_data)
{
  static int i = 0;
  map_template *map_templates[] = {&map_circles, &map_star, &map_conch};
  size_t map_templates_len = sizeof(map_templates) / sizeof(map_templates[0]);
  while (map_templates[i]->name != game_data.map->name)
  {
    ++i;
  }
  char c = ' ';
  while (c != 'c' && c != 'C')
  {
    set_background(frame_buff, 0);
    draw_text_center(frame_buff, "VOLBA MAPY", frame_buff->width / 2, HEIGHT_M / 10, 3, font, 0xffff);
    draw_text_center(frame_buff, "aktualni mapa", frame_buff->width / 2, HEIGHT_M / 2 - HEIGHT_M / 7, 2, font, 0xffff);
    char string_tmp[40];
    snprintf(string_tmp, 40, "<  %s  >", game_data.map->name);
    draw_text_center(frame_buff, string_tmp, frame_buff->width / 2, HEIGHT_M / 2, 3, font, 0xffff);
    draw_text_center(frame_buff, "vybirej klavesami [A] [D]", frame_buff->width / 2, HEIGHT_M / 2 + HEIGHT_M / 7, 2, font, 0xffff);
    draw_text_center(frame_buff, "POTVRDIT: [C]", frame_buff->width / 2, HEIGHT_M - HEIGHT_M / 10, 2, font, 0xffff);
    // update display
    lcd_from_fb(frame_buff, lcd_mem_base);
    // scan input
    pthread_mutex_lock(&mtx);
    pthread_cond_wait(&character_has_been_read, &mtx);
    c = read_thread_data.last_read;
    pthread_mutex_unlock(&mtx);
    // listen orders
    if (c == 'a' || c == 'A')
    {
      i = (i - 1 + map_templates_len) % map_templates_len;
    }
    if (c == 'd' || c == 'D')
    {
      i = (i + 1 + map_templates_len) % map_templates_len;
    }
    game_data.map = map_templates[i];
  }
  return game_data;
}

game_init_data_t sub_menu_ghosts(fb_data *frame_buff, unsigned char *lcd_mem_base, font_descriptor_t *font, game_init_data_t game_data)
{
  char c = ' ';
  while (c != 'c' && c != 'C')
  {
    // set buffer
    set_background(frame_buff, 0);
    draw_text_center(frame_buff, "NASTAVENI DUCHU", frame_buff->width / 2, HEIGHT_M / 10, 3, font, 0xffff);
    draw_text_center(frame_buff, "aktualni pocet duchu", frame_buff->width / 2, HEIGHT_M / 2 - HEIGHT_M / 7, 2, font, 0xffff);
    char string_tmp[40];
    snprintf(string_tmp, 40, "%d", game_data.ghost_nr);
    draw_text_center(frame_buff, string_tmp, frame_buff->width / 2, HEIGHT_M / 2, 3, font, 0xffff);
    snprintf(string_tmp, 40, "zmackni cislo (max %c)", MAX_GHOSTS);
    draw_text_center(frame_buff, string_tmp, frame_buff->width / 2, HEIGHT_M / 2 + HEIGHT_M / 7, 2, font, 0xffff);
    draw_text_center(frame_buff, "POTVRDIT: [C]", frame_buff->width / 2, HEIGHT_M - HEIGHT_M / 10, 2, font, 0xffff);
    // update display
    lcd_from_fb(frame_buff, lcd_mem_base);
    // scan input
    pthread_mutex_lock(&mtx);
    pthread_cond_wait(&character_has_been_read, &mtx);
    c = read_thread_data.last_read;
    pthread_mutex_unlock(&mtx);
    // listen orders
    if (c > '0' && c <= MAX_GHOSTS)
    {
      game_data.ghost_nr = c - '0';
    }
  }
  return game_data;
}
