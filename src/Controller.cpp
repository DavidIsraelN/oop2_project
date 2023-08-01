#include "Controller.h"


Controller::Controller() : m_window(sf::VideoMode(WIN_WIDTH, WIN_HEIGHT + INFO_HEIGHT), "Bubble Trouble"),
                           m_board(WIN_WIDTH, WIN_HEIGHT, INFO_HEIGHT), m_menu(WIN_WIDTH, WIN_HEIGHT + INFO_HEIGHT) { }


void Controller::run()
{
  auto action = Action::MENU;
  while (m_window.isOpen())
  {
    if (action == Action::MENU)
      action = m_menu.run(m_window);

    if (action == Action::GAME_OVER)
      m_menu.setBackButton(false);

    m_board.run(action, m_window);
  }
}