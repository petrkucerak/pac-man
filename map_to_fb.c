/*******************************************************************
  Program to draw map to frame buffer on MicroZed
  based MZ_APO board designed by Petr Porazil at PiKRON

  map_to_fb.c      - program to draw map

  (C) Copyright 2021 by Lukas Nejezchleb
      e-mail:   nejezluk@fel.cvut.cz
      license:  any combination of GPL, LGPL, MPL or BSD licenses

 *******************************************************************/
#include "map_to_fb.h"
#include "map_from_template.h"
#include "text_fb.h"
#include "draw_shapes.h"
bool render_map(map_data *data, fb_data *frame_buff){
    set_background(frame_buff, 0);
    for(int i=0; i<frame_buff->width*frame_buff->height; ++i){
        if(data->board_arr[i]==WALL){
            frame_buff->fb[i] = WALL_COLOR;
        }
         if(data->board_arr[i]==PASSAGE){
            frame_buff->fb[i] = PATH_COLOR;
        }
        if(data->board_arr[i]==COIN){
            int x= i%frame_buff->width;
            int y= i/frame_buff->width;
            draw_circle(frame_buff, x,y,5, 0xd000);
        }
        if(data->board_arr[i]==SUPERCOIN){
             int x= i%frame_buff->width;
            int y= i/frame_buff->width;
            draw_circle(frame_buff, x,y,5, 0xf91f);
        }
    }
    return true;
}
