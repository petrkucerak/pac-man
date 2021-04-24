/*******************************************************************
  Program to draw text to frame buffer on MicroZed
  based MZ_APO board designed by Petr Porazil at PiKRON

  text_fb.c      - simple program to draw text

  (C) Copyright 2021 by Lukas Nejezchleb
      e-mail:   nejezluk@fel.cvut.cz
      license:  any combination of GPL, LGPL, MPL or BSD licenses

 *******************************************************************/
#ifndef TEXT_FB_H
#define TEXT_FB_H
#include "data_structures.h"
#include "font_types.h"

/**
 * function to draw char, left upper edge is at x, y
 */
void draw_char(fb_data *frame, char letter, int x, int y, int scale, font_descriptor_t *font, uint16_t color);

/**
 * returns width of character
 */
int char_width(font_descriptor_t *fdes, int letter);

/**
 * returns offset in font bitmap data
 */
uint32_t char_offset(font_descriptor_t *fdes, char letter);

/**
 * draws text to frame buffer, left upper edge is at x, y
 */
void draw_text(fb_data *frame, char* text, int x, int y, int scale, font_descriptor_t *font, uint16_t color);

/**
 * draws text to frame buffer, centre of text is at x, y
 */
void draw_text_center(fb_data *frame, char *text, int x, int y, int scale, font_descriptor_t *font, uint16_t color);
#endif
