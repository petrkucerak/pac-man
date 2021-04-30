/*******************************************************************
  Program to draw map to frame buffer on MicroZed
  based MZ_APO board designed by Petr Porazil at PiKRON

  map_to_fb.h      - simple program to draw map

  (C) Copyright 2021 by Lukas Nejezchleb
      e-mail:   nejezluk@fel.cvut.cz
      license:  any combination of GPL, LGPL, MPL or BSD licenses

 *******************************************************************/
#ifndef MAP_TO_FB_H
#define MAT_TO_FB_H
#include "data_structures.h"
#include <stdbool.h>
#define WALL_COLOR 0xf
#define PATH_COLOR 0

/**
 * given map_data draws the map to frame buffer, returns if there are any coins to be eaten
 */
bool render_map(map_data *data, fb_data *frame_buff);


#endif
