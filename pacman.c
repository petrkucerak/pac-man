/*******************************************************************
  All inportant functions for pacman on MicroZed
  based MZ_APO board designed by Petr Porazil at PiKRON

  pacman.h      - all important functions for pacman

  (C) Copyright 2021 by Lukas Nejezchleb
      e-mail:   nejezluk@fel.cvut.cz
      license:  any combination of GPL, LGPL, MPL or BSD licenses

 *******************************************************************/

#include "pacman.h"
#include "draw_shapes.h"
#include "map_from_template.h"
#include "config.h"
#include <stdbool.h>

//internal functions
bool can_move(pacman_type *pacman, int dirx, int diry, map_data *map);
// end of internal functions

/*
Given map data creates pacman
*/
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

/*
Moves pacman if possible and changes direction if key has been pressed
*/
void pacman_move(pacman_type *pacman, map_data *map)
{
    //find out if some important key has been pressed
    char pressed;
    pthread_mutex_lock(&mtx);
    pressed = read_thread_data.last_read;
    pthread_mutex_unlock(&mtx);
    if ((pressed == KEY_UP) && (can_move(pacman, 0, -1, map)))
    {
        pacman->direction.x = 0;
        pacman->direction.y = -1;
    }
    if ((pressed == KEY_DWN) && (can_move(pacman, 0, 1, map)))
    {
        pacman->direction.x = 0;
        pacman->direction.y = 1;
    }
    if ((pressed == KEY_LEFT) && (can_move(pacman, -1, 0, map)))
    {
        pacman->direction.x = -1;
        pacman->direction.y = 0;
    }
    if ((pressed == KEY_RIGHT) && (can_move(pacman, 1, 0, map)))
    {
        pacman->direction.x = 1;
        pacman->direction.y = 0;
    }
    if(can_move(pacman, pacman->direction.x, pacman->direction.y, map)){
        pacman->location.x = pacman->location.x+pacman->direction.x;
        pacman->location.y = pacman->location.y+pacman->direction.y;
    }
    if(map->board_arr[map->width * (pacman->location.y) + pacman->location.x]== COIN){
        map->board_arr[map->width * (pacman->location.y) + pacman->location.x] = PASSAGE;
        pacman->score++;
    }
    if(map->board_arr[map->width * (pacman->location.y) + pacman->location.x]== SUPERCOIN){
        map->board_arr[map->width * (pacman->location.y) + pacman->location.x] = PASSAGE;
        pacman->lives--;
    }
}

bool can_move(pacman_type *pacman, int dirx, int diry, map_data *map)
{
    int pixel = map->board_arr[map->width * (pacman->location.y + diry) + pacman->location.x + dirx];
    return (pixel != BLOCKED);
}

void draw_pacman(pacman_type *pacman, fb_data * fb, map_data* map){
     //draw pacman
    draw_circle(fb, pacman->location.x, pacman->location.y, map->max_object_diameter/2, PACMAN_COLOR);
}
