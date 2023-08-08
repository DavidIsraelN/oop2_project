#pragma once
#include <cstddef>

/* ----------------------------------------------------------
 * enum class for the game operation.
 * the order of the firsts elements (levels and game over)
 * is very important for the operation of the game!
 */

enum class Action
{
  LEVEL1, LEVEL2, LEVEL3, GAME_OVER, BACK_TO_GAME, BACK_TO_MENU, MENU, /* EXIT,
  HELP, MUTE, RECORDS,*/ NOTHING
};


const size_t SCREEN_4K = 1; // Parameter for 4K screen. 1 - no. 2 - yes.
const size_t WIN_WIDTH = 900 * SCREEN_4K;
const size_t WIN_HEIGHT = 600 * SCREEN_4K;

const size_t MAX_NUM_OF_RECORDS = 7; // the amount of records that can be saved
const size_t MAX_PLAYER_NAME = 10;
const size_t MAX_SCORE_DIGIT = 4;
