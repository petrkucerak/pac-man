/**
 * @file map_template.h
 * @author Lukas Nejezchleb (nejezluk@fel.cvut.cz)
 * @brief File housing the definition of the template data structure Current maps: map star, map circles, map conch
 * @version 0.1
 * @date 2021-05-04
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef MAP_TEMPLATE_H
#define MAP_TEMPLATE_H

/**
 * @brief the definition of the template data structure
 * 
 */
typedef struct
{
    char *name;         /* name of the map */
    int pacman_spawn_x; /* spawning location of pacman */
    int pacman_spawn_y; /* spawning location of pacman */
    int ghost_spawn_x;  /* spawning location of ghost */
    int ghost_spawn_y;  /* spawning location of ghost */
    int width;          /* width of the map */
    int height;         /* height of the map */
    char *board;        /* actual data about the content of map */
    const int coin;     /* value used to describe coin */
    const int wall;     /* value used to describe wall */
    const int special;  /* value used to describe special coin */
    const int blank;    /* value used to describe place without coin */
} map_template;

// first map
extern map_template map_circles;

// star map
extern map_template map_star;

// conch map
extern map_template map_conch;

#endif
