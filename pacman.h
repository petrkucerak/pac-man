/**
 * @file pacman.h
 * @author Lukas Nejezchleb (nejezluk@fel.cvut.cz)
 * @brief Module for the controls and rendering of pacman
 * @version 0.1
 * @date 2021-05-04
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef PACMAN_H
#define PACMAN_H
#include "data_structures.h"
#include "map_template.h"

/**
 * @brief Returns pacman with initial score and lives at the spawning coords of the map
 * 
 * @param map
 * @param lives
 * @param score
 * @return pacman_type 
 */
pacman_type create_pacman(map_data *map, int lives, int score);

/**
 * @brief Returns pacman with initial score and lives at the spawning coords of the map
 * 
 * @param pacman
 * @param map
 * @return true 
 * @return false 
 */
bool pacman_move(pacman_type *pacman, map_data *map);

/**
 * @brief draws circle if pacman is not facing any direction or the ”pie” shape to symbolise the heading
 * 
 * @param pacman
 * @param fb
 * @param map
 */
void draw_pacman(pacman_type *pacman, fb_data *fb, map_data *map);

/**
 * @brief  returns true if pacman can move in given direction
 * 
 * @param pacman
 * @param dirx
 * @param diry
 * @param map
 * @return true 
 * @return false 
 */
bool pacman_can_move(pacman_type *pacman, int dirx, int diry, map_data *map);
#endif
