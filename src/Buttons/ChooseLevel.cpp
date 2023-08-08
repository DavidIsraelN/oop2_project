#include "Buttons/ChooseLevel.h"
#include "ResourcesManager.h"

//----------------------------------------------------------
ChooseLevel::ChooseLevel(const sf::Vector2f& size, const sf::Vector2f& position, Action level)
  : Button(size, position, "LEVEL " + std::to_string(int(level) + 1), level)
{ }

//----------------------------------------------------------
Action ChooseLevel::action(sf::RenderWindow& window)
{
  return getAction();
}
