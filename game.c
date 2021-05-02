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

//internal function
void led_blink(unsigned char *led_mem_base, int scare_countdown);

//returns true if the game should be rendered imedeatly
bool game_tick(map_data *map, pacman_type *pacman, ghost_type *ghost_arr, int num_ghosts, int *scare);
//end of internal functions

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
  pacman_type pacman = create_pacman(map, game_data->pacman_lives,0);
  ghost_type ghost[game_data->ghost_nr];
  for (int i = 0; i < game_data->ghost_nr; ++i)
  {
    ghost[i] = create_ghost(map, i);
  }
  // actual game
  char read = ' ';
  bool coins_to_eat = true;
  int scare_countdown = -1;
  while ((read != 'q') && (pacman.lives > 0) && (coins_to_eat))
  {
    for (int i = 0; i < GAME_SPEED; ++i)
    {
      if (game_tick(map, &pacman, ghost, game_data->ghost_nr, &scare_countdown))
      {
        break;
      }
    }
    //do the rendering
    led_blink(peripherals->led_mem_base, scare_countdown);
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
  pthread_mutex_lock(&mtx);
  read_thread_data.last_read = ' ';
  pthread_mutex_unlock(&mtx);
  // termination
  free(fb.fb);
  free(map->board_arr);
  free(map);
  return pacman.score;
}

void led_blink(unsigned char *led_mem_base, int scare_countdown)
{
  static int period = 0;
  static int time = 0;
  static uint32_t color = LED_NORMAL_COLOR;
  if ((scare_countdown > 0) && (period == 0))
  { //scared regime began
    period = scare_countdown / 30 + 1;
    time = 0;
    color = LED_SCARE_COLOR2;
  }
  else if (scare_countdown > 0)
  {
    time++;
    if (time >= period)
    {
      period = scare_countdown / 30 + 1;
      time = 0;
      //change color
      color = (color == LED_SCARE_COLOR1) ? LED_SCARE_COLOR2 : LED_SCARE_COLOR1;
    }
  }
  else
  {
    //no scare regime
    color = LED_NORMAL_COLOR;
  }
  sel_leds_color(led_mem_base, color);
}

bool game_tick(map_data *map, pacman_type *pacman, ghost_type *ghost_arr, int num_ghosts, int *scare)
{
  bool ret = false;
  if (*scare == 0)
  {
    for (int j = 0; j < num_ghosts; ++j)
    {
      ghost_arr[j].scared = false;
      ghost_arr[j].moving_randomly = true;
    }
    ret = true;
  }
  else if (*scare > 0)
  {
    (*scare)--;
  }

  if (pacman_move(pacman, map)) // eaten supercoin
  {
    *scare = SCARE_REGIME_DURATION;
    for (int j = 0; j < num_ghosts; ++j)
    {
      ghost_arr[j].scared = true;
      ghost_arr[j].moving_randomly = true;
    }
    ret = true;
  }
  bool scare_regime = false; //find out if by chance all ghost have not been eaten
  for (int i = 0; i < num_ghosts; ++i)
  {
    // move every ghost and check if pacman has not been eaten
    if (ghost_move(&ghost_arr[i], map, pacman))
    {
      *pacman = create_pacman(map, pacman->lives - 1, pacman->score-SCORE_DEATH_PENALTY);
      for (int j = 0; j < num_ghosts; ++j)
      {
        ghost_arr[j] = create_ghost(map, j);
      }
      ret = true;
      break;
    }
    scare_regime = scare_regime || (ghost_arr[i].scared);
  }
  if (!scare_regime)
  {
    (*scare) = -1;
  }
  return ret;
}
