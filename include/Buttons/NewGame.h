#pragma once
#include "Button.h"

/* ----------------------------------------------------------
 * class for new game button and screen (inherited from button class).
 */

class NewGame : public Button
{
public:
  NewGame(float, float, const sf::Vector2f&, const sf::Vector2f&);
  Action action(sf::RenderWindow&) override;

private:
  void drawLevels(sf::RenderWindow&) const;
  void buildLevels(float, float);

  sf::Text m_text_title;
  std::vector<std::unique_ptr<Button>> m_buttons;
};

