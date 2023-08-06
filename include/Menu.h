#pragma once
#include "Buttons/Button.h"

/* ----------------------------------------------------------
 * Class that is responsible for menu screen and all its operation.
 */

enum class Action;

class Menu
{
public:
  Menu(float, float);
  Action run(sf::RenderWindow&);
  void setBackButton(bool);

private:
  void buildMenu(float, float);
  void drawMenu(sf::RenderWindow&) const;

  sf::Text m_text_title;
  std::vector<std::unique_ptr<Button>> m_buttons;
  bool m_back_button = false;
};
