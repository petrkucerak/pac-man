/*******************************************************************
  Program to draw text to frame buffer on MicroZed
  based MZ_APO board designed by Petr Porazil at PiKRON

  final_score.h      - functions for draw final score

  (C) Copyright 2021 by Petr Kucera
      e-mail:   kucerp28@fel.cvut.cz
      license:  any combination of GPL, LGPL, MPL or BSD licenses

 *******************************************************************/
#include <stdbool.h>
#include "data_structures.h"
#include "font_types.h"

#ifndef FINAL_SCORE_H
#define FINAL_SCORE_H

/**
 * function draw final score
 * @return false - quit game; true - play game again
 */
bool draw_final_score(int score, fb_data *frame_buff, unsigned char *lcd_mem_base, font_descriptor_t *font);

#endif
