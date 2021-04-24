#ifndef DRAW_SHAPES_H
#define DRAW_SHAPES_H
#include "data_structures.h"
void draw_circle(fb_data *frame, int x, int y,  int radius, uint16_t color);
void draw_rectangle(fb_data *frame, int x, int y, int width, int height, uint16_t color);
#endif
