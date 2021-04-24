/*******************************************************************
  Project main function template for MicroZed based MZ_APO board
  designed by Petr Porazil at PiKRON

  change_me.c      - main file

  include your name there and license for distribution.

  Remove next text: This line should not appear in submitted
  work and project name should be change to match real application.
  If this text is there I want 10 points subtracted from final
  evaluation.

 *******************************************************************/

#define _POSIX_C_SOURCE 200112L

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <unistd.h>

#include "mzapo_parlcd.h"
#include "mzapo_phys.h"
#include "mzapo_regs.h"
#include "data_structures.h"
#include "update_peripherals.h"
#include "text_fb.h"
#include "font_types.h"
#include "map_from_template.h"
#include "map_to_fb.h"
#include "draw_shapes.h"

int main(int argc, char *argv[])
{
  printf("Hello world\n");
  unsigned char *parlcd_mem_base;
  parlcd_mem_base = map_phys_address(PARLCD_REG_BASE_PHYS, PARLCD_REG_SIZE, 0);
  if (parlcd_mem_base == NULL)
  {
    exit(1);
  }
  unsigned char *led_mem_base;
  led_mem_base = map_phys_address(SPILED_REG_BASE_PHYS, SPILED_REG_SIZE, 0);
  if (led_mem_base == NULL)
  {
    exit(1);
  }
  parlcd_hx8357_init(parlcd_mem_base);
  fb_data frame_buff;
  frame_buff.width = 480;
  frame_buff.height = 320;
  frame_buff.fb = (uint16_t *)malloc(480 * 320 * sizeof(uint16_t));
  if (frame_buff.fb == NULL)
  {
    exit(1);
  }
  font_descriptor_t *font = &font_winFreeSystem14x16;
  int pacmanx = map_apo_of_doom.pacman_spawn_x;
  int pacmany = map_apo_of_doom.pacman_spawn_y;
  map_data *map = create_map_data(480, 320, &map_apo_of_doom);
  coords pacman = get_coords_from_template(pacmany, pacmanx, &map_apo_of_doom, 480, 320);
  bool can_move = true;
  while (can_move)
  {
    update_fb(map, &frame_buff);
    draw_circle(&frame_buff, pacman.x, pacman.y ,10,0xffe0);
    lcd_from_fb(&frame_buff, parlcd_mem_base);

    if (map->board_arr[480 * (pacman.y) + pacman.x+1] != BLOCKED)
    {
      pacman.x = pacman.x + 1;
    }
    else
    {
      can_move = false;
    }
  }
  draw_text_center(&frame_buff, "KONEC", 240, 160, 6, font, 0xffff);
  lcd_from_fb(&frame_buff, parlcd_mem_base);
  sleep(1);
  free(frame_buff.fb);
  printf("Goodbye world\n");

  return 0;
}
