#include "Controller.h"
#include "EnumClassAction.h"
#include "ResourcesManager.h"
#include <exception>
#include <chrono>
#include <thread>

//----------------------------------------------------------
Controller::Controller() :
  m_window(sf::VideoMode(WIN_WIDTH, WIN_HEIGHT/* + INFO_HEIGHT*/), "Bubble Trouble"),
  m_board(WIN_WIDTH, WIN_HEIGHT/*, INFO_HEIGHT*/), 
  m_menu(WIN_WIDTH, WIN_HEIGHT/* + INFO_HEIGHT*/)
{ }

//----------------------------------------------------------
void Controller::run()
{
  auto action = Action::MENU;
  try {
    while (m_window.isOpen())
    {
      if (action == Action::MENU)
        action = m_menu.run(m_window);

      if (action == Action::GAME_OVER)
        m_menu.setBackButton(false);

      m_board.run(action, m_window);
    }
  }
  catch (std::exception& e) {
    runException();
  }
}

//----------------------------------------------------------
void Controller::runException()
{
  auto e_msg = sf::Text("We've run into a broblem\n\t\tTurns off. . .",
    ResourceManager::Resource().getFont(FontIndex::TRY),
    m_window.getSize().x / 20);
  auto d = m_window.getSize();
  e_msg.setFillColor(sf::Color::Black);
  e_msg.setPosition({ float(m_window.getSize().x) / 2, float(m_window.getSize().y) / 2 });
  e_msg.setOrigin({ e_msg.getGlobalBounds().width / 2,
                    e_msg.getGlobalBounds().height / 2 });

  m_window.clear(sf::Color::Cyan);
  m_window.draw(e_msg);
  m_window.display();
  std::this_thread::sleep_for(std::chrono::seconds(3));
  m_window.close();
}