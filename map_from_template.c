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
void create_cell(int row, int col, map_template *template, map_data *map);
void create_cross(int row, int col, map_template *template, map_data *map, char center_val);
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
            map = NULL;
        }
        else
        {
            map->board_arr = map_array;
        }
    }

    if (map != NULL)
    {
        int cell_width = screen_w / template->width;
        cell_width = (cell_width % 2 == 0) ? (cell_width - 1) : cell_width;
        int cell_height = screen_h / template->height;
        cell_height = (cell_height % 2 == 0) ? (cell_height - 1) : cell_height;

        if (cell_height > cell_width)
        {
            map->max_object_diameter = cell_width;
        }
        else
        {
            map->max_object_diameter = cell_height;
        }

        map->width = screen_w;
        map->height = screen_h;

        for (int row = 0; row < template->height; row++)
        {
            for (int col = 0; col < template->width; col++)
            {
                //create map for each cell in template
                create_cell(row, col, template, map);
            }
        }
    }
    return map;
}

void create_cell(int row, int col, map_template *template, map_data *map)
{
    char *map_array = map->board_arr;
    int screen_w = map->width;
    int screen_h = map->height;
    char cell_value = template->board[template->width * row + col];

    if (cell_value == template->coin)
    {
        create_cross(row, col, template, map, COIN);
    }
    else if (cell_value == template->blank)
    {
        create_cross(row, col, template, map, PASSAGE);
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
        create_cross(row, col, template, map, SUPERCOIN);
    }
}

void create_cross(int row, int col, map_template *template, map_data *map, char center_val)
{
    int screen_w = map->width;
    int screen_h = map->height;
    char *map_array = map->board_arr;

    int cell_width = screen_w / template->width;
    cell_width = (cell_width % 2 == 0) ? (cell_width - 1) : cell_width;
    int cell_height = screen_h / template->height;
    cell_height = (cell_height % 2 == 0) ? (cell_height - 1) : cell_height;
    int offset_x = col * cell_width;
    int offset_y = row * cell_height;

    //from top to bottom
    int begin_index = offset_x + cell_width / 2 + screen_w * (offset_y + cell_height / 2);
    if ((row > 0) && (template->board[(row - 1) * template->width + col] != template->wall))
    {
        begin_index = offset_x + cell_width / 2 + screen_w * offset_y;
    }
    int end_index = offset_x + cell_width / 2 + screen_w * (offset_y + cell_height / 2);
    if ((row < template->height - 1) && (template->board[(row + 1) * template->width + col] != template->wall))
    {
        end_index = offset_x + cell_width / 2 + screen_w * (offset_y + cell_height);
    }
    for (int index = begin_index; index < end_index; index = index + screen_w)
    {
        map_array[index] = PASSAGE;
    }

    //from left to right
    begin_index = offset_x + cell_width / 2 + screen_w * (offset_y + cell_height / 2);
    if ((col > 0) && (template->board[(row) * template->width + col - 1] != template->wall))
    {
        begin_index = offset_x + screen_w * (offset_y + cell_height / 2);
    }
    end_index = offset_x + cell_width / 2 + screen_w * (offset_y + cell_height / 2);
    if ((col < template->width - 1) && (template->board[(row) * template->width + col + 1] != template->wall))
    {
        end_index = offset_x + cell_width + screen_w * (offset_y + cell_height / 2);
    }
    for (int index = begin_index; index < end_index; index = index + 1)
    {
        map_array[index] = PASSAGE;
    }
    //fill in the centre val
    map_array[offset_x + cell_width / 2 + screen_w * (offset_y + cell_height / 2)] = center_val;
}

coords get_coords_from_template(int row, int col, map_template *template, int screen_w, int screen_h)
{
    int cell_width = screen_w / template->width;
    cell_width = (cell_width % 2 == 0) ? (cell_width - 1) : cell_width;
    int cell_height = screen_h / template->height;
    cell_height = (cell_height % 2 == 0) ? (cell_height - 1) : cell_height;
    coords coords = {
        .x = col * cell_width + cell_width / 2,
        .y = row * cell_height + cell_height / 2,
    };
    return coords;
}
