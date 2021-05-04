/**
 * @file game.h
 * @author Lukas Nejezchleb (nejezluk@fel.cvut.cz), Petr Kucera (kucerp28@fel.cvut.cz)
 * @brief Module where the game is taking place
 * @version 0.1
 * @date 2021-05-04
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef GAME_H
#define GAME_H
#include "data_structures.h"
#include "pacman.h"
#include "ghost.h"

/**
 * @brief Initialises all necessary data structures and loops the game tick and refreshing screen while the player has not won, lost or pressed the q key
 * 
 * @param game_data 
 * @param peripherals 
 * @return int pac-man game score
 */
int run_game(game_init_data_t* game_data, peripherals_data_t* peripherals);

/**
 * @brief Internal functions for setting the color of RGB leds according to the game state
 * 
 * @param led_mem_base 
 * @param scare_countdown 
 * @param pacman_score 
 */
void led_blink(unsigned char *led_mem_base, int scare_countdown, int pacman_score);

/**
 * @brief  displays the pause message and waits for user to press the pause of quit key
 * 
 * @param fb 
 * @param peripherals 
 */
void pause(fb_data *fb, peripherals_data_t *peripherals);

/**
 * @brief moves pacman and each ghost one step, checking for collisions and user input
 * 
 * @param map 
 * @param pacman 
 * @param ghost_arr 
 * @param num_ghosts 
 * @param scare 
 * @return true 
 * @return false 
 */
bool game_tick(map_data *map, pacman_type *pacman, ghost_type *ghost_arr, int num_ghosts, int *scare);

#endif
