#ifndef UPDATE_LCD_H
#define UPDATE_LCD_H
#include "stdint.h"
#include "data_structures.h"
void lcd_from_fb(const fb_data* frame_buff, unsigned char *parlcd_mem_base);
void led_strip_number(unsigned char *led_mem_base, int max_nr, int nr);
void set_left_RGB(unsigned char *led_mem_base, uint8_t r, uint8_t g, uint8_t b);
void set_right_RGB(unsigned char *led_mem_base, uint8_t r, uint8_t g, uint8_t b);
#endif
