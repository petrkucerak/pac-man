/**
 * @file ghost.c
 * @author Lukas Nejezchleb (nejezluk@fel.cvut.cz)
 * @brief Module where all the logic and movement of ghost is placed
 * @version 0.1
 * @date 2021-05-04
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include "ghost.h"
#include "data_structures.h"
#include "draw_shapes.h"
#include "map_from_template.h"
#include "config.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

bool ghost_move(ghost_type *ghost, map_data *map, pacman_type *pacman)
{
    if ((pacman->location.x == ghost->location.x) && (pacman->location.y == ghost->location.y))
    {
        if (ghost->scared)
        {
            ghost->location = map->ghost_spawn;
            ghost->scared = false;
            pacman->score += GHOST_SCORE_INCECREASE;
        }
        else
        {
            return true;
        }
    }

    if (ghost->scared == false)
    {
        if ((rand() % GHOST_SWITCH_TO_RANDOM == 0) && (ghost->moving_randomly == false))
        {
            ghost->moving_randomly = true;
        }
        else if ((rand() % GHOST_SWITCH_TO_TARGET == 0) && (ghost->moving_randomly == true))
        {
            ghost->moving_randomly = false;
        }
    }
    moves_costs_t possible_moves[4];
    int possibilities = create_moves(possible_moves, ghost, map, pacman);
    change_direction(ghost, possibilities, possible_moves);
    ghost->location.x = ghost->location.x + ghost->direction.x;
    ghost->location.y = ghost->location.y + ghost->direction.y;
    if ((pacman->location.x == ghost->location.x) && (pacman->location.y == ghost->location.y))
    {
        if (ghost->scared)
        {
            ghost->location = map->ghost_spawn;
            ghost->scared = false;
            pacman->score += GHOST_SCORE_INCECREASE;
        }
        else
        {
            return true;
        }
    }
    return false;
}

bool ghost_can_move(ghost_type *ghost, int dirx, int diry, map_data *map)
{
    int pixel = map->board_arr[map->width * (ghost->location.y + diry) + ghost->location.x + dirx];
    return (pixel != BLOCKED);
}

int create_moves(moves_costs_t *moves_arr, ghost_type *ghost, map_data *map, pacman_type *pacman)
{
    // both 4 on next lines is ammount of directions and should not be changed
    coords dirs[4] = {{.x = 0, .y = -1}, {.x = 0, .y = 1}, {.x = 1, .y = 0}, {.x = -1, .y = 0}};
    int ret = 0;
    for (int i = 0; i < 4; ++i)
    {
        if (ghost_can_move(ghost, dirs[i].x, dirs[i].y, map))
        {
            if ((dirs[i].x != -ghost->direction.x) || (dirs[i].y != -ghost->direction.y))
            {
                // add the direction
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
    return ret; // return ammount of valid options to move
}

void draw_ghost(fb_data *fb, ghost_type *ghost, map_data *map)
{
    if (ghost->scared)
    {
        draw_ghost_shape(fb, ghost->location.x, ghost->location.y, map->max_object_diameter / 8, 0x1f);
    }
    else
    {
        draw_ghost_shape(fb, ghost->location.x, ghost->location.y, map->max_object_diameter / 8, ghost->color);
    }
}

ghost_type create_ghost(map_data *map, int ghost_nr)
{
    ghost_type ghost;
    ghost.moving_randomly = true;
    ghost.scared = false;
    ghost.location = map->ghost_spawn;
    coords direction = {0, 0};
    ghost.direction = direction;
    uint16_t color_pallete[] = {GHOST_COLORS};
    ghost.color = color_pallete[ghost_nr % (GHOST_COLORS_AMMOUNT)];
    return ghost;
}

void change_direction(ghost_type *ghost, int possibilities, moves_costs_t *moves_options)
{
    if (possibilities == 0)
    {
        // host reached dead_end
        ghost->direction.x = -ghost->direction.x;
        ghost->direction.x = -ghost->direction.y;
    }
    else if (possibilities == 1)
    {
        // only one way possible, pick that one
        ghost->direction = moves_options[0].dir;
    }
    else if (ghost->moving_randomly)
    {
        ghost->direction = moves_options[rand() % possibilities].dir;
    }
    else
    {
        // pick direction with smallest cost
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
