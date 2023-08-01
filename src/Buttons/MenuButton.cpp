#include "Buttons/MenuButton.h"
#include "EnumClassAction.h"

MenuButton::MenuButton(float width, float height)
    : Button(sf::Vector2f(width / 3.f, height / 7.f), sf::Vector2f(width / 2, height / 2), "Menu") { }


Action MenuButton::action(sf::RenderWindow& window)
{
  return Action::MENU;
}
