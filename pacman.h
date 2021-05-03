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


/*
* @returns Pacman at spawning point of map
*/
pacman_type create_pacman(map_data *map, int lives, int score);

/*
* reads key from terminal, changes direction if moving this direction is possible
* moves the pacman in the direction if possible
* @returns true if pacman has eaten supercoin
*/
bool pacman_move(pacman_type *pacman, map_data *map);

/*
* draws pacman to the frame buffer
*/
void draw_pacman(pacman_type *pacman, fb_data *fb, map_data *map);
#endif
