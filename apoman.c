/*******************************************************************
  Main function for project apoman for MicroZed based MZ_APO board
  designed by Petr Porazil at PiKRON

  apoman.c      - main file

(C) Copyright 2021 by Petr Kucera and Lukas Nejezchleb
      e-mails:   kucerp28@fel.cvut.cz , nejezluk@fel.cvut.cz
      license:  any combination of GPL, LGPL, MPL or BSD licenses
 *******************************************************************/

#define _POSIX_C_SOURCE 200112L

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>

#include "mzapo_parlcd.h"
#include "mzapo_phys.h"
#include "mzapo_regs.h"
#include "data_structures.h"
#include "font_types.h"
#include "map_template.h"
#include "map_from_template.h"
#include "map_to_fb.h"
#include "update_peripherals.h"
#include "text_fb.h"
#include "draw_shapes.h"
#include "game.h"
#include "menu_utilities.h"
#include "terminal_read.h"

#define LED_MAX_VAL 6
#define SCREEN_WIDTH 480
#define SCREEN_HEIGHT 320

pthread_mutex_t mtx;
read_thread_data_type read_thread_data;

int main(int argc, char *argv[])
{
  // init a periphery
  printf("Hello world\n");

  unsigned char *led_mem_base;
  led_mem_base = map_phys_address(SPILED_REG_BASE_PHYS, SPILED_REG_SIZE, 0);
  if (led_mem_base == NULL)
  {
    exit(1);
  }

  unsigned char *lcd_mem_base;
  lcd_mem_base = map_phys_address(PARLCD_REG_BASE_PHYS, PARLCD_REG_SIZE, 0);
  if (lcd_mem_base == NULL)
  {
    exit(1);
  }
  //terminal read

  pthread_mutex_init(&mtx, NULL); // initialize mutex with default attributes
  read_thread_data.quit = false; 
  read_thread_data.last_read = ' ';
  pthread_t threads[1];
  pthread_create(&threads[0], NULL, input_thread, &read_thread_data);
  // frame buffer
  fb_data fb;
  fb.fb = malloc(sizeof(uint16_t) * SCREEN_WIDTH * SCREEN_HEIGHT);
  fb.width = SCREEN_WIDTH;
  fb.height = SCREEN_HEIGHT;
  if (fb.fb == NULL)
  {
    exit(1);
  }

  // init display
  parlcd_hx8357_init(lcd_mem_base);
  font_descriptor_t *font = &font_winFreeSystem14x16;

  // text menu
  // run_init_game_menu(&fb, lcd_mem_base, font);

  // exit for debug
  // exit(-1);
  
  map_data *map = create_map_data(SCREEN_WIDTH, SCREEN_HEIGHT, &map_circles);
  if (map == NULL)
  {
    free(fb.fb);
    exit(1);
  }
  //run_init_game_menu();

  // get starting coords for pacman
  coords pacman = get_coords_from_template(map_circles.pacman_spawn_y,
                                           map_circles.pacman_spawn_x, &map_circles,
                                           SCREEN_WIDTH, SCREEN_HEIGHT);
  bool can_move = true;

  while (can_move)
  {
    if (map->board_arr[pacman.x + (pacman.y - 1) * SCREEN_WIDTH] != BLOCKED)
    {
      pacman.y--;
    }
    else
    {
      can_move = false;
    }

    render_map(map, &fb);
    //draw pacman
    draw_circle(&fb, pacman.x, pacman.y, 8, 0xffe0);
    lcd_from_fb(&fb, lcd_mem_base);
  }

  // program termination
  draw_text_center(&fb, "KONEC", SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 10, font, 0xffff);
  lcd_from_fb(&fb, lcd_mem_base);
  printf("Goodbye world\n");

  char read = ' ';
  while (read != 'q')
  {
    pthread_mutex_lock(&mtx);
    read = read_thread_data.last_read;
    pthread_mutex_unlock(&mtx);
  }
  // free allocated memory
  free(fb.fb);
  fb.fb = NULL;
  free(map->board_arr);
  free(map);

  pthread_mutex_lock(&mtx);
  read_thread_data.quit = true;
  pthread_mutex_unlock(&mtx);
  pthread_join(threads[0], NULL); //wait for thread to join
  pthread_mutex_destroy(&mtx);
  return 0;
}
