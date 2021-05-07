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
 * @brief Returns dynamically allocated memory with the data created from the map template given
 * 
 * @param screen_w
 * @param screen_h
 * @param template
 * @return map_data* 
 */
map_data *create_map_data(int screen_w, int screen_h, map_template *template);

/**
 * @brief Returns coords in the map given coords in the template
 * 
 * @param row
 * @param col
 * @param template
 * @param screen_w
 * @param screen_h
 * @return coords 
 */
coords get_coords_from_template(int row, int col, map_template *template, int screen_w, int screen_h);

/**
 * @brief Create a cell (only internal function)
 * 
 * @param row
 * @param col
 * @param template
 * @param map
 */
void create_cell(int row, int col, map_template *template, map_data *map);

/**
 * @brief Create a cross  (only internal function)
 * 
 * @param row
 * @param col
 * @param template
 * @param map
 * @param center_val
 */
void create_cross(int row, int col, map_template *template, map_data *map, char center_val);
#endif
