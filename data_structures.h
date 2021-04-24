#ifndef DATA_STRUCTURES_H
#define DATA_STRUCTURES_H
#include <stdint.h>

typedef struct{
    int width;
    int height;
    uint16_t *fb;
}fb_data;

typedef struct{
    int width;
    int height;
    char *board_arr;
    int max_object_diameter; //maximum dimensions of ghosts, pacman and coins
}map_data;

typedef struct{
    int x;
    int y;
}coords;


//place where is the coin drawn, pacman can walk accross it
#define COIN 3

//black place on the map, pacman is allowed to walk there
#define PASSAGE 1 

//place that will be drawn in color to show where the wall is
#define WALL    2

//black place on the map, pacman is not allowed there
#define BLOCKED 0 

//place where is the supercoin drawn, pacman can walk accross it
#define SUPERCOIN 4

#endif
