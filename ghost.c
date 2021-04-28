/*******************************************************************
  All inportant functions for ghost on MicroZed
  based MZ_APO board designed by Petr Porazil at PiKRON

  ghost.c      - all important functions for ghost

  (C) Copyright 2021 by Lukas Nejezchleb
      e-mail:   nejezluk@fel.cvut.cz
      license:  any combination of GPL, LGPL, MPL or BSD licenses

 *******************************************************************/
#include "ghost.h"
#include "data_structures.h"
#include <stdbool.h>
//internal functions
bool can_move(ghost_type *ghost, int dirx, int diry, map_data *map);
// end of internal functions


bool can_move(ghost_type *ghost, int dirx, int diry, map_data *map)
{
    int pixel = map->board_arr[map->width * (ghost->location.y + diry) + ghost->location.x + dirx];
    return (pixel != BLOCKED);
}
