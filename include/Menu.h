#pragma once
#include "Buttons/Button.h"

enum class Action;

class Menu
{
public:
  Menu(float, float);
  Action run(sf::RenderWindow&);
  void handleKey();
  void handleClick();

private:
  void draw(sf::RenderWindow&) const;
  sf::Text m_text_title;
  std::vector<std::unique_ptr<Button>> m_buttons;
  static bool m_back_button;
};

