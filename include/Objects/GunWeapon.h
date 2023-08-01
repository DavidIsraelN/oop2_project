#pragma once
#include "Weapon.h"

const float BULLET_SPEED_Y = -1000.f;

class GunWeapon : public Weapon
{
public:
  GunWeapon(size_t, const sf::Vector2f&);
  void moveObject(/*const sf::Vector2f&*/) override;

private:
  float m_speed_y = BULLET_SPEED_Y;
};

