#include "Objects/Weapon.h"
#include "Objects/Ball.h"
#include <iostream>

void Weapon::collide(Ball& ball)
{
  setDel();
  ball.collide(*this);
}

void Weapon::collide(Wall&)
{
  setDel();
}

bool Weapon::isDel()
{
  return m_deleted;
}

void Weapon::setDel()
{
  m_deleted = true;
}