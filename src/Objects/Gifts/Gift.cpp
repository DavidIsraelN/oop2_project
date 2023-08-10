#include "Objects/Gifts/Gift.h"
#include "TimerManager.h"

//-------------------------------------------------------------------
Gift::Gift(const sf::Vector2f& position, float floor) : m_floor(floor)
{
  m_sprite = sf::Sprite(ResourceManager::Resource().getTexture(TextureIndex::SPRITE_SEET));
  m_sprite.setTextureRect(ResourceManager::Resource().getTextureRect(StaticObjIndex::GIFT));
  const auto bounds = m_sprite.getLocalBounds();
  m_sprite.setScale(GIFT_SIZE / bounds.width, GIFT_SIZE / bounds.height);
  m_sprite.setPosition(position);
  m_sprite.setOrigin(bounds.width / 2, bounds.height / 2);
}

//-------------------------------------------------------------------
void Gift::moveObject()
{
  if (!checkTimer()) return;

  if (m_sprite.getGlobalBounds().top + m_sprite.getGlobalBounds().height >= m_floor) return;

  m_sprite.move(0, m_speed_y * TimerManager::Timer().Timer().getDeltaTime());
}

//-------------------------------------------------------------------
bool Gift::isDel() const
{
  return m_deleted;
}

//-------------------------------------------------------------------
void Gift::setDel()
{
  m_deleted = true;
}

//-------------------------------------------------------------------
bool Gift::checkTimer()
{
  m_gift_timer -= TimerManager::Timer().getDeltaTime();
  if (m_gift_timer <= 0)
  {
    setDel();
    return false;
  }
  return true;
}
