#include "Objects/Door.h"
#include "Objects/Ball.h"

//-------------------------------------------------------------------
Door::Door(const sf::Vector2f& position, float width, float height)
{
  m_sprite = sf::Sprite(ResourceManager::Resource().getObjTexture(ObjIndex::DOOR));
  const auto bounds = m_sprite.getLocalBounds();
  m_sprite.setScale(width / bounds.width, height / bounds.height);
  m_sprite.setPosition(position);
  m_sprite.setOrigin(bounds.width / 2, bounds.height / 2);
}

//-------------------------------------------------------------------
void Door::collide(Ball& ball)
{
  ball.collide(*this);
}
