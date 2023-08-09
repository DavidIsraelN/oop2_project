#pragma once
#include <SFML/Graphics.hpp>
#include "Level.h"
#include "GameOver.h"
#include "StatusBar.h"
#include "EnumAndMacroes.h"

/* ------------------------------------------------------------------
 * This class is responsible for all the gameplay, 
 * receiving the input from the player and display the game to the screen.
 */

class Board
{
public:
  Board(float, float);
  void run(Action&, sf::RenderWindow&);

private:
  void doStep();
  bool doAction(Action&, sf::RenderWindow&);
  void checkMsgs(sf::RenderWindow&);
  void drawMsg(sf::RenderWindow&, std::string, bool&);
  bool handleEvent(sf::RenderWindow&, const sf::Event&, Action&);

  sf::View m_view;
  Level m_current_level;
  StatusBar m_status_bar;
  GameOver m_game_over;
  sf::RectangleShape m_msg_rec;
  sf::Text m_msg_txt;
  float m_msg_timer = MSG_DELAY;
  bool m_next_room = false, m_start_level = true, m_new_game = true,
       m_disqualification = false;
};
