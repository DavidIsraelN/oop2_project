#pragma once
#include "Button.h"

/*
 * class for back button (inherited from button class).
 */

class Back : public Button
{
public:
  Back(const sf::Vector2f&, const sf::Vector2f&, Action = Action::BACK_TO_MENU);
  Action action(sf::RenderWindow&) override;

};
