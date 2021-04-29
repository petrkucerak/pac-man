/*******************************************************************
  Program to draw text to frame buffer on MicroZed
  based MZ_APO board designed by Petr Porazil at PiKRON

  game.c      - file with game logic

  (C) Copyright 2021 by Petr Kucera, Lukas Nejezchleb
      e-mail:   kucerp28@fel.cvut.cz, nejezluk@fel.cvut.cz
      license:  any combination of GPL, LGPL, MPL or BSD licenses

 *******************************************************************/

#ifndef GAME_H
#define GAME_H
#include "data_structures.h"
#include "pacman.h"
#include "ghost.h"

int run_game(game_init_data_t* game_data, peripherals_data_t* peripherals);

#endif
