#include "Board.h"
#include <functional>
#include "Buttons/NewGame.h"
#include "TimerManager.h"
#include "Menu.h"
#include "Colors.h"

Board::Board(float win_width, float win_height, float info_height) :
    m_status_bar(win_width, win_height, info_height), m_current_level(win_width, win_height, info_height),
    m_msg_rec({win_width, win_height}), m_game_over(win_width, win_height, info_height),
    m_msg_txt("", ResourceManager::Resource().getFont(FontIndex::TRY), win_width / 10)
{
  m_msg_rec.setFillColor(semi_transparent);
  m_msg_txt.setFillColor(sf::Color::White);
  m_msg_txt.setOutlineThickness(10);
  //m_rooms_txt.setStyle(2);
  m_msg_txt.setOutlineColor(sf::Color::Black);
  m_msg_txt.setPosition({win_width / 2, win_height / 2});
}

void Board::run(Action& action, sf::RenderWindow& window)
{
  if(!doAction(action, window)) return;

  while (window.isOpen())
  {
    window.clear();

    m_current_level.draw(window);
    m_status_bar.draw(window);
    checkMsgs(window);
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
        if (!m_next_room && event.key.code == sf::Keyboard::Space)
          m_current_level.createBullet();
      }

    m_current_level.updateStatusBar(m_status_bar);
    if (m_next_room | m_start_level | m_player_ball_collision) continue;

    if (m_current_level.levelOver())
    {
      action = Action(m_current_level.getLevelNum()); // index of next level is current level num
      return;
    }

    m_current_level.movePlayer();
    m_current_level.moveBalls();
    m_current_level.moveBullets();
    m_current_level.handleCollision();
    m_current_level.splitBall();
    m_current_level.erase(m_next_room);

  }
}

void Board::checkMsgs(sf::RenderWindow& window)
{
  if (m_start_level) drawMsg(window, "LEVEL " + std::to_string(m_current_level.getLevelNum()), m_start_level);
  if (m_next_room) drawMsg(window, "NEXT ROOM", m_next_room);
  if (m_current_level.isPlayerBallCollision())
  {
    m_player_ball_collision = true;
    drawMsg(window, "OUCH", m_player_ball_collision);
  }
}


void Board::drawMsg(sf::RenderWindow& window, std::string msg, bool& show)
{
  m_next_room_timer -= TimerManager::Timer().getDeltaTime();
  if (m_next_room_timer <= 0)
  {
    show = false;
    m_next_room_timer = MSG_DELAY;
    return;
  }
  m_msg_txt.setString(msg);
  m_msg_txt.setOrigin({m_msg_txt.getGlobalBounds().width / 2, m_msg_txt.getGlobalBounds().height / 2});
  window.draw(m_msg_rec);
  window.draw(m_msg_txt);
}


bool Board::doAction(Action& action, sf::RenderWindow& window)
{
  if (action > Action::GAME_OVER)
    return false;

  if (action == Action::GAME_OVER)
  {
    action = m_game_over.run(window);
    return false;
  }

  m_current_level.loadLevel(action);
  m_start_level = true;
  return true;
}

//
//void Board::update_status_bar()
//{
//  TimerManager::Timer().updateTimer();
//  m_status_bar.setTime();
//  m_status_bar.setScore(m_current_level.ge);
//  m_status_bar.setLevel(m_current_level.);
//}
