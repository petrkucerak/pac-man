/**
 * @file final_score.h
 * @author Petr Kucera (kucerp28@fel.cvut.cz)
 * @brief Module with function draw final score that draws the final score to the screen and waits for user input. Returns true if the user pressed the s key and therefor wants to continue playing or the q key indicating he wants to end the program
 * @version 0.1
 * @date 2021-05-04
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include <stdbool.h>
#include "data_structures.h"
#include "font_types.h"

#ifndef FINAL_SCORE_H
#define FINAL_SCORE_H

/**
 * @brief Draws the final score to the screen and waits for user input
 * 
 * @param score
 * @param frame_buff
 * @param lcd_mem_base
 * @param font
 * @return true if the user pressed the s key and therefor wants to continue playing
 * @return false if the user pressed the q key indicating he wants to end the program
 */
bool draw_final_score(int score, fb_data *frame_buff, unsigned char *lcd_mem_base, font_descriptor_t *font);

#endif
