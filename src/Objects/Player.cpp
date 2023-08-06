#include "Objects/Player.h"
#include "Sound.h"
#include "TimerManager.h"
#include <iostream>

const int BALL_COLLIDE_SCORE = -15;

//-------------------------------------------------------------------
Player::Player(const sf::Vector2f& position, float width, float height)
  : m_original_position(position)
{
  m_sprite = sf::Sprite(ResourceManager::Resource().getObjTexture(ObjIndex::PLAYER));
  const auto bounds = m_sprite.getLocalBounds();
  m_sprite.setScale(width*2 / bounds.width, height*2 / bounds.height);
  setOriginalState();
  m_sprite.setOrigin(bounds.width / 2, bounds.height / 1.3f);
}

//-------------------------------------------------------------------
void Player::setOriginalState()
{
  m_sprite.setPosition(m_original_position);
}

//-------------------------------------------------------------------
void Player::setPosition(const sf::Vector2f& position)
{
  m_sprite.setPosition(position);
  m_original_position = position;
}

//-------------------------------------------------------------------
void Player::moveObject()
{
  auto delta_time = TimerManager::Timer().Timer().getDeltaTime();
  m_sprite.move(m_x_direction * m_speed * delta_time, 0);
}

//-------------------------------------------------------------------
void Player::setDirection(int x_direction)
{
  m_x_direction = x_direction;
}

//-------------------------------------------------------------------
void Player::collide(Ball&)
{
  Sound::Sounds().Play(SoundIndex::DEATH);
  decreaseLife();
  incOrDecScore(BALL_COLLIDE_SCORE);
}

//-------------------------------------------------------------------
size_t Player::getScore() const
{
  return m_score;
}

//-------------------------------------------------------------------
size_t Player::getLife() const
{
  return m_life;
}

//-------------------------------------------------------------------
void Player::incOrDecScore(int inc_or_dec)
{
  if (int(m_score) + inc_or_dec < 0)
  {
    m_score = 0;
    return;
  }
  m_score += inc_or_dec;
}

//-------------------------------------------------------------------
void Player::decreaseLife()
{
  --m_life;
}
