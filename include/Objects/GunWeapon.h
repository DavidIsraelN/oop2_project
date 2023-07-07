#pragma once
#include "Weapon.h"

class GunWeapon : public Weapon
{
public:
  GunWeapon(size_t, const sf::Vector2f&);
  void moveObject(/*const sf::Vector2f&*/) override;

private:
  float m_velocity_Y = -1000.f;
};

