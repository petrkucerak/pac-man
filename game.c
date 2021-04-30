/*******************************************************************
  Program to draw text to frame buffer on MicroZed
  based MZ_APO board designed by Petr Porazil at PiKRON

  game.c      - file with game logic

  (C) Copyright 2021 by Petr Kucera, Lukas Nejezchleb
      e-mail:   kucerp28@fel.cvut.cz, nejezluk@fel.cvut.cz
      license:  any combination of GPL, LGPL, MPL or BSD licenses

 *******************************************************************/

#include "game.h"
#include "update_peripherals.h"
#include <stdlib.h>
#include <stdio.h>
#include "draw_shapes.h"
#include "map_to_fb.h"
#include "map_from_template.h"
#include "config.h"

int run_game(game_init_data_t *game_data, peripherals_data_t *peripherals)
{
  map_data *map = create_map_data(peripherals->lcd_w, peripherals->lcd_h, game_data->map);
  if (map == NULL)
  {
    // return to show error with malloc
    return -1;
  }
  fb_data fb;
  fb.fb = malloc(sizeof(uint16_t) * peripherals->lcd_w * peripherals->lcd_h);
  fb.width = peripherals->lcd_w;
  fb.height = peripherals->lcd_h;
  if (fb.fb == NULL)
  {
    free(map->board_arr);
    free(map);
    return -1;
  }
  pacman_type pacman = create_pacman(game_data->map, peripherals->lcd_w, peripherals->lcd_h,
                                     game_data->pacman_lives);
  ghost_type ghost[game_data->ghost_nr];
  for (int i = 0; i < game_data->ghost_nr; ++i)
  {
    ghost[i] = create_ghost(game_data->map, peripherals->lcd_w, peripherals->lcd_h, i);
  }
  // actual game
  char read = ' ';
  bool coins_to_eat = true;
  int scare_countdown = -1;
  uint32_t rgb_color = 0;
  while ((read != 'q') && (pacman.lives > 0) && (coins_to_eat))
  {
    if (scare_countdown == 0)
    {
      for (int j = 0; j < game_data->ghost_nr; ++j)
      {
        ghost[j].scared = false;
        ghost[j].moving_randomly = true;
        scare_countdown = -1;
      }
    }
    else if (scare_countdown > 0)
    {
      scare_countdown--;
    }

    if (pacman_move(&pacman, map)) // eaten supercoin
    {
      scare_countdown = SCARE_REGIME_DURATION;
      rgb_color = 0xf;
      for (int j = 0; j < game_data->ghost_nr; ++j)
      {
        ghost[j].scared = true;
        ghost[j].moving_randomly = true;
      }
    }
    bool scare_regime = false;
    for (int i = 0; i < game_data->ghost_nr; ++i)
    {
      // move every ghost and check if pacman has not been eaten
      if (ghost_move(&ghost[i], map, &pacman))
      {
        pacman = create_pacman(game_data->map, peripherals->lcd_w, peripherals->lcd_h,
                               pacman.lives - 1);
        for (int j = 0; j < game_data->ghost_nr; ++j)
        {
          ghost[j] = create_ghost(game_data->map, peripherals->lcd_w, peripherals->lcd_h, j);
        }
        scare_regime = false;
        break;
      }
      scare_regime = scare_regime || (ghost[i].scared);
    }
    if (scare_regime)
    {
      if (scare_countdown % (scare_countdown/30+1)== 0)
      {
        if (rgb_color == 0)
        {
          rgb_color = 0xf;
        }
        else
        {
          rgb_color = 0;
        }
      }
    }
    else
    {
      rgb_color = 0xf00;
    }
    sel_leds_color(peripherals->led_mem_base, rgb_color);
    coins_to_eat = render_map(map, &fb);
    draw_pacman(&pacman, &fb, map);
    for (int i = 0; i < game_data->ghost_nr; ++i)
    {
      draw_ghost(&fb, &ghost[i], map);
    }
    led_strip_number(peripherals->led_mem_base, game_data->pacman_lives, pacman.lives);
    lcd_from_fb(&fb, peripherals->lcd_mem_base);
    pthread_mutex_lock(&mtx);
    read = read_thread_data.last_read;
    pthread_mutex_unlock(&mtx);
  }

  // termination
  free(fb.fb);
  free(map->board_arr);
  free(map);
  return pacman.score;
}
