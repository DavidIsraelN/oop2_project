#include "Objects/Player.h"
#include "TimerManager.h"
#include <iostream>

Player::Player(const sf::Vector2f& position, float width, float height) : m_original_position(position)
{
  m_sprite = sf::Sprite(ResourceManager::Resource().getObjTexture(ObjIndex::PLAYER));
  const auto bounds = m_sprite.getLocalBounds();
  m_sprite.setScale(width*2 / bounds.width, height*2 / bounds.height);
  setOriginalPosition();
  m_sprite.setOrigin(bounds.width / 2, bounds.height / 1.3f);
}

void Player::setOriginalPosition()
{
  m_sprite.setPosition(m_original_position);
}

void Player::moveObject(/*const sf::Vector2f& window_size*/)
{
  auto delta_time = TimerManager::Timer().Timer().getDeltaTime();

//  if (m_x_direction == -1 && m_sprite.getGlobalBounds().left > 0)
//    if (m_sprite.getGlobalBounds().left - m_velocity_X * delta_time >= 0)
//      m_sprite.move(-m_velocity_X * delta_time, 0);
//  if (m_x_direction == 1 && m_sprite.getGlobalBounds().left + m_sprite.getGlobalBounds().width < window_size.x)
//    if (m_sprite.getGlobalBounds().left + m_sprite.getGlobalBounds().width + m_velocity_X * delta_time <= window_size.x)
//      m_sprite.move(m_velocity_X * delta_time, 0);

  m_sprite.move(m_x_direction * m_velocity_X * delta_time, 0);
}

void Player::setDirection(int x_direction)
{
  m_x_direction = x_direction;
}

//-------------------------------------------------------------------
void Player::collide(Ball&)
{
  --m_life;
//  std::cout << "life - " << m_life << "\n";
}

size_t Player::getScore() const
{
  return m_score;
}

void Player::increaseScore()
{
  m_score++;

}
