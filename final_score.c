/*******************************************************************
  Program to draw text to frame buffer on MicroZed
  based MZ_APO board designed by Petr Porazil at PiKRON

   final_score.h      - functions for draw final score

  (C) Copyright 2021 by Petr Kucera
      e-mail:   kucerp28@fel.cvut.cz
      license:  any combination of GPL, LGPL, MPL or BSD licenses

 *******************************************************************/

#include <stdio.h>
#include "final_score.h"
#include "data_structures.h"
#include "draw_shapes.h"
#include "update_peripherals.h"
#include "text_fb.h"
#include <unistd.h>

bool draw_final_score(int score, fb_data *frame_buff, unsigned char *lcd_mem_base, font_descriptor_t *font)
{
   char c = ' ';
   while (c != 's' && c != 'q')
   {
      set_background(frame_buff, 0);
      draw_text_center(frame_buff, "SKORE", frame_buff->width / 2, frame_buff->height / 10, 3, font, 0xffff);
      char string_tmp[20];
      snprintf(string_tmp, 20, "%d", score);
      draw_text_center(frame_buff, string_tmp, frame_buff->width / 2, frame_buff->height / 2, 4, font, 0xffff);
      draw_text_center(frame_buff, "ZNOVU [s]        KONEC [q]", frame_buff->width / 2, frame_buff->height - frame_buff->height / 10, 2, font, 0xffff);
      // update display
      lcd_from_fb(frame_buff, lcd_mem_base);
      // scan input
      pthread_mutex_lock(&mtx);
      pthread_cond_wait(&character_has_been_read, &mtx);
      c = read_thread_data.last_read;
      pthread_mutex_unlock(&mtx);
   }
   if(c == 's') return true;
   else return false;
}
