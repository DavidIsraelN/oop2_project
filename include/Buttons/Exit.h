#pragma once
#include "Button.h"

/* ----------------------------------------------------------
 * class for exit button (inherited from button class).
 */

class Exit : public Button
{
public:
  Exit(const sf::Vector2f&, const sf::Vector2f&);
  Action action(sf::RenderWindow&) override;

};
