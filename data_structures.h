/**
 * @file data_structures.h
 * @author Lukas Nejezchleb (nejezluk@fel.cvut.cz), Petr Kucera (kucerp28@fel.cvut.cz)
 * @brief File with definitions of data structures used across modules like fb data (data about next frame on the screeen), map data (data about currently played map)
 * @version 0.1
 * @date 2021-05-04
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef DATA_STRUCTURES_H
#define DATA_STRUCTURES_H
#include <stdint.h>
#include <stdbool.h>
#include <pthread.h>
#include "map_template.h"

/**
 * @brief the buffer structure
 * 
 */
typedef struct
{
   int width;
   int height;
   uint16_t *fb;
} fb_data;

/**
 * @brief the coords structure
 * 
 */
typedef struct
{
   int x;
   int y;
} coords;

/**
 * @brief the basic map metadatas
 * 
 */
typedef struct
{
   int width;
   int height;
   char *board_arr;
   int max_object_diameter; // maximum dimensions of ghosts, pacman and coins
   coords ghost_spawn;
   coords pacman_spawn;
} map_data;

/**
 * @brief thread data type
 * 
 */
typedef struct
{
   bool quit;
   char last_read;
} read_thread_data_type;

/**
 * @brief the pac-man metadatas
 * 
 */
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
extern pthread_cond_t character_has_been_read;

/**
 * @brief peripherals config data
 * 
 */
typedef struct
{
   unsigned char *lcd_mem_base;
   unsigned char *led_mem_base;
   int lcd_w;
   int lcd_h;
} peripherals_data_t;

/**
 * @brief data necessary for game initialization
 * 
 */
typedef struct
{
   int pacman_lives;
   int ghost_nr;
   map_template *map;
} game_init_data_t;

/**
 * @brief the ghost metadatas
 * 
 */
typedef struct
{
   bool moving_randomly;
   bool scared;
   coords location;
   coords direction;
   uint16_t color;
} ghost_type;

/**
 * @brief place where is the coin drawn, pacman can walk accross it
 * 
 */
#define COIN 3

/**
 * @brief black place on the map, pacman is allowed to walk there
 * 
 */
#define PASSAGE 1

/**
 * @brief place that will be drawn in color to show where the wall is
 * 
 */
#define WALL 2

/**
 * @brief black place on the map, pacman is not allowed there
 * 
 */
#define BLOCKED 0

/**
 * @brief place where is the supercoin drawn, pacman can walk accross it
 * 
 */
#define SUPERCOIN 4

#endif
