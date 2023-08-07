#pragma once

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


// the amount of records that can be saved
const size_t MAX_NUM_OF_RECORDS = 7;
