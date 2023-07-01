#include "Objects/Weapon.h"
#include <iostream>


bool Weapon::isDel()
{
  return m_deleted;
}
void Weapon::setDel()
{
  m_deleted = true;
}