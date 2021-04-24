#ifndef MAP_TO_FB_H
#define MAT_TO_FB_H
#include "data_structures.h"
#include <stdbool.h>
#define WALL_COLOR 0x1f
#define PATH_COLOR 0
bool update_fb(map_data *data, fb_data *frame_buff);


#endif
