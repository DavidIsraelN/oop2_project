#include "Objects/Wall.h"
#include "Objects/Ball.h"
#include "Objects/Weapon.h"

//-------------------------------------------------------------------
Wall::Wall(const sf::Vector2f& position, float width, float height)
{
  m_sprite = sf::Sprite(ResourceManager::Resource().getTexture(TextureIndex::SPRITE_SEET));
  m_sprite.setTextureRect(ResourceManager::Resource().getTextureRect(StaticObjIndex::WALL));
  const auto bounds = m_sprite.getLocalBounds();
  m_sprite.setScale(width / bounds.width, height / bounds.height);
  m_sprite.setPosition(position);
  m_sprite.setOrigin(bounds.width / 2, bounds.height / 2);
}

//-------------------------------------------------------------------
void Wall::collide(Ball& ball)
{
  ball.collide(*this);
}

//-------------------------------------------------------------------
void Wall::collide(Weapon& weapon)
{
  weapon.collide(*this);
}
