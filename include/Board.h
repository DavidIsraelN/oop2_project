#pragma once
#include <SFML/Graphics.hpp>
#include "Level.h"
#include "GameOver.h"
#include "StatusBar.h"
#include "EnumClassAction.h"
#include "unordered_map"

const float MSG_DELAY = 1.f;

class Board
{
public:
  Board(float, float, float);
  void run(Action&, sf::RenderWindow&);
  void draw(sf::RenderWindow&) const;
  void handleEvent(sf::Event&);
  void setView(/* direction / pixels */);

private:
//  void update_status_bar();
  bool doAction(Action&, sf::RenderWindow&);
  void checkMsgs(sf::RenderWindow&);
  void drawMsg(sf::RenderWindow&, std::string, bool&);

  Action m_action;
  sf::View m_view;
  Level m_current_level;
  StatusBar m_status_bar;
  sf::RectangleShape m_msg_rec;
  sf::Text m_msg_txt;
  float m_next_room_timer = MSG_DELAY;
  bool m_next_room = false, m_start_level, m_player_ball_collision = false;
  GameOver m_game_over;
//  std::unordered_map<Action, std::function<void()>> m_action_map;
};

