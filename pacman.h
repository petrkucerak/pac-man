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


pacman_type create_pacman(map_template* map, int screen_w, int screen_h, int lives);

void pacman_move(pacman_type* pacman, map_data* map);

#endif
