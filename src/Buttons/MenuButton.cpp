#include "Buttons/MenuButton.h"

//----------------------------------------------------------
MenuButton::MenuButton(const sf::Vector2f& size, const sf::Vector2f& position)
  : Button(size, position, "MENU", Action::MENU)
{ }

//----------------------------------------------------------
Action MenuButton::action(sf::RenderWindow& window)
{
  return getAction();
}
