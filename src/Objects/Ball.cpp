#include "Objects/Ball.h"
#include "TimerManager.h"
#include <iostream>

Ball::Ball(size_t ratio, float base_size, const sf::Vector2f& position)
{
  auto size =  (ratio * 0.5f + 0.5f) * base_size;
  m_ceiling = (-int(ratio) * 0.5f + 7.f) * size;
  std::cout << m_ceiling << std::endl;
//  m_velocity_Y = size * 10;
  m_sprite = sf::Sprite(ResourceManager::Resource().getObjTexture(ObjIndex::RED_BALL));
  auto bounds = m_sprite.getLocalBounds();
  m_sprite.setScale(size / bounds.width, size / bounds.height);
  m_sprite.setPosition(position);
  m_sprite.setOrigin(bounds.width / 2, bounds.height / 2);
  m_begin_ceiling = m_sprite.getGlobalBounds().top;
}

void Ball::moveObject(const sf::Vector2f& window_size)
{
  auto delta_time = TimerManager::Timer().Timer().getDeltaTime();

  auto distance_top = (m_active_ceiling ? m_ceiling : window_size.y - m_begin_ceiling) - (window_size.y - m_sprite.getGlobalBounds().top);
  auto distance_bottom = window_size.y - (m_sprite.getGlobalBounds().top + m_sprite.getGlobalBounds().height);

  auto ratio = (distance_top <= distance_bottom) ? (distance_top / distance_bottom )  : 1 - (distance_bottom / distance_top / 2);
//  if (ratio < 0.01) m_velocity_Y = m_velocity_Y > 0 ? m_velocity_Y : -m_velocity_Y;
  //  auto calculate_y = ratio * (m_world_width - m_win_width) + m_win_width / 2;
//  auto calculate_y = ratio * (window_size.y - m_jump_height) + m_jump_height / 2;

  //if (ratio < 0) ratio = 0.2f;

  if (ratio < 0.01) ratio = 0.01;
  else if (ratio < 0.02) ratio = 0.02;
//  else if (ratio < 0.3) ratio = 0.3;
//  else if (ratio < 0.4) ratio = 0.4;
//  else if (ratio < 0.5) ratio = 0.5;
//  else if (ratio < 0.6) ratio = 0.6;
//  else if (ratio < 0.7) ratio = 0.7;
//  else if (ratio < 0.8) ratio = 0.8;
//  else if (ratio < 0.9) ratio = 0.9;
//  else if (ratio < 0.1) ratio = 1;


  if (m_sprite.getGlobalBounds().left + m_sprite.getGlobalBounds().width > window_size.x)
    m_velocity_x = m_velocity_x > 0 ? -m_velocity_x : m_velocity_x;

  if (m_sprite.getGlobalBounds().left < 0)
    m_velocity_x = m_velocity_x > 0 ? m_velocity_x : -m_velocity_x;

  if (m_sprite.getGlobalBounds().top + m_sprite.getGlobalBounds().height > window_size.y)
  {
    m_velocity_y = m_velocity_y > 0 ? -m_velocity_y : m_velocity_y;
    m_active_ceiling = true;
  }
  if (m_sprite.getGlobalBounds().top < 0 || m_sprite.getGlobalBounds().top < window_size.y - m_ceiling)
    m_velocity_y = m_velocity_y > 0 ? m_velocity_y : -m_velocity_y;

  m_sprite.move(m_velocity_x * delta_time, m_velocity_y * delta_time * ratio +
                                               m_velocity_y * delta_time / 15);

}

bool Ball::isDel() const
{
 return m_deleted;
}

//-------------------------------------------------------------------
bool Ball::collidesWith(const Object& other_obj) const
{
//  if (!other_obj.collidesWith(*this)) return false;
//  auto distance = sqrt(pow(other_obj - a, 2) + pow(y - b, 2));
}
