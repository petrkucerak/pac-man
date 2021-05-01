/*******************************************************************
  Program to draw simple shapes to frame buffer on MicroZed
  based MZ_APO board designed by Petr Porazil at PiKRON

  draw_shapes.h      - simple program to draw shapes

  (C) Copyright 2021 by Lukas Nejezchleb
      e-mail:   nejezluk@fel.cvut.cz
      license:  any combination of GPL, LGPL, MPL or BSD licenses

 *******************************************************************/

#ifndef DRAW_SHAPES_H
#define DRAW_SHAPES_H
#include "data_structures.h"

/**
 * function to draw circle to fb_data frame at x,y with radius and color
 */
void draw_circle(fb_data *frame, int x, int y, int radius, uint16_t color);

/**
 * function to draw rectangle to fb_data frame at x,y with width and height and color
 */
void draw_rectangle(fb_data *frame, int x, int y, int width, int height, uint16_t color);

/**
 * sets background to certain color
 */
void set_background(fb_data *frame, uint16_t color);

/**
 * draws the ghost shape to fb 
 */
void draw_ghost_shape(fb_data *frame, int x, int y, int scale, uint16_t color);

#endif
