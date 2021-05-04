/**
 * @file draw_shapes.h
 * @author Lukas Nejezchleb (nejezluk@fel.cvut.cz)
 * @brief Module with functions to draw shapes to the frame buffer
 * @version 0.1
 * @date 2021-05-04
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef DRAW_SHAPES_H
#define DRAW_SHAPES_H
#include "data_structures.h"

/**
 * @brief Draws the circle with center at x,y with given radius
 * 
 * @param frame 
 * @param x 
 * @param y 
 * @param radius 
 * @param color 
 */
void draw_circle(fb_data *frame, int x, int y, int radius, uint16_t color);

/**
 * @brief Draws rectangle with left upper corner at x,y
 * 
 * @param frame 
 * @param x 
 * @param y 
 * @param width 
 * @param height 
 * @param color 
 */
void draw_rectangle(fb_data *frame, int x, int y, int width, int height, uint16_t color);

/**
 * @brief Draws given colour across the whole frame buffer
 * 
 * @param frame 
 * @param color 
 */
void set_background(fb_data *frame, uint16_t color);

/**
 * @brief Draws an ghost at x,y, bitmap of ghost is also in this function
 * 
 * @param frame 
 * @param x 
 * @param y 
 * @param scale 
 * @param color 
 */
void draw_ghost_shape(fb_data *frame, int x, int y, int scale, uint16_t color);

/**
 * @brief Pacman facing given direction with his mouth
 * 
 * @param frame 
 * @param x 
 * @param y 
 * @param radius 
 * @param color 
 * @param direction 
 */
void draw_pacman_dir(fb_data *frame, int x, int y, int radius, uint16_t color, int direction);
#endif
