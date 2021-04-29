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
#include "draw_shapes.h"
#include "map_to_fb.h"
#include "map_from_template.h"

int run_game(game_init_data_t *game_data, peripherals_data_t *peripherals)
{
  map_data *map = create_map_data(peripherals->lcd_w, peripherals->lcd_h, game_data->map);
  if (map == NULL)
  {
    //return to show error with malloc
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
  ghost_type ghost = create_ghost(game_data->map,  peripherals->lcd_w, peripherals->lcd_h, 0);
  //actual game
  char read = ' ';
  while (read != 'q')
  {
    pacman_move(&pacman, map);
    ghost_move(&ghost, map, &pacman);
    render_map(map, &fb);
    draw_pacman(&pacman, &fb, map);
    draw_ghost(&fb, &ghost, map);
    led_strip_number(peripherals->led_mem_base, game_data->pacman_lives, pacman.lives);
    lcd_from_fb(&fb, peripherals->lcd_mem_base);
    pthread_mutex_lock(&mtx);
    read = read_thread_data.last_read;
    pthread_mutex_unlock(&mtx);
  }

  //termination
  free(fb.fb);
  free(map->board_arr);
  free(map);
  return 0;
};
