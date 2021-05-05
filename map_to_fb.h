/**
 * @file map_to_fb.h
 * @author Lukas Nejezchleb (nejezluk@fel.cvut.cz)
 * @brief Module for rendering the map to the frame buffer. Houses function render map.
 * @version 0.1
 * @date 2021-05-04
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef MAP_TO_FB_H
#define MAT_TO_FB_H
#include "data_structures.h"
#include <stdbool.h>

/**
 * @brief given map_data draws the map to frame buffer
 * 
 * @param data 
 * @param frame_buff 
 * @return true if there are any coins to be eaten
 * @return false 
 */
bool render_map(map_data *data, fb_data *frame_buff);

#endif
