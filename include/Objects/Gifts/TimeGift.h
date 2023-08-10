#pragma once
#include "Gift.h"

/* ----------------------------------------------------------
 * class for time gift object (inherited from Gift class).
 */

class TimeGift : public Gift
{
public:
  TimeGift(const sf::Vector2f&, float);
  void collide(Player&) override;

};
