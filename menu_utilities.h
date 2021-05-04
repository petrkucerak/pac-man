/**
 * @file menu_utilities.h
 * @author Petr Kucera (kucerp28@fel.cvut.cz)
 * @brief Module for drawing menu, setting game settings and starting the game
 * @version 0.1
 * @date 2021-05-04
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include <stdbool.h>
#include "data_structures.h"
#include "font_types.h"

#ifndef MENU_UTILITIES_H
#define MENU_UTILITIES_H

/**
 * @brief Calls other menu functions which set the game parameters or runs the game if user pressed the s key. Quits program if user pressed the q key.
 * 
 * @param frame_buff 
 * @param lcd_mem_base 
 * @param font 
 * @param peripherals 
 */
void run_init_game_menu(fb_data *frame_buff, unsigned char *lcd_mem_base, font_descriptor_t *font, peripherals_data_t peripherals);

/**
 * @brief Function to drow menu with settings to fb_data
 * 
 * @param frame_buff 
 * @param font 
 * @param game_data 
 */
void draw_menu(fb_data *frame_buff, font_descriptor_t *font, game_init_data_t game_data);

/**
 * @brief Displays current amount of lives and lets the user change
 * 
 * @param frame_buff 
 * @param lcd_mem_base 
 * @param font 
 * @param game_data 
 * @return game_init_data_t 
 */
game_init_data_t sub_menu_lives(fb_data *frame_buff, unsigned char *lcd_mem_base, font_descriptor_t *font, game_init_data_t game_data);

/**
 * @brief Displays current map and lets the user change it
 * 
 * @param frame_buff 
 * @param lcd_mem_base 
 * @param font 
 * @param game_data 
 * @return game_init_data_t 
 */
game_init_data_t sub_menu_map(fb_data *frame_buff, unsigned char *lcd_mem_base, font_descriptor_t *font, game_init_data_t game_data);

/**
 * @brief Displays current amount of ghosts and lets the user change
 * 
 * @param frame_buff 
 * @param lcd_mem_base 
 * @param font 
 * @param game_data 
 * @return game_init_data_t 
 */
game_init_data_t sub_menu_ghosts(fb_data *frame_buff, unsigned char *lcd_mem_base, font_descriptor_t *font, game_init_data_t game_data);

#endif
