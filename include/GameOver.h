#pragma once
#include "Buttons/Button.h"
#include <SFML/Graphics.hpp>

class GameOver
{
public:
  GameOver(float, float, float);
  Action run(sf::RenderWindow&) const;

private:
  void bulidGameOver(float, float);
  void drawGameOver(sf::RenderWindow&) const;
  std::vector<std::unique_ptr<Button>> m_buttons;

//  sf::RectangleShape m_rooms_rec;
  sf::Text m_game_over_txt;
};

