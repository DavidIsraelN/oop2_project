#pragma once
#include "Weapon.h"

const float BULLET_SPEED_Y = -1000.f;
const size_t BULLET_SIZE = 15;

class GunWeapon : public Weapon
{
public:
  GunWeapon(const sf::Vector2f&);
  void moveObject(/*const sf::Vector2f&*/) override;

private:
  float m_speed_y = BULLET_SPEED_Y;
};

