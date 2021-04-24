/*******************************************************************
  Program to draw simple shapes to frame buffer on MicroZed
  based MZ_APO board designed by Petr Porazil at PiKRON

  draw_shapes.c      - simple program to draw shapes

  (C) Copyright 2021 by Lukas Nejezchleb
      e-mail:   nejezluk@fel.cvut.cz
      license:  any combination of GPL, LGPL, MPL or BSD licenses

 *******************************************************************/



#include "draw_shapes.h"
int pixel_dist_squared(int x1, int y1, int x2, int y2){
    return ((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
}

void draw_circle(fb_data *frame, int x, int y, int radius, uint16_t color)
{
    for (int row = y - radius; row < y + radius; row++)
    {
        for (int col = x - radius; col < x + radius; col++)
        {
            if(row>0&&col>0&&row<frame->height&& col<frame->width){
                if(pixel_dist_squared(col, row, x,y)<=(radius*radius)){
                    frame->fb[row*frame->width+col] = color;
                }
            }
        }
    }
}

void draw_rectangle(fb_data *frame, int x, int y, int width, int height, uint16_t color)
{
    for (int i = 0; i < width; ++i)
    {
        if ((x + i >= 0) && (x + i < frame->width))
        {
            for (int j = 0; j < height; ++j)
            {
                if ((y + j >= 0) && (y + j < frame->height))
                {
                    //place on the screen
                    frame->fb[(y + j) * frame->width + x + i] = color;
                }
            }
        }
    }
}
