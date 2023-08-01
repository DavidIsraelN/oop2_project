#include "Buttons/Exit.h"
#include "EnumClassAction.h"

Exit::Exit(float width, float height)
    : Button(sf::Vector2f(width / 3.f, height / 7.f), sf::Vector2f(width / 2, 10.f * height / 12), "Exit") { }


Action Exit::action(sf::RenderWindow& window)
{
  window.close();
  return Action::EXIT;
}
