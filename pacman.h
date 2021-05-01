/*******************************************************************
  All inportant functions for pacman on MicroZed
  based MZ_APO board designed by Petr Porazil at PiKRON

  pacman.h      - all important functions for pacman

  (C) Copyright 2021 by Lukas Nejezchleb
      e-mail:   nejezluk@fel.cvut.cz
      license:  any combination of GPL, LGPL, MPL or BSD licenses

 *******************************************************************/
#ifndef PACMAN_H
#define PACMAN_H
#include "data_structures.h"
#include "map_template.h"

#define PACMAN_COLOR 0xffe0

pacman_type create_pacman(map_data *map, int lives);

bool pacman_move(pacman_type* pacman, map_data* map);

void draw_pacman(pacman_type *pacman, fb_data * fb, map_data* map);
#endif
