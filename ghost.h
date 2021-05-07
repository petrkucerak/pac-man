/**
 * @file ghost.h
 * @author Lukas Nejezchleb (nejezluk@fel.cvut.cz)
 * @brief Module where all the logic and movement of ghost is placed
 * @version 0.1
 * @date 2021-05-04
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#ifndef GHOST_H
#define GHOST_H

#include "data_structures.h"

/**
 * @brief price of movement
 * 
 */
typedef struct
{
   coords dir;
   int cost;
} moves_costs_t;

/**
 * @brief Creates the ghost at spawning point at map
 * 
 * @param map
 * @param ghost_nr
 * @return ghost_type 
 */
ghost_type create_ghost(map_data *map, int ghost_nr);

/**
 * @brief Draws the ghost to frame buffer with color indicating its state
 * 
 * @param fb
 * @param ghost
 * @param map
 */
void draw_ghost(fb_data *fb, ghost_type *ghost, map_data *map);

/**
 * @brief Has small chance to change the ghost movement from random to targeting and vice versa. Changes the ghosts direction if there are more possibilities, moves the ghost in the resulting direction.
 * 
 * @param ghost
 * @param map
 * @param pacman
 * @return true 
 * @return false 
 */
bool ghost_move(ghost_type *ghost, map_data *map, pacman_type *pacman);

/**
 * @brief Returns true if ghost can move in given direction
 * 
 * @param ghost
 * @param dirx
 * @param diry
 * @param map
 * @return true 
 * @return false 
 */
bool ghost_can_move(ghost_type *ghost, int dirx, int diry, map_data *map);

/**
 * @brief Returns number of possible moves, which it has put into the array along with their cost
 * 
 * @param moves_arr
 * @param ghost
 * @param map
 * @param pacman
 * @return returns number of possible moves, which it has put into the array along with their cost
 */
int create_moves(moves_costs_t *moves_arr, ghost_type *ghost, map_data *map, pacman_type *pacman);

/**
 * @brief Changes the direction of ghost to the path that would lead the closest to pacman or random if ghost is moving randomly
 * 
 * @param ghost
 * @param possibilities
 * @param moves_options
 */
void change_direction(ghost_type *ghost, int possibilities, moves_costs_t *moves_options);

#endif
