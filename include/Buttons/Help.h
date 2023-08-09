#pragma once
#include "Button.h"

/* ----------------------------------------------------------
 * class for help button and screen (inherited from button class).
 */

class Help : public Button
{
public:
  Help(float, float, const sf::Vector2f&, const sf::Vector2f&, const sf::Vector2f&);
  Action action(sf::RenderWindow&) override;

private:
  void drawHelp(sf::RenderWindow&) const;

  std::unique_ptr<Button> m_back;
  sf::Sprite m_help;
};
