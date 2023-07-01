#include "Buttons/Back.h"
#include "EnumClassAction.h"

Back::Back(const sf::Vector2f& size, const sf::Vector2f& position, Action back)
    : Button(size, position, "BACK >")
{
  m_action = back;
}

Action Back::action(sf::RenderWindow& window)
{
  return m_action;
}