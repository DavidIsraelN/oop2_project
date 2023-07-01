#include "Controller.h"


Controller::Controller() : m_window(sf::VideoMode(WIN_WIDTH, WIN_HEIGHT + INFO_HEIGHT), "Bubble Trouble"),
                           m_board(WIN_WIDTH, WIN_HEIGHT, INFO_HEIGHT), m_menu(WIN_WIDTH, WIN_HEIGHT + INFO_HEIGHT) { }


void Controller::run()
{
//  m_board.setAction(m_menu.run(m_window));
//
//  while (m_window.isOpen())
//    m_board.run(m_window);
//  //
//  auto action = m_menu.run(m_window);
  auto action = Action::MENU;
  while (m_window.isOpen())
  {
    if (action == Action::MENU)
      action = m_menu.run(m_window);
    m_board.run(action, m_window);
  }

  //  m_window.clear();
//  m_window.display();
//  while (m_window.isOpen())
//  {
//    for (auto event = sf::Event{}; m_window.waitEvent(event); )
//      switch (event.type)
//      {
//      case sf::Event::Closed:
//        m_window.close();
//      }
//
//  }
}