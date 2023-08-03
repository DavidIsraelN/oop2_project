#include "Board.h"
#include "Buttons/NewGame.h"
#include "TimerManager.h"
#include "EnumClassAction.h"
#include "Menu.h"
#include "Colors.h"

//----------------------------------------------------------
Board::Board(float win_width, float win_height/*, float info_height*/) :
  m_status_bar(win_width, win_height/*, info_height*/),
  m_current_level(win_width, win_height/*, info_height*/),
  m_msg_rec({win_width, win_height}), 
  m_game_over(win_width, win_height/*, info_height*/),
  m_msg_txt("", ResourceManager::Resource().getFont(FontIndex::TRY), win_width / 7)
{
  m_msg_rec.setFillColor(semi_transparent);
  m_msg_txt.setFillColor(sf::Color::White);
  m_msg_txt.setOutlineThickness(10);
  m_msg_txt.setOutlineColor(sf::Color::Black);
  m_msg_txt.setPosition({win_width / 2, win_height / 2.5f});
}

//----------------------------------------------------------
void Board::run(Action& action, sf::RenderWindow& window)
{
  if(!doAction(action, window)) return; // if level load, doAction == true.

  while (window.isOpen())
  {
    window.clear();

    m_current_level.draw(window);
    m_status_bar.draw(window);
    checkMsgs(window);
    window.display();

    for (auto event = sf::Event{}; window.pollEvent(event); )
      if (!handleEvent(window, event, action)) return;

    m_current_level.updateStatusBar(m_status_bar);
    if (m_next_room || m_start_level || m_player_ball_collision) continue;

    if (m_current_level.lifeEnd())
    {
      action = Action::GAME_OVER;
      return;
    }

    if (m_current_level.levelOver())
    {
      action = Action(m_current_level.getLevelNum()); // index of next level is current level num
      //m_temp_score = m_current_level.getScore();
      //m_temp_life = m_current_level.getLife();
      m_new_game = false;
      return;
    }
    
    doStep();
  }
}

//----------------------------------------------------------
bool Board::doAction(Action& action, sf::RenderWindow& window)
{
  switch (action)
  {
  default:
    return false;

  case Action::BACK_TO_GAME:
    return true;

  case Action::GAME_OVER:
    action = m_game_over.run(window, m_current_level.getScore());
    return false;

  case Action::LEVEL1:
  case Action::LEVEL2:
  case Action::LEVEL3:
//    if (m_current_level.levelOver())
//      std::cout << "hhh\n";
    m_current_level.loadLevel(action, m_new_game);
    m_status_bar.setStatusBar(m_current_level.getObjHeight());
    //m_temp_score = 0;
    m_player_ball_collision = m_next_room = false;
    m_start_level = m_new_game = true;
    return true;
  }
  return false; // never got here.
}

//----------------------------------------------------------
bool Board::handleEvent(sf::RenderWindow& window, const sf::Event& event, Action& action)
{
  switch (event.type)
  {
  case sf::Event::Closed:
    window.close();
    return false;

  case sf::Event::KeyPressed:
    if (event.key.code == sf::Keyboard::Escape)
    {
      m_current_level.pause();
      action = Action::MENU;
      return false;
    }
    if (!m_next_room && event.key.code == sf::Keyboard::Space)
      m_current_level.createBullet();
  }
  return true;
}

//----------------------------------------------------------
void Board::doStep()
{
  m_current_level.movePlayer();
  m_current_level.moveBalls();
  m_current_level.moveBullets();
  m_current_level.handleCollision();
  m_current_level.splitBall();
  m_current_level.erase(m_next_room);
}

//----------------------------------------------------------
void Board::checkMsgs(sf::RenderWindow& window)
{
  if (m_start_level) 
    drawMsg(window, "LEVEL " + std::to_string(m_current_level.getLevelNum()), m_start_level);

  if (m_next_room) 
    drawMsg(window, "NEXT ROOM", m_next_room);

  if (m_current_level.PlayerCollidedBall())
  {
    m_player_ball_collision = true;
    drawMsg(window, "OUCH", m_player_ball_collision);
  }
}

//----------------------------------------------------------
void Board::drawMsg(sf::RenderWindow& window, std::string msg, bool& show)
{
  m_msg_timer -= TimerManager::Timer().getDeltaTime();
  if (m_msg_timer <= 0)
  {
    show = false;
    m_msg_timer = MSG_DELAY;
    return;
  }
  m_msg_txt.setString(msg);
  m_msg_txt.setOrigin({m_msg_txt.getGlobalBounds().width / 2,
                       m_msg_txt.getGlobalBounds().height / 2});
  window.draw(m_msg_rec);
  window.draw(m_msg_txt);
}
