/*******************************************************************
  All inportant functions for pacman on MicroZed
  based MZ_APO board designed by Petr Porazil at PiKRON

  pacman.h      - all important functions for pacman

  (C) Copyright 2021 by Lukas Nejezchleb
      e-mail:   nejezluk@fel.cvut.cz
      license:  any combination of GPL, LGPL, MPL or BSD licenses

 *******************************************************************/

#include "pacman.h"
#include "map_from_template.h"

pacman_type create_pacman(map_template *map, int screen_w, int screen_h, int lives)
{
    pacman_type pacman;
    pacman.lives = lives;
    pacman.maxlives = lives;
    pacman.location = get_coords_from_template(map->pacman_spawn_y, map->pacman_spawn_x,
                                               map, screen_w, screen_h);
    coords direction = {0, 0};
    pacman.direction = direction;
    pacman.score = 0;
    return pacman;
}
