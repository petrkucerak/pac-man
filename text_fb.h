/**
 * @file text_fb.h
 * @author Lukas Nejezchleb (nejezluk@fel.cvut.cz)
 * @brief Module for drawing text to frame buffer
 * @version 0.1
 * @date 2021-05-04
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef TEXT_FB_H
#define TEXT_FB_H
#include "data_structures.h"
#include "font_types.h"

/**
 * @brief Draws the character to the frame buffer. Left upper corner is at x,y and the char is scale times bigger than the bitmap in font
 * 
 * @param frame
 * @param letter
 * @param x
 * @param y
 * @param scale
 * @param font
 * @param color
 */
void draw_char(fb_data *frame, char letter, int x, int y, int scale, font_descriptor_t *font, uint16_t color);

/**
 * @brief Returns the lenght of given char
 * 
 * @param fdes
 * @param letter
 * @return int 
 */
int char_width(font_descriptor_t *fdes, int letter);

/**
 * @brief Returns offset of given char in bitmap data
 * 
 * @param fdes
 * @param letter
 * @return uint32_t 
 */
uint32_t char_offset(font_descriptor_t *fdes, char letter);

/**
 * @brief Draws text to the frame buffer, x,y are the coordinates of the left upper edge
 * 
 * @param frame
 * @param text
 * @param x
 * @param y
 * @param scale
 * @param font
 * @param color
 */
void draw_text(fb_data *frame, char *text, int x, int y, int scale, font_descriptor_t *font, uint16_t color);

/**
 * @brief Draws the text centered around x,y
 * 
 * @param frame
 * @param text
 * @param x
 * @param y
 * @param scale
 * @param font
 * @param color
 */
void draw_text_center(fb_data *frame, char *text, int x, int y, int scale, font_descriptor_t *font, uint16_t color);
#endif
