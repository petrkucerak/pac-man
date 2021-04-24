#ifndef MAP_TEMPLATE_H
#define MAP_TEMPLATE_H

typedef struct
{
    char *name;         /* name of the map*/
    int pacman_spawn_x; /*spawning location of pacman*/
    int pacman_spawn_y; /*spawning location of pacman*/
    int ghost_spawn_x;  /*spawning location of ghost*/
    int ghost_spawn_y;  /*spawning location of ghost*/
    int width;          /*width of the map*/
    int height;         /*height of the map*/
    char *board;        /*actual data about the content of map*/
    const int coin;          /*value used to describe coin*/
    const int wall;          /*value used to describe wall*/
    const int special;       /*value used to describe special coin*/
    const int blank;          /*value used to describe place without coin*/
} map_template;

extern map_template map_apo_of_doom;

#endif
