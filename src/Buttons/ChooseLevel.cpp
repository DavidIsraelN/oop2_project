#include "Buttons/ChooseLevel.h"
#include "EnumClassAction.h"
#include "ResourcesManager.h"

ChooseLevel::ChooseLevel(const sf::Vector2f& size, const sf::Vector2f& position, Action level)
  : Button(size, position, "Level " + std::to_string(int(level)+1))
{
  m_action = level;
}

Action ChooseLevel::action(sf::RenderWindow& window)
{
  return m_action;
}
