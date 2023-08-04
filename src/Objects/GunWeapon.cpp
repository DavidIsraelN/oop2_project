#include "Objects/GunWeapon.h"
#include "TimerManager.h"

GunWeapon::GunWeapon(const sf::Vector2f& position)
{
  m_sprite = sf::Sprite(ResourceManager::Resource().getObjTexture(ObjIndex::BULLET));
  const auto bounds = m_sprite.getLocalBounds();
  m_sprite.setScale(BULLET_SIZE / bounds.width, BULLET_SIZE / bounds.height);
  m_sprite.setPosition(position);
  m_sprite.setOrigin(bounds.width / 2, bounds.height / 2);
}

void GunWeapon::moveObject()
{
  auto delta_time = TimerManager::Timer().Timer().getDeltaTime();

  m_sprite.move(0, m_speed_y * delta_time);

  if (m_sprite.getGlobalBounds().top < 0)
    setDel();
}
