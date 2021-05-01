/*******************************************************************
  Config file for project apoman for MicroZed based MZ_APO board
  designed by Petr Porazil at PiKRON

  config.h      - config file

(C) Copyright 2021 by Petr Kucera and Lukas Nejezchleb
      e-mails:   kucerp28@fel.cvut.cz , nejezluk@fel.cvut.cz
      license:  any combination of GPL, LGPL, MPL or BSD licenses
 *******************************************************************/
#ifndef CONFIG_H
#define CONFIG_H

#define KEY_UP 'w'
#define KEY_DWN 's'
#define KEY_LEFT 'a'
#define KEY_RIGHT 'd'
#define KEY_QUIT 'q'

#define COIN_SCORE_INCECREASE 100
#define GHOST_SCORE_INCECREASE 200
#define SCARE_REGIME_DURATION 300 //in game tics
#define GAME_SPEED 2 //ammount of ticks in one frame

#define UP 1
#define RIGHT 2
#define DWN 3
#define LEFT 4

#define LED_SCARE_COLOR1 0
#define LED_SCARE_COLOR2 0xf
#define LED_NORMAL_COLOR 0xf00


#endif
