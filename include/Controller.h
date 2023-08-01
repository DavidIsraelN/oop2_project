#pragma once
#include <SFML/Graphics.hpp>
#include "Board.h"
#include "Menu.h"

/* ----------------------------------------------------------
 * This class is responsible for starting and ending the game.
 */

const size_t SCREEN_4K = 1; // Parameter for 4K screen. 1 - no. 2 - yes.
const size_t WIN_WIDTH = 900* SCREEN_4K;
const size_t WIN_HEIGHT = 550* SCREEN_4K;
const size_t INFO_HEIGHT = 50* SCREEN_4K;

class Controller
{
public:
  Controller();
  void run();

private:
  sf::RenderWindow m_window;
  Board m_board;
  Menu m_menu;
};
