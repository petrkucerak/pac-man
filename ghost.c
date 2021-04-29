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
#include "draw_shapes.h"
#include "map_from_template.h"
#include <stdbool.h>
#include <stdlib.h>

//internal functions
//returns true if pacman can move in given direction
bool ghost_can_move(ghost_type *ghost, int dirx, int diry, map_data *map);

//returns ammount of directions added to moves_arr
int create_moves(moves_costs_t *moves_arr, ghost_type *ghost, map_data *map, pacman_type *pacman);

//changes ghosts direction
void change_direction(ghost_type *ghost, int possibilities, moves_costs_t *moves_options);
// end of internal functions

void ghost_move(ghost_type *ghost, map_data *map, pacman_type *pacman)
{
    moves_costs_t possible_moves[4];
    int possibilities = create_moves(possible_moves, ghost, map, pacman);
    change_direction(ghost, possibilities, possible_moves);
    ghost->location.x = ghost->location.x+ghost->direction.x;
    ghost->location.y = ghost->location.y+ghost->direction.y;
}

bool ghost_can_move(ghost_type *ghost, int dirx, int diry, map_data *map)
{
    int pixel = map->board_arr[map->width * (ghost->location.y + diry) + ghost->location.x + dirx];
    return (pixel != BLOCKED);
}

int create_moves(moves_costs_t *moves_arr, ghost_type *ghost, map_data *map, pacman_type *pacman)
{
    //both 4 on next lines is ammount of directions and should not be changed
    coords dirs[4] = {{.x = 0, .y = -1}, {.x = 0, .y = 1}, {.x = 1, .y = 0}, {.x = -1, .y = 0}};
    int ret = 0;
    for (int i = 0; i < 4; ++i)
    {
        if (ghost_can_move(ghost, dirs[i].x, dirs[i].y, map))
        {
            if ((dirs[i].x != -ghost->direction.x) || (dirs[i].y != -ghost->direction.y))
            {
                //add the direction
                moves_arr[ret].dir = dirs[i];
                int cost = (pacman->location.x - ghost->location.x - dirs[i].x) *
                               (pacman->location.x - ghost->location.x - dirs[i].x) +
                           (pacman->location.y - ghost->location.y - dirs[i].y) *
                               (pacman->location.y - ghost->location.y - dirs[i].y);
                moves_arr[ret].cost = cost;
                ret++;
            }
        }
    }
    return ret; //return ammount of valid options to move
}

void draw_ghost(fb_data *fb, ghost_type *ghost, map_data *map)
{
    draw_circle(fb, ghost->location.x, ghost->location.y, map->max_object_diameter / 3, ghost->color);
}

ghost_type create_ghost(map_template *map, int screen_w, int screen_h, int ghost_nr)
{
    ghost_type ghost;
    ghost.moving_randomly = false;
    ghost.scared = false;
    ghost.location = get_coords_from_template(map->ghost_spawn_x, map->ghost_spawn_y,
                                               map, screen_w, screen_h);
    coords direction = {0, 0};
    ghost.direction = direction;
    ghost.color = 0xf000;
    return ghost;
}

void change_direction(ghost_type *ghost, int possibilities, moves_costs_t *moves_options){
    if (possibilities == 0)
    {
        //host reached dead_end
        ghost->direction.x = -ghost->direction.x;
        ghost->direction.x = -ghost->direction.y;
    }
    else if (possibilities == 1)
    {
        //only one way possible, pick that one
        ghost->direction = moves_options[0].dir;
    }
    else if (ghost->moving_randomly)
    {
        ghost->direction = moves_options[rand() % possibilities].dir;
    }
    else
    {
        //pick direction with smallest cost
        int lowest_cost = moves_options[0].cost;
        int lowest_index = 0;
        for (int i = 1; i < possibilities; ++i)
        {
            if (lowest_cost > moves_options[i].cost)
            {
                lowest_cost = moves_options[i].cost;
                lowest_index = i;
            }
        }
        ghost->direction = moves_options[lowest_index].dir;
    }
}
