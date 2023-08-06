#include "Objects/Ball.h"
#include "Colors.h"
#include "Objects/Door.h"
#include "Objects/Player.h"
#include "Objects/Wall.h"
#include "Sound.h"
#include "TimerManager.h"
#include <iostream>

//-------------------------------------------------------------------
Ball::Ball(size_t ratio, float base_size, const sf::Vector2f& position, float floor, int x_direction)
    : m_ratio(ratio), m_floor(floor), m_original_position(position)
{
  m_speed_x *= x_direction;
  auto size = (ratio * 0.5f + 0.5f) * base_size;
  m_ceiling = m_floor - (-int(ratio) * 0.5f + 6.5f) * size;
  m_sprite = sf::Sprite(ResourceManager::Resource().getObjTexture(ObjIndex::BALL));
  m_sprite.setColor(getColor(ratio - 1));
  auto bounds = m_sprite.getLocalBounds();
  m_sprite.setScale(size / bounds.width, size / bounds.height);
  m_sprite.setOrigin(bounds.width / 2, bounds.height / 2);
  setOriginalState();
}

//-------------------------------------------------------------------
void Ball::moveObject()
{
  auto delta_time = TimerManager::Timer().Timer().getDeltaTime();
  auto distance_top = m_sprite.getGlobalBounds().top - 
    (m_active_ceiling ? m_ceiling : m_begin_ceiling);
  auto distance_bottom = m_floor -
    (m_sprite.getGlobalBounds().top + m_sprite.getGlobalBounds().height);
  auto ratio = (distance_top <= distance_bottom)? 
    (distance_top / distance_bottom )  : 1 - (distance_bottom / distance_top / 2);

  if (ratio < 0.01) ratio = 0.01;
  else if (ratio < 0.02) ratio = 0.02;

  if (m_sprite.getGlobalBounds().top < m_ceiling)
    m_speed_y *= m_speed_y > 0 ? 1 : -1;

  m_sprite.move(m_speed_x * delta_time,
                m_speed_y * delta_time * ratio + m_speed_y * delta_time / 15);
}

//-------------------------------------------------------------------
void Ball::setDirection(const sf::FloatRect& bounds)
{

  if (m_sprite.getGlobalBounds().top + m_sprite.getGlobalBounds().height > m_floor)
  {
    m_speed_y *= m_speed_y > 0 ? -1 : 1;
    m_active_ceiling = true;
  }
  else if (bounds.top + bounds.height - m_sprite.getGlobalBounds().top > 0 &&
             bounds.top + bounds.height - m_sprite.getGlobalBounds().top < bounds.height / 10)
    m_speed_y *= m_speed_y > 0 ? 1 : -1;
  else if (m_sprite.getGlobalBounds().left < bounds.left)
    m_speed_x *= m_speed_x > 0 ? -1 : 1;
  else
    m_speed_x *= m_speed_x > 0 ? 1 : -1;
}

//-------------------------------------------------------------------
void Ball::setOriginalState()
{
  m_sprite.setPosition(m_original_position);
  m_begin_ceiling = std::min(m_sprite.getGlobalBounds().top, m_ceiling);
  m_active_ceiling = false;
  m_deleted = false;
}

//-------------------------------------------------------------------
bool Ball::isDel() const
{
  return m_deleted;
}

//-------------------------------------------------------------------
void Ball::setDel()
{
  m_deleted = true;
}

//-------------------------------------------------------------------
size_t Ball::getRatio() const
{
  return m_ratio;
}

//-------------------------------------------------------------------
bool Ball::collidesWith(Object& other_obj) const
{
  return collidesWith(other_obj);
//  if (!other_obj.collidesWith(*this)) return false;
//  auto distance = sqrt(pow(other_obj - a, 2) + pow(y - b, 2));
}

//-------------------------------------------------------------------
void Ball::collide(Door& door)
{
  setDirection(door.getGlobalBounds());
}

//-------------------------------------------------------------------
void Ball::collide(Wall& wall)
{
  setDirection(wall.getGlobalBounds());
}

//-------------------------------------------------------------------
void Ball::collide(Weapon&)
{
  setDel();
  Sound::Sounds().Play(SoundIndex::HIT);
  // random gift
}

//-------------------------------------------------------------------
void Ball::collide(Player& player)
{
 player.collide(*this);
}
