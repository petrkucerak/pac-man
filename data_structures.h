/*******************************************************************
  Data structures definitions for project apoman for MicroZed based MZ_APO board
  designed by Petr Porazil at PiKRON

  data_structures.c      - file with definitions of used data structures

(C) Copyright 2021 by Petr Kucera and Lukas Nejezchleb
      e-mails:   kucerp28@fel.cvut.cz , nejezluk@fel.cvut.cz
      license:  any combination of GPL, LGPL, MPL or BSD licenses
 *******************************************************************/

#ifndef DATA_STRUCTURES_H
#define DATA_STRUCTURES_H
#include <stdint.h>
#include <stdbool.h>
#include <pthread.h>
#include "map_template.h"

typedef struct
{
    int width;
    int height;
    uint16_t *fb;
} fb_data;

typedef struct
{
    int width;
    int height;
    char *board_arr;
    int max_object_diameter; // maximum dimensions of ghosts, pacman and coins
} map_data;

typedef struct
{
    int x;
    int y;
} coords;

typedef struct
{
    bool quit;
    char last_read;
} read_thread_data_type;

typedef struct
{
    coords location;
    coords direction;
    int score;
    int lives;
    int maxlives;
} pacman_type;

extern read_thread_data_type read_thread_data;
extern pthread_mutex_t mtx;

typedef struct
{
    unsigned char *lcd_mem_base;
    unsigned char *led_mem_base;
    int lcd_w;
    int lcd_h;
} peripherals_data_t;

typedef struct 
{
    int pacman_lives;
    int ghost_nr;
    map_template *map;
}game_init_data_t;

typedef struct
{
    bool moving_randomly;
    bool scared;
    coords location;
    coords direction;
    uint16_t color;
}ghost_type;



/**
 * place where is the coin drawn, pacman can walk accross it
 */
#define COIN 3

/**
 * black place on the map, pacman is allowed to walk there
 */
#define PASSAGE 1

/**
 * place that will be drawn in color to show where the wall is
 */
#define WALL 2

/**
 * black place on the map, pacman is not allowed there
 */
#define BLOCKED 0

/**
 * place where is the supercoin drawn, pacman can walk accross it
 */
#define SUPERCOIN 4

#endif
