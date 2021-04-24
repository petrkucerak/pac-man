#ifndef TEXT_FB_H
#define TEXT_FB_H
#include "data_structures.h"
#include "font_types.h"

void draw_char(fb_data *frame, char letter, int x, int y, int scale, font_descriptor_t *font, uint16_t color);
int char_width(font_descriptor_t *fdes, int letter);
uint32_t char_offset(font_descriptor_t *fdes, char letter);
void set_background(fb_data *frame, uint16_t color);
void draw_text(fb_data *frame, char* text, int x, int y, int scale, font_descriptor_t *font, uint16_t color);
void draw_text_center(fb_data *frame, char *text, int x, int y, int scale, font_descriptor_t *font, uint16_t color);
#endif
