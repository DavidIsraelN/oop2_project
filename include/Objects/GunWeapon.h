#pragma once
#include "Weapon.h"

/* ----------------------------------------------------------
 * class for GunWeapon object (inherited from Weapon class).
 */

class GunWeapon : public Weapon
{
public:
  GunWeapon(const sf::Vector2f&);
  void moveObject() override;

private:
  float m_speed_y = BULLET_SPEED_Y;
};
