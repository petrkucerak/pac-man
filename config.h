/**
 * @file config.h
 * @author Lukas Nejezchleb (nejezluk@fel.cvut.cz), Petr Kucera (kucerp28@fel.cvut.cz)
 * @brief File, where user preferences can be set. For example maximum cap for lives, score gained by eating ghosts/coins can be set here.
 * @version 0.1
 * @date 2021-05-04
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef CONFIG_H
#define CONFIG_H

#define KEY_UP 'w'
#define KEY_DWN 's'
#define KEY_LEFT 'a'
#define KEY_RIGHT 'd'
#define KEY_QUIT 'q'
#define PAUSE_KEY 'p'
#define PAUSE_TEXT "GAME IS PAUSED"
#define PAUSE_TEXT_SIZE 4
#define PAUSE_SUBTEXT "press %c to resume or %c to quit"
#define PAUSE_SUBTEXT_SIZE 2
#define PAUSE_SUBTEXT_OFFSET 50
#define PAUSE_FONT font_winFreeSystem14x16
#define PAUSE_COLOR 0xffff

#define COIN_SCORE_INCECREASE 100
#define GHOST_SCORE_INCECREASE 200
#define SCORE_DEATH_PENALTY 0
#define MAX_SCORE 20000 //percentage of this will affect RGB led intensity

#define MAX_GHOSTS '4'
#define MAX_LIVES '4'

#define SCARE_REGIME_DURATION 300 //in game ticks
#define GAME_SPEED 2 //ammount of ticks in one frame

#define GAME_START_TERMINAL "Move pacman with %c%c%c%c keys, to pause press %c, to quit game press %c.\n"
#define GAME_END_TERMINAL "Game has ended with pacman getting score %d and having %d lives\n"

//led colors
#define LED_SCARE_COLOR1 0
#define LED_SCARE_COLOR2 0xf
#define LED_NORMAL_COLOR 0xf00

//map colors
#define WALL_COLOR 0x9
#define PATH_COLOR 0
#define COIN_COLOR 0xd000
#define COIN_RADIUS 5
#define SUPERCOIN_COLOR 0xf91f
#define SUPERCOIN_RADIUS 5

//ghost colors
// green pink  azure red
#define GHOST_COLORS 0x07C0, 0xF01F, 0x07DC, 0xF800
#define GHOST_COLORS_AMMOUNT 4

#define PACMAN_COLOR 0xffe0

//chance for ghosts to switch modes (higher means more unlikely)
#define GHOST_SWITCH_TO_RANDOM 2000
#define GHOST_SWITCH_TO_TARGET 900


#define UP 1
#define RIGHT 2
#define DWN 3
#define LEFT 4

#endif
