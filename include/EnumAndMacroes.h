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

const size_t VIEW_OFFSET = WIN_WIDTH / 90 * SCREEN_4K;

const size_t MAX_NUM_OF_RECORDS = 7; // the amount of records that can be saved
const size_t MAX_PLAYER_NAME = 10;
const size_t MAX_SCORE_DIGIT = 4;

const float SPEED_BALL_X = 200.f * SCREEN_4K;
const float SPEED_BALL_Y = -700.f * SCREEN_4K;
const float SPEED_GIFT_Y = 100 * SCREEN_4K;
const size_t BALLS_KIND = 4;

const size_t STARTING_LIFE = 3;
const size_t PLAYER_SPEED = 400 * SCREEN_4K;

const float BULLET_SPEED_Y = -1000.f * SCREEN_4K;
const size_t BULLET_SIZE = 10 * SCREEN_4K;
const size_t GIFT_SIZE = 30 * SCREEN_4K;

const float ANIMATION_TIMER = 0.05f;
const float SHUT_TIMER = 0.1f;
const float BOOM_TIMER = 0.05f;
const float GIFT_TIMER = 5;
const float BULLET_DELAY = 0; // 0.4f
const float MSG_DELAY = 1.5f;

const int LEFT_DIRECTION = -1;
const int RIGHT_DIRECTION = 1;
const int STAND = 0;

const size_t NEXT_LEVEL_SCORE = 20;
const int BALL_COLLIDE_SCORE = -15;

const float ADDITIONAL_TIME_GIFT = 10;