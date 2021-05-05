/**
 * @file update_peripherals.h
 * @author Lukas Nejezchleb (nejezluk@fel.cvut.cz)
 * @brief Module for setting the peripherals
 * @version 0.1
 * @date 2021-05-04
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef UPDATE_LCD_H
#define UPDATE_LCD_H
#include <stdint.h>
#include "data_structures.h"

/**
 * @brief Sets the lcd pixels to colors described in frame buffer
 * 
 * @param frame_buff 
 * @param parlcd_mem_base 
 */
void lcd_from_fb(const fb_data *frame_buff, unsigned char *parlcd_mem_base);

/**
 * @brief Shows number as number of clusters on the led strip
 * 
 * @param led_mem_base 
 * @param max_nr 
 * @param nr 
 */
void led_strip_number(unsigned char *led_mem_base, int max_nr, int nr);

/**
 * @brief Sets the left RGB led to particular rgb color
 * 
 * @param led_mem_base 
 * @param r 
 * @param g 
 * @param b 
 */
void set_left_RGB(unsigned char *led_mem_base, uint8_t r, uint8_t g, uint8_t b);

/**
 * @brief Sets the right RGB led to particular rgb color
 * 
 * @param led_mem_base 
 * @param r 
 * @param g 
 * @param b 
 */
void set_right_RGB(unsigned char *led_mem_base, uint8_t r, uint8_t g, uint8_t b);

/**
 * @brief Sets both to color
 * 
 * @param led_mem_base 
 * @param color 
 */
void sel_leds_color(unsigned char *led_mem_base, uint32_t color);
#endif
