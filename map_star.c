/*******************************************************************
  Map circles for apoman on MicroZed
  based MZ_APO board designed by Petr Porazil at PiKRON

  map_star.c      - star map template

  (C) Copyright 2021 by Petr Kucera
      e-mail:   kucerp28@fel.cvut.cz
      license:  any combination of GPL, LGPL, MPL or BSD licenses

 *******************************************************************/
#include "map_template.h"

// the meaning of numbers in array is defined in 'data_strcuture.h'

static char board_data_s[] = {
   1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
   1,3,2,2,2,2,2,3,2,2,2,2,2,3,1,
   1,2,1,2,1,1,1,2,1,1,1,2,1,2,1,
   1,2,2,2,2,2,2,2,2,2,2,2,2,2,1,
   1,2,1,2,1,1,1,2,1,1,1,2,1,2,1,
   1,2,2,2,2,2,2,3,2,2,2,2,2,3,1,
   1,2,1,2,1,1,1,2,1,1,1,2,1,2,1,
   1,2,2,2,2,2,2,2,2,2,2,2,2,2,1,
   1,2,1,2,1,1,1,2,1,1,1,2,1,1,1,
   1,2,2,2,2,2,2,2,2,3,2,2,0,0,1,
   1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
};


map_template map_star = {
   .name = "Star_map",
   .pacman_spawn_x = 1, /* spawning location of pacman */
   .pacman_spawn_y = 9, /* spawning location of pacman */
   .ghost_spawn_x = 13,  /* spawning location of ghost */
   .ghost_spawn_y = 9,  /* spawning location of ghost */
   .width = 15,         /* width of the map */
   .height = 11,        /* height of the map */
   .board = board_data_s, /* actual data about the content of map */
   .coin = 2,           /* value used to describe coin */
   .wall = 1,           /* value used to describe wall */
   .special = 3,        /* value used to describe special coin */
   .blank = 0,          /* value used to describe place without coin */
};
