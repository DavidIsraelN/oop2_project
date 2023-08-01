#pragma once
#include "Button.h"

/*
 * class for help button and screen (inherited from button class).
 */

class Help : public Button
{
public:
  Help(float, float, const sf::Vector2f&, const sf::Vector2f&);
  Action action(sf::RenderWindow&) override;

private:
  void loadHelp();
  void drawHelp(sf::RenderWindow&) const;

  sf::Text m_text_title;
  std::unique_ptr<Button> m_back;
};

