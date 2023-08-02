#pragma once

/* ----------------------------------------------------------
 * the order of the firsts elements (levels)
 * is very important for the operation of the game!
 */

enum class Action
{
  LEVEL1, LEVEL2, LEVEL3, GAME_OVER, BACK_TO_GAME, BACK_TO_MENU, MENU, /* EXIT,
  HELP, MUTE, RECORDS,*/ NOTHING
};
