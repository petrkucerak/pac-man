#ifndef MAP_FROM_TEMPLATE_H
#define MAP_FROM_TEMPLATE_H
#include "data_structures.h"
#include "map_template.h"

map_data *create_map_data(int screen_w, int screen_h, map_template *template);
void create_cell(int row, int col, map_template *template, char *map_array, int screen_w, int screen_h);
void create_cross(int row, int col, map_template *template, char *map_array, int screen_w, int screen_h, char center_val);
coords get_coords_from_template(int row, int col, map_template *template, int screen_w, int screen_h);
#endif
