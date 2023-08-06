#pragma once
#include "Buttons/Button.h"
#include <SFML/Graphics.hpp>

/* ------------------------------------------------------------------
 * This class is responsible for game over screen.
 */

class GameOver
{
public:
  GameOver(float, float);
  Action run(sf::RenderWindow&, size_t) const;

private:
  void buildGameOver(float, float);
  void drawGameOver(sf::RenderWindow&, size_t) const;

  std::vector<std::unique_ptr<Button>> m_buttons;
  sf::Text m_game_over_txt;
};
