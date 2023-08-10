#pragma once
#include "Gift.h"

/* ----------------------------------------------------------
 * class for life gift object (inherited from Gift class).
 */

class LifeGift : public Gift
{
public:
  LifeGift(const sf::Vector2f&, float);
  void collide(Player&) override;

};
