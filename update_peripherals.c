/**
 * @file update_peripherals.c
 * @author Lukas Nejezchleb (nejezluk@fel.cvut.cz)
 * @brief Module for setting the peripherals
 * @version 0.1
 * @date 2021-05-04
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "update_peripherals.h"
#include "mzapo_parlcd.h"
#include "mzapo_regs.h"
#include <stdio.h>
#include <stdbool.h>

void lcd_from_fb(const fb_data *frame_buff, unsigned char *parlcd_mem_base)
{
    if (parlcd_mem_base == NULL)
    {
        return;
    }
    parlcd_write_cmd(parlcd_mem_base, 0x2c);
    for (int i = 0; i < frame_buff->width * frame_buff->height; ++i)
    {
        parlcd_write_data(parlcd_mem_base, frame_buff->fb[i]);
    }
}

void led_strip_number(unsigned char *led_mem_base, int max_nr, int nr)
{
    if (max_nr <= 0 || nr < 0 || led_mem_base == NULL)
    {
        return;
    }
    int divisions = max_nr * 2 - 1;
    uint32_t output = 0;
    float width = 32 / (float)divisions;
    int displayed = 1;
    bool active = true; // indicates if it is just space or if the led can light up
    float current_limit = width;
    for (int i = 0; i < 32; ++i)
    {
        if (current_limit < i)
        {
            current_limit += width;
            if (active)
            {

                active = false;
            }
            else
            {
                displayed++;
                active = true;
            }
        }
        if (active && (displayed <= nr))
        {
            output = output | 1;
        }
        output = output << 1;
    }

    *(volatile uint32_t *)(led_mem_base + SPILED_REG_LED_LINE_o) = output;
}

void set_left_RGB(unsigned char *led_mem_base, uint8_t r, uint8_t g, uint8_t b)
{
    if (led_mem_base == NULL)
    {
        return;
    }
    uint32_t color = (r << 16) | (g << 8) | b;
    *(volatile uint32_t *)(led_mem_base + SPILED_REG_LED_RGB1_o) = color;
}

void set_right_RGB(unsigned char *led_mem_base, uint8_t r, uint8_t g, uint8_t b)
{
    if (led_mem_base == NULL)
    {
        return;
    }
    uint32_t color = (r << 16) | (g << 8) | b;
    *(volatile uint32_t *)(led_mem_base + SPILED_REG_LED_RGB2_o) = color;
}

void sel_leds_color(unsigned char *led_mem_base, uint32_t color)
{
    if (led_mem_base == NULL)
    {
        return;
    }
    *(volatile uint32_t *)(led_mem_base + SPILED_REG_LED_RGB1_o) = color;
    *(volatile uint32_t *)(led_mem_base + SPILED_REG_LED_RGB2_o) = color;
}
