/**
 * @file map_to_fb.c
 * @author Lukas Nejezchleb (nejezluk@fel.cvut.cz)
 * @brief Module for rendering the map to the frame buffer. Houses function render map
 * @version 0.1
 * @date 2021-05-04
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include "map_to_fb.h"
#include "map_from_template.h"
#include "text_fb.h"
#include "draw_shapes.h"
#include "config.h"

bool render_map(map_data *data, fb_data *frame_buff)
{
   bool ret = false;
   set_background(frame_buff, 0);
   for (int i = 0; i < frame_buff->width * frame_buff->height; ++i)
   {
      if (data->board_arr[i] == WALL)
      {
         frame_buff->fb[i] = WALL_COLOR;
      }
      if (data->board_arr[i] == PASSAGE)
      {
         frame_buff->fb[i] = PATH_COLOR;
      }
      if (data->board_arr[i] == COIN)
      {
         ret = true;
         int x = i % frame_buff->width;
         int y = i / frame_buff->width;
         draw_circle(frame_buff, x, y, COIN_RADIUS, COIN_COLOR);
      }
      if (data->board_arr[i] == SUPERCOIN)
      {
         ret = true;
         int x = i % frame_buff->width;
         int y = i / frame_buff->width;
         draw_circle(frame_buff, x, y, SUPERCOIN_RADIUS, SUPERCOIN_COLOR);
      }
   }
   return ret;
}
