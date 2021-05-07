/**
 * @file text_fb.c
 * @author Lukas Nejezchleb (nejezluk@fel.cvut.cz)
 * @brief Module for drawing text to frame buffer
 * @version 0.1
 * @date 2021-05-04
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "text_fb.h"
#include "draw_shapes.h"
#include <stdio.h>

void draw_char(fb_data *frame, char letter, int x, int y, int scale, font_descriptor_t *font, uint16_t color)
{
   int letter_width = char_width(font, letter);
   int letter_height = font->height;
   uint32_t offset = char_offset(font, letter);
   for (int row = 0; row < letter_height; ++row)
   {
      uint16_t bits = *(font->bits + offset + row);
      for (int col = 0; col < letter_width; ++col)
      {
         uint16_t mask = 1 << (15 - col);
         if (bits & mask)
         {
            int rectx = x + col * scale;
            int rexty = y + row * scale;

            draw_rectangle(frame, rectx, rexty, scale, scale, color);
         }
      }
   }
}

int char_width(font_descriptor_t *fdes, int letter)
{
   int width = 0;

   if ((letter >= fdes->firstchar) && ((letter - fdes->firstchar) < fdes->size))
   {
      letter -= fdes->firstchar;
      if (fdes->width)
         width = fdes->width[letter];
      else
         width = fdes->maxwidth;
   }
   return width;
}

uint32_t char_offset(font_descriptor_t *fdes, char letter)
{

   if ((letter >= fdes->firstchar) && ((letter - fdes->firstchar) < fdes->size))
   {
      //character exists in the font
      return (letter - fdes->firstchar) * fdes->height;
   }
   else
   {
      return 0;
   }
}

void draw_text(fb_data *frame, char *text, int x, int y, int scale, font_descriptor_t *font, uint16_t color)
{
   for (int i = 0; text[i] != '\0'; ++i)
   {
      draw_char(frame, text[i], x, y, scale, font, color);
      x = x + char_width(font, text[i]) * scale;
   }
}

void draw_text_center(fb_data *frame, char *text, int x, int y, int scale, font_descriptor_t *font, uint16_t color)
{
   int textlen = 0;
   int textheight = font->height * scale;
   for (int i = 0; text[i] != '\0'; ++i)
   {
      textlen += char_width(font, text[i]) * scale;
   }
   x = x - textlen / 2;
   y = y - textheight / 2;
   for (int i = 0; text[i] != '\0'; ++i)
   {
      draw_char(frame, text[i], x, y, scale, font, color);
      x = x + char_width(font, text[i]) * scale;
   }
}
