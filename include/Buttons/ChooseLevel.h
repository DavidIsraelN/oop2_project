#pragma once
#include "Button.h"

/* ----------------------------------------------------------
 * class for choose level button (inherited from button class).
 */

class ChooseLevel : public Button
{
public:
  ChooseLevel(const sf::Vector2f&, const sf::Vector2f&, Action);
  Action action(sf::RenderWindow&) override;

};
