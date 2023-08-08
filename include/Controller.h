#pragma once
#include <SFML/Graphics.hpp>
#include "Board.h"
#include "Menu.h"

/* ----------------------------------------------------------
 * This class is responsible for starting and ending the game.
 */

class Controller
{
public:
  Controller();
  void run();

private:
  void runException();

  sf::RenderWindow m_window;
  Board m_board;
  Menu m_menu;
};
