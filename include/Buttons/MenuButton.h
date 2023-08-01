#pragma once
#include "Button.h"

/*
 * class for menu button (inherited from button class).
 */

class MenuButton : public Button
{
public:
  MenuButton(const sf::Vector2f&, const sf::Vector2f&);
  Action action(sf::RenderWindow&) override;

};
