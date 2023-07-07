#include "Objects/Object.h"

void Object::draw(sf::RenderWindow& window) const
{
  window.draw(m_sprite);
}

//-------------------------------------------------------------------
bool Object::collidesWith(Object& other_obj) const
{
  return m_sprite.getGlobalBounds().intersects(other_obj.m_sprite.getGlobalBounds());
}

sf::FloatRect Object::getGlobalBounds() const
{
  return m_sprite.getGlobalBounds();
}
