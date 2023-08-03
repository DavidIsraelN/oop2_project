#pragma once
#include "Buttons/Button.h"
#include <SFML/Graphics.hpp>

class GameOver
{
public:
  GameOver(float, float/*, float*/);
  Action run(sf::RenderWindow&, size_t) const;

private:
  void buildGameOver(float, float);
  void drawGameOver(sf::RenderWindow&, size_t) const;
  std::vector<std::unique_ptr<Button>> m_buttons;

//  sf::RectangleShape m_rooms_rec;
  sf::Text m_game_over_txt;
};

