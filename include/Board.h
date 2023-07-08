#pragma once
#include <SFML/Graphics.hpp>
#include "Level.h"
#include "StatusBar.h"
#include "GameOver.h"
#include "EnumClassAction.h"
#include "unordered_map"

class Board
{
public:
  Board(float, float, float);
  void run(Action&, sf::RenderWindow&);
  void draw(sf::RenderWindow&) const;
  void handleEvent(sf::Event&);
  void setView(/* direction / pixels */);

private:
  void update_status_bar();
  void doAction(Action);

  Action m_action;
  sf::View m_view;
  Level m_current_level;
  StatusBar m_status_bar;
  GameOver m_game_over;
//  std::unordered_map<Action, std::function<void()>> m_action_map;
};

