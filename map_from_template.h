/*******************************************************************
  Program to create map from template on MicroZed
  based MZ_APO board designed by Petr Porazil at PiKRON

  map_from_template.h      - creates map from template

  (C) Copyright 2021 by Lukas Nejezchleb
      e-mail:   nejezluk@fel.cvut.cz
      license:  any combination of GPL, LGPL, MPL or BSD licenses

 *******************************************************************/
#ifndef MAP_FROM_TEMPLATE_H
#define MAP_FROM_TEMPLATE_H
#include "data_structures.h"
#include "map_template.h"

/**
 * given map template returns dynamically allocated map for the whole screen
 */
map_data *create_map_data(int screen_w, int screen_h, map_template *template);

/**
 * fiven coords in template returns coords on the actual map
 */
coords get_coords_from_template(int row, int col, map_template *template, int screen_w, int screen_h);
#endif
