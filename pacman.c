/**
 * @file pacman.c
 * @author Lukas Nejezchleb (nejezluk@fel.cvut.cz)
 * @brief Module for the controls and rendering of pacman
 * @version 0.1
 * @date 2021-05-04
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "pacman.h"
#include "draw_shapes.h"
#include "map_from_template.h"
#include "config.h"
#include <stdbool.h>

pacman_type create_pacman(map_data *map, int lives, int score)
{
    pacman_type pacman;
    pacman.lives = lives;
    pacman.maxlives = lives;
    pacman.location = map->pacman_spawn;
    coords direction = {0, 0};
    pacman.direction = direction;
    pacman.score = score;
    return pacman;
}

bool pacman_move(pacman_type *pacman, map_data *map)
{
    bool ret = false;
    // find out if some important key has been pressed
    char pressed;
    pthread_mutex_lock(&mtx);
    pressed = read_thread_data.last_read;
    pthread_mutex_unlock(&mtx);
    if ((pressed == KEY_UP||pressed == KEY_UP+'A'-'a') && (pacman_can_move(pacman, 0, -1, map)))
    {
        pacman->direction.x = 0;
        pacman->direction.y = -1;
    }
    if ((pressed == KEY_DWN||pressed == KEY_DWN+'A'-'a') && (pacman_can_move(pacman, 0, 1, map)))
    {
        pacman->direction.x = 0;
        pacman->direction.y = 1;
    }
    if ((pressed == KEY_LEFT||pressed == KEY_LEFT+'A'-'a') && (pacman_can_move(pacman, -1, 0, map)))
    {
        pacman->direction.x = -1;
        pacman->direction.y = 0;
    }
    if ((pressed == KEY_RIGHT||pressed == KEY_RIGHT+'A'-'a') && (pacman_can_move(pacman, 1, 0, map)))
    {
        pacman->direction.x = 1;
        pacman->direction.y = 0;
    }
    if (pacman_can_move(pacman, pacman->direction.x, pacman->direction.y, map))
    {
        pacman->location.x = pacman->location.x + pacman->direction.x;
        pacman->location.y = pacman->location.y + pacman->direction.y;
    }
    if (map->board_arr[map->width * (pacman->location.y) + pacman->location.x] == COIN)
    {
        map->board_arr[map->width * (pacman->location.y) + pacman->location.x] = PASSAGE;
        pacman->score = pacman->score + COIN_SCORE_INCECREASE;
    }
    if (map->board_arr[map->width * (pacman->location.y) + pacman->location.x] == SUPERCOIN)
    {
        map->board_arr[map->width * (pacman->location.y) + pacman->location.x] = PASSAGE;
        ret = true;
    }
    return ret;
}

bool pacman_can_move(pacman_type *pacman, int dirx, int diry, map_data *map)
{
    int pixel = map->board_arr[map->width * (pacman->location.y + diry) + pacman->location.x + dirx];
    return (pixel != BLOCKED);
}

void draw_pacman(pacman_type *pacman, fb_data *fb, map_data *map)
{
    // draw pacman
    coords location = pacman->location;
    if ((pacman->direction.x == -1) && (pacman->direction.y == 0))
    {
        draw_pacman_dir(fb, location.x, location.y, map->max_object_diameter / 2, PACMAN_COLOR, LEFT);
    }
    else if ((pacman->direction.x == 1) && (pacman->direction.y == 0))
    {
        draw_pacman_dir(fb, location.x, location.y, map->max_object_diameter / 2, PACMAN_COLOR, RIGHT);
    }
    else if ((pacman->direction.x == 0) && (pacman->direction.y == 1))
    {
        draw_pacman_dir(fb, location.x, location.y, map->max_object_diameter / 2, PACMAN_COLOR, DWN);
    }
    else if ((pacman->direction.x == 0) && (pacman->direction.y == -1))
    {
        draw_pacman_dir(fb, location.x, location.y, map->max_object_diameter / 2, PACMAN_COLOR, UP);
    }
    else
    {
        draw_circle(fb, location.x, location.y, map->max_object_diameter / 2, PACMAN_COLOR);
    }
}
