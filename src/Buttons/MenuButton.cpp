#include "Buttons/MenuButton.h"
#include "EnumClassAction.h"

//----------------------------------------------------------
MenuButton::MenuButton(const sf::Vector2f& size, const sf::Vector2f& position)
  : Button(size, position, "Menu", Action::MENU)
{ }
//: Button(sf::Vector2f(width / 3.f, height / 7.f), sf::Vector2f(width / 2, height / 2)

//----------------------------------------------------------
Action MenuButton::action(sf::RenderWindow& window)
{
  return getAction();
}
