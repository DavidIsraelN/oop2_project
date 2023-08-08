#include "Buttons/Exit.h"

//----------------------------------------------------------
Exit::Exit(const sf::Vector2f& size, const sf::Vector2f& position)
  : Button(size, position,"EXIT"/*, Action::EXIT*/)
{ }

//----------------------------------------------------------
Action Exit::action(sf::RenderWindow& window)
{
  window.close();
  return getAction();
}
