#include "Objects/GunWeapon.h"
#include "TimerManager.h"
#include <iostream>

GunWeapon::GunWeapon(size_t size, const sf::Vector2f& position)
{
  m_sprite = sf::Sprite(ResourceManager::Resource().getObjTexture(ObjIndex::BULLET));
  const auto bounds = m_sprite.getLocalBounds();
  m_sprite.setScale(size / bounds.width, size / bounds.height);
  m_sprite.setPosition(position);
  m_sprite.setOrigin(bounds.width / 2, bounds.height / 2);
}

void GunWeapon::moveObject(/*const sf::Vector2f& window_size*/)
{
  auto delta_time = TimerManager::Timer().Timer().getDeltaTime();

  m_sprite.move(0, m_velocity_Y * delta_time);

  if (m_sprite.getGlobalBounds().top < 0)
    setDel();
}
