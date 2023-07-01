#pragma once
#include "MovingObject.h"

class Weapon : public MovingObject
{
public:
  bool isDel();
  void setDel();

private:
  bool m_deleted = false;

};

