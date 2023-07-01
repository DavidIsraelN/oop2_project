#include "Objects/Ball.h"
#include "TimerManager.h"
#include <iostream>

Ball::Ball(size_t size, const sf::Vector2f& position)
{
  m_jump_height = size * 5;
//  m_velocity_Y = size * 10;
  m_sprite = sf::Sprite(ResourceManager::Resource().getObjTexture(ObjIndex::RED_BALL));
  auto bounds = m_sprite.getLocalBounds();
  m_sprite.setScale(size / bounds.width, size / bounds.height);
  m_sprite.setPosition(position);
  m_sprite.setOrigin(bounds.width / 2, bounds.height / 2);
}

void Ball::moveObject(const sf::Vector2f& window_size)
{
  auto delta_time = TimerManager::Timer().Timer().getDeltaTime();

  auto distance_top = m_jump_height -  (window_size.y - m_sprite.getGlobalBounds().top);
  auto distance_bottom = window_size.y - (m_sprite.getGlobalBounds().top + m_sprite.getGlobalBounds().height);

  //  std::cout << "jump height: " << m_jump_height << std::endl;
  //  std::cout << "window_y: " << window_size.y << std::endl;
  //  std::cout << "position top: " << m_sprite.getGlobalBounds().top << std::endl;
  //  std::cout << "position bottom: " << m_sprite.getGlobalBounds().top + m_sprite.getGlobalBounds().height << std::endl;
//  std::cout << "distance top: " << distance_top << std::endl;
//  std::cout << "distance bottom: " << distance_bottom << std::endl << std::endl;

  auto ratio = (distance_top <= distance_bottom) ? (distance_top / distance_bottom )  : 1 - (distance_bottom / distance_top / 2);
//  if (ratio < 0.01) m_velocity_Y = m_velocity_Y > 0 ? m_velocity_Y : -m_velocity_Y;
  //  auto calculate_y = ratio * (m_world_width - m_win_width) + m_win_width / 2;
//  auto calculate_y = ratio * (window_size.y - m_jump_height) + m_jump_height / 2;

//  std::cout << "ratio: " << ratio << std::endl << std::endl;

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
    m_velocity_X = m_velocity_X > 0 ? -m_velocity_X : m_velocity_X;

  if (m_sprite.getGlobalBounds().left < 0)
    m_velocity_X = m_velocity_X > 0 ? m_velocity_X : -m_velocity_X;

  if (m_sprite.getGlobalBounds().top + m_sprite.getGlobalBounds().height > window_size.y)
    m_velocity_Y = m_velocity_Y > 0 ? -m_velocity_Y : m_velocity_Y;

  if (m_sprite.getGlobalBounds().top < 0 || m_sprite.getGlobalBounds().top < window_size.y - m_jump_height)
    m_velocity_Y = m_velocity_Y > 0 ? m_velocity_Y : -m_velocity_Y;

  m_sprite.move(m_velocity_X * delta_time, m_velocity_Y * delta_time * ratio + m_velocity_Y * delta_time / 15);

}

bool Ball::isDel() const
{
 return m_need_to_delete;
}