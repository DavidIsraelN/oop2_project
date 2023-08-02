#pragma once
#include <SFML/Graphics.hpp>
#include "Level.h"
#include "GameOver.h"
#include "StatusBar.h"
//#include "EnumClassAction.h"

/* ----------------------------------------------------------
 * This class is responsible for all the gameplay, 
 * receiving the input from the player and display the game to the screen.
 */

enum class Action;
const float MSG_DELAY = 1.f;

class Board
{
public:
  Board(float, float, float);
  void run(Action&, sf::RenderWindow&);

private:
  void doStep();
  bool doAction(Action, sf::RenderWindow&);
  void checkMsgs(sf::RenderWindow&);
  void drawMsg(sf::RenderWindow&, std::string, bool&);
  bool handleEvent(sf::RenderWindow&, const sf::Event&, Action&);

  //Action m_action = Action::NOTHING;
  sf::View m_view;
  Level m_current_level;
  StatusBar m_status_bar;
  sf::RectangleShape m_msg_rec;
  sf::Text m_msg_txt;
  float m_msg_timer = MSG_DELAY;
  bool m_next_room = false, m_start_level , m_player_ball_collision = false;
  GameOver m_game_over;
};
