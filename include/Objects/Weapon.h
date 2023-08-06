#pragma once
#include "MovingObject.h"

/* ----------------------------------------------------------
 * class for Weapon object (inherited from MovingObject class).
 * the game can be expanded to contain more types of weapons by gifts.
 */

class Weapon : public MovingObject
{
public:
  void collide(Ball&) override;
  void collide(Wall&) override;
  bool isDel();
  void setDel();

private:
  bool m_deleted = false;
};
