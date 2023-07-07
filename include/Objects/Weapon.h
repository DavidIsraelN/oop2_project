#pragma once
#include "MovingObject.h"

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

