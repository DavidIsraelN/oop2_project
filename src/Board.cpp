#include "Board.h"
#include <functional>
#include "Buttons/NewGame.h"
#include "TimerManager.h"
#include "Menu.h"

Board::Board(float win_width, float win_height, float info_height) :
    m_status_bar(win_width, win_height, info_height), m_current_level(win_width, win_height)
{
//  m_action_map[Action::LEVEL1] = std::bind(&Level::load_1, &m_current_level);
//  m_action_map[Action::LEVEL2] = std::bind(&Level::load_2, &m_current_level);
//  m_action_map[Action::LEVEL3] = std::bind(&Level::load_3, &m_current_level);
//  m_action_map[Action::MENU] = std::bind(&Menu::run, &m_current_level);
  //m_action_map[Action::NEW_GAME] = std::bind(&NewGame::action, &m_current_level);
}

void Board::run(Action& action, sf::RenderWindow& window)
{
  doAction(action);

//  sf::Clock clock;

  while (window.isOpen())
  {
    window.clear(sf::Color::Yellow);
    m_current_level.draw(window);
    m_status_bar.draw(window);
    window.display();

    for (auto event = sf::Event{}; window.pollEvent(event); )
      switch (event.type)
      {
      case sf::Event::Closed:
        window.close();
        return;

      case sf::Event::KeyPressed:
        if (event.key.code == sf::Keyboard::Escape)
        {
          m_current_level.pause();
          action = Action::MENU;
          return;
        }

        if (event.key.code == sf::Keyboard::Space)
          m_current_level.createBullet();
      }
    m_current_level.movePlayer();
    m_current_level.moveBalls();
    m_current_level.moveBullets();
//  m_current_level.handleCollision();
    m_current_level.erase();
    TimerManager::Timer().updateTimer();
    m_status_bar.setTime();
//    levelAction(clock.restart());
//    setLevel(window);
  }
}
void Board::doAction(Action action)
{
  if (action > Action::LEVEL3)
    return;

  m_current_level.loadLevel(action);
}