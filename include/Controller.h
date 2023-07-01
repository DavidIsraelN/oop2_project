#pragma once
#include <SFML/Graphics.hpp>
#include "Board.h"
#include "Menu.h"

const size_t WIN_WIDTH = 900;
const size_t WIN_HEIGHT = 550;
const size_t  INFO_HEIGHT = 50;

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

