#pragma once
#include "Gift.h"

class TimeGift : public Gift
{
public:
  TimeGift(const sf::Vector2f&, float);
  void collide(Player&) override;

private:

};

