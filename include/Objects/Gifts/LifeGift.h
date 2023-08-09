#pragma once
#include "Gift.h"

class LifeGift : public Gift
{
public:
  LifeGift(const sf::Vector2f&, float);
  void collide(Player&) override;

private:

};

