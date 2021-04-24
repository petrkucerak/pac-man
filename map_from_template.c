/*******************************************************************
  Program to create map from template on MicroZed
  based MZ_APO board designed by Petr Porazil at PiKRON

  map_from_template.c      - creates map from template

  (C) Copyright 2021 by Lukas Nejezchleb
      e-mail:   nejezluk@fel.cvut.cz
      license:  any combination of GPL, LGPL, MPL or BSD licenses

 *******************************************************************/
#include "map_from_template.h"
#include <stdlib.h>

//functions used only inside map_from_template
void create_cell(int row, int col, map_template *template, char *map_array, int screen_w, int screen_h);
void create_cross(int row, int col, map_template *template, char *map_array, int screen_w, int screen_h, char center_val);
//end of functions used only inside 

map_data *create_map_data(int screen_w, int screen_h, map_template *template)
{
    map_data *map = malloc(sizeof(map_data));
    if (map != NULL)
    {
        char *map_array = calloc(screen_h * screen_w, sizeof(char));
        if (map_array == NULL)
        {
            free(map);
        }
        else
        {
            map->board_arr = map_array;
        }
    }

    if (map != NULL)
    {

        for (int row = 0; row < template->height; row++)
        {
            for (int col = 0; col < template->width; col++)
            {
                create_cell(row, col, template, map->board_arr, screen_w, screen_h);
            }
        }
    }
    return map;
}

void create_cell(int row, int col, map_template *template, char *map_array, int screen_w, int screen_h)
{
    char cell_value = template->board[template->width * row + col];
    if (cell_value == template->coin)
    {
        create_cross(row, col, template, map_array, screen_w, screen_h, COIN);
    }
    else if (cell_value == template->blank)
    {
        create_cross(row, col, template, map_array, screen_w, screen_h, PASSAGE);
    }
    else if (cell_value == template->wall)
    {
        int cell_width = screen_w / template->width;
        cell_width = (cell_width % 2 == 0) ? (cell_width - 1) : cell_width;
        int cell_height = screen_h / template->height;
        cell_height = (cell_height % 2 == 0) ? (cell_height - 1) : cell_height;
        //fill every pixel with wall
        for (int i = 0; i < cell_width; ++i)
        {
            for (int j = 0; j < cell_height; ++j)
            {
                map_array[(row * cell_height + j) * screen_w + col * cell_width + i] = WALL;
            }
        }
    }
    else if (cell_value == template->special)
    {
        create_cross(row, col, template, map_array, screen_w, screen_h, SUPERCOIN);
    }
}

void create_cross(int row, int col, map_template *template, char *map_array, int screen_w, int screen_h, char center_val)
{
    int cell_width = screen_w / template->width;
    cell_width = (cell_width % 2 == 0) ? (cell_width - 1) : cell_width;
    int cell_height = screen_h / template->height;
    cell_height = (cell_height % 2 == 0) ? (cell_height - 1) : cell_height;
    int offset_x = col * cell_width;
    int offset_y = row * cell_height;
    //fill in the centre point
    map_array[offset_x + cell_width / 2 + screen_w * (offset_y + cell_height / 2)] = center_val;
    //check if should fill passage to the top
    if (row > 0)
    {
        char template_value = template->board[(row - 1) * template->width + col];
        if ((template_value == template->coin) || (template_value == template->special) ||
            (template_value == template->blank))
        {
            //there is something to connect to at the top
            for (int i = 0; i < cell_height / 2; ++i)
            {
                map_array[offset_x + cell_width / 2 + screen_w * (offset_y + i)] = PASSAGE;
            }
        }
    }
    if (row < template->height - 1)
    {
        char template_value = template->board[(row + 1) * template->width + col];
        if ((template_value == template->coin) || (template_value == template->special) ||
            (template_value == template->blank))
        {
            //there is something to connect to at the bottom
            for (int i = cell_height / 2 + 1; i < cell_height; ++i)
            {
                map_array[offset_x + cell_width / 2 + screen_w * (offset_y + i)] = PASSAGE;
            }
        }
    }
    if (col > 0)
    {
        char template_value = template->board[row * template->width + col - 1];
        if ((template_value == template->coin) || (template_value == template->special) ||
            (template_value == template->blank))
        {
            //there is something to connect to at the left
            for (int i = 0; i < cell_width / 2; ++i)
            {
                map_array[offset_x + i + screen_w * (offset_y + cell_height / 2)] = PASSAGE;
            }
        }
    }
    if (col < template->width - 1)
    {
        char template_value = template->board[row * template->width + col + 1];
        if ((template_value == template->coin) || (template_value == template->special) ||
            (template_value == template->blank))
        {
            //there is something to connect to at the left
            for (int i = cell_width / 2 + 1; i < cell_width; ++i)
            {
                map_array[offset_x + i + screen_w * (offset_y + cell_height / 2)] = PASSAGE;
            }
        }
    }
}

coords get_coords_from_template(int row, int col, map_template *template, int screen_w, int screen_h)
{
    int cell_width = screen_w / template->width;
    cell_width = (cell_width % 2 == 0) ? (cell_width - 1) : cell_width;
    int cell_height = screen_h / template->height;
    cell_height = (cell_height % 2 == 0) ? (cell_height - 1) : cell_height;
    coords coords = {
        .x = col*cell_width+cell_width/2,
        .y = row*cell_height+cell_height/2,
    };
    return coords;
}
