/*******************************************************************
  All inportant functions for ghost on MicroZed
  based MZ_APO board designed by Petr Porazil at PiKRON

  ghost.h      - all important functions for ghost

  (C) Copyright 2021 by Lukas Nejezchleb
      e-mail:   nejezluk@fel.cvut.cz
      license:  any combination of GPL, LGPL, MPL or BSD licenses

 *******************************************************************/
#ifndef GHOST_H
#define GHOST_H

#include "data_structures.h"
//internal data structure
typedef struct
{
  coords dir;
  int cost;
} moves_costs_t;
/*
returns ghost structure
*/
ghost_type create_ghost(map_template *map, int screen_w, int screen_h, int ghost_nr);

/*
draws the ghost
*/
void draw_ghost(fb_data *fb, ghost_type *ghost, map_data *map);

/*
moves the ghost, returns true if pacman was eaten by the ghost
*/
bool ghost_move(ghost_type *ghost, map_data *map, pacman_type *pacman);

#endif
