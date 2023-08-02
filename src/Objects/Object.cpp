#include "Objects/Object.h"
#include <iostream>

void Object::draw(sf::RenderWindow& window) const
{
  window.draw(m_sprite);
}

//-------------------------------------------------------------------
bool Object::collidesWith(Object& other_obj) const
{
  return m_sprite.getGlobalBounds().intersects(other_obj.m_sprite.getGlobalBounds());
}

//-------------------------------------------------------------------
sf::FloatRect Object::getGlobalBounds() const
{
  //std::cout << m_sprite.getGlobalBounds().height << " " << m_sprite.getGlobalBounds().left << "\n";
  return m_sprite.getGlobalBounds();
}
