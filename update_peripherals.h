/*******************************************************************
  Simple program to update peripherals on MicroZed
  based MZ_APO board designed by Petr Porazil at PiKRON

  update_peripherals.c      - simple program to update peripherals

  (C) Copyright 2021 by Lukas Nejezchleb
      e-mail:   nejezluk@fel.cvut.cz
      license:  any combination of GPL, LGPL, MPL or BSD licenses

 *******************************************************************/

#ifndef UPDATE_LCD_H
#define UPDATE_LCD_H
#include <stdint.h>
#include "data_structures.h"

//function that updates the LCD from frame buffer. LCD has to be initialised
void lcd_from_fb(const fb_data* frame_buff, unsigned char *parlcd_mem_base);

//function that shows nr on the ledstrip
void led_strip_number(unsigned char *led_mem_base, int max_nr, int nr);

//sets left RGB to particular color
void set_left_RGB(unsigned char *led_mem_base, uint8_t r, uint8_t g, uint8_t b);

//sets right RGB to particular color
void set_right_RGB(unsigned char *led_mem_base, uint8_t r, uint8_t g, uint8_t b);
#endif
