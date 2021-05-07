/**
 * @file draw_shapes.c
 * @author Lukas Nejezchleb (nejezluk@fel.cvut.cz)
 * @brief Module with functions to draw shapes to the frame buffer
 * @version 0.1
 * @date 2021-05-04
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "draw_shapes.h"
#include <stdlib.h>
#include "config.h"

int pixel_dist_squared(int x1, int y1, int x2, int y2)
{
   return ((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

void draw_circle(fb_data *frame, int x, int y, int radius, uint16_t color)
{
   for (int row = y - radius; row < y + radius; row++)
   {
      for (int col = x - radius; col < x + radius; col++)
      {
         if (row > 0 && col > 0 && row < frame->height && col < frame->width)
         {
            if (pixel_dist_squared(col, row, x, y) <= (radius * radius))
            {
               frame->fb[row * frame->width + col] = color;
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
               // place on the screen
               frame->fb[(y + j) * frame->width + x + i] = color;
            }
         }
      }
   }
}

void set_background(fb_data *frame, uint16_t color)
{
   for (int i = 0; i < frame->width * frame->height; ++i)
   {
      frame->fb[i] = color;
   }
}

void draw_ghost_shape(fb_data *frame, int x, int y, int scale, uint16_t color)
{
   // offset x and y so the ghost would be centered around
   x = x - scale * 4; // 4 is half of bitsize of uint8_t
   y = y - scale * 4; // 4 is half of height of ghost bitmap
   uint8_t ghost_bitmap[] = {0x3c, 0x7e, 0x7e, 0xdb, 0xff, 0xff, 0xff, 0xdb};
   /*
      xxxx   
     xxxxxx 
     xxxxxx
    xx xx xx
    xxxxxxxx
    xxxxxxxx
    xxxxxxxx
    xx xx xx
    */
   for (int i = 0; i < 8; ++i)
   { //for every row int ghost bitmap

      for (int j = 0; j < 8; ++j)
      { //for every bit in uint8_t ghost bitmap

         if ((ghost_bitmap[i] & (1 << (8 - j - 1))) != 0)
         {
            draw_rectangle(frame, x + j * scale, y + i * scale, scale, scale, color);
         }
      }
   }
}

void draw_pacman_dir(fb_data *frame, int x, int y, int radius, uint16_t color, int direction)
{
   for (int row = y - radius; row < y + radius; row++)
   {
      for (int col = x - radius; col < x + radius; col++)
      {
         if (row > 0 && col > 0 && row < frame->height && col < frame->width)
         {
            if ((pixel_dist_squared(col, row, x, y) <= (radius * radius)) &&
                (abs(x - col) > (y - row)) && direction == UP)
            {
               frame->fb[row * frame->width + col] = color; //drawing pacman facing up
            }
            else if ((pixel_dist_squared(col, row, x, y) <= (radius * radius)) &&
                     (abs(x - col) > (row - y)) && direction == DWN)
            {
               frame->fb[row * frame->width + col] = color; //drawing pacman facing down
            }
            else if ((pixel_dist_squared(col, row, x, y) <= (radius * radius)) &&
                     (abs(row - y) > (col - x)) && direction == RIGHT)
            {
               frame->fb[row * frame->width + col] = color; //drawing pacman facing right
            }
            else if ((pixel_dist_squared(col, row, x, y) <= (radius * radius)) &&
                     (abs(row - y) > (x - col)) && direction == LEFT)
            {
               frame->fb[row * frame->width + col] = color; //drawing pacman facing left
            }
         }
      }
   }
}
