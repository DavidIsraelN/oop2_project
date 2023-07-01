#include "Buttons/Records.h"
#include "EnumClassAction.h"

Records::Records(float width, float height)
    : Button(sf::Vector2f(width / 3.f, height / 7.f), sf::Vector2f(width / 2, 8.f * height / 12), "Records") { }


Action Records::action(sf::RenderWindow& window)
{
  return Action::RECORDS;
}
