#pragma once
#include "Button.h"

/* ----------------------------------------------------------
 * class for mute button (inherited from button class).
 */

class Mute : public Button
{
public:
  Mute(const sf::Vector2f&, const sf::Vector2f&, Action);
  Action action(sf::RenderWindow&) override;

};
