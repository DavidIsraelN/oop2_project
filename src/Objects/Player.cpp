#include "Objects/Player.h"
#include "Sound.h"
#include "TimerManager.h"

//-------------------------------------------------------------------
Player::Player(const sf::Vector2f& position, float width, float height)
  : m_original_position(position)
{
  m_sprite = sf::Sprite(ResourceManager::Resource().getTexture(TextureIndex::SPRITE_SEET));
  m_sprite.setTextureRect(ResourceManager::Resource().getTextureRect(StaticObjIndex::STAND_PLAYER));
  const auto bounds = m_sprite.getLocalBounds();
  m_sprite.setScale(width*2 / bounds.width, height*2 / bounds.height);
  setOriginalState();
  m_sprite.setOrigin(bounds.width / 2, bounds.height / 1.3f);
  m_old_x_direction = m_x_direction = STAND;
}

//-------------------------------------------------------------------
void Player::setOriginalState()
{
  m_sprite.setPosition(m_original_position);
  m_is_shut = false;
  m_sprite.setTextureRect(ResourceManager::Resource().getTextureRect(StaticObjIndex::STAND_PLAYER));
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
  m_old_x_direction = m_x_direction;
  m_x_direction = x_direction;
}

//-------------------------------------------------------------------
void Player::setAnimation()
{
  auto old_global_bounds = m_sprite.getGlobalBounds();

  if (m_is_shut)
  {
    m_sprite.setTextureRect(ResourceManager::Resource().getTextureRect(StaticObjIndex::SHUT_PLAYER));
    m_shut_timer -= TimerManager::Timer().getDeltaTime();
    if (m_shut_timer <= 0)
      m_is_shut = false;
    if (m_sprite.getScale().x > 0) m_sprite.scale(-1, 1);
    fixPosition(old_global_bounds);
    return;
  }

  if (m_x_direction == STAND)
    m_sprite.setTextureRect(ResourceManager::Resource().getTextureRect(StaticObjIndex::STAND_PLAYER));
  else
  {
    setAnimationIndex();
    m_sprite.setTextureRect(ResourceManager::Resource().getWalkingTextureRect(m_animation_index));
}
    if ((m_x_direction == RIGHT_DIRECTION && m_sprite.getScale().x < 0) ||
        (m_x_direction == LEFT_DIRECTION && m_sprite.getScale().x > 0))
      m_sprite.scale(-1, 1);

    fixPosition(old_global_bounds);
}

//-------------------------------------------------------------------
void Player::collide(Ball&)
{
  Sound::Sounds().Play(SoundIndex::DEATH);
  decreaseLife();
  incOrDecScore(BALL_COLLIDE_SCORE);
  m_is_shut = false;
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

//-------------------------------------------------------------------
void Player::setShut()
{
  m_is_shut = true;
  m_shut_timer = SHUT_TIMER;
}

//-------------------------------------------------------------------
void Player::setAnimationIndex()
{
  if (m_old_x_direction != m_x_direction)
  {
    m_animation_timer = ANIMATION_TIMER;
    m_animation_index = 0;
  }
  m_animation_timer -= TimerManager::Timer().getDeltaTime();
  if (m_animation_timer <= 0)
  {
    m_animation_timer = ANIMATION_TIMER;
    ++m_animation_index;
  }
}

//-------------------------------------------------------------------
void Player::fixPosition(sf::FloatRect& old_global_bounds)
{
  if ((old_global_bounds.left + old_global_bounds.width / 2) != m_sprite.getGlobalBounds().left + m_sprite.getGlobalBounds().width / 2)
  {
    auto d = (m_sprite.getGlobalBounds().left + m_sprite.getGlobalBounds().width / 2) -
             (old_global_bounds.left + old_global_bounds.width / 2);
    m_sprite.setPosition(m_sprite.getPosition().x - d, m_sprite.getPosition().y);
  }
  if (m_sprite.getGlobalBounds().top + m_sprite.getGlobalBounds().height != old_global_bounds.top + old_global_bounds.height)
  {
    auto d = m_sprite.getGlobalBounds().top + m_sprite.getGlobalBounds().height - (old_global_bounds.top + old_global_bounds.height);
    m_sprite.setPosition(m_sprite.getPosition().x, m_sprite.getPosition().y - d);
  }
}



// ============= don't del yet ====================

//    auto old_global_bounds = m_sprite.getGlobalBounds();
//    m_sprite.setTextureRect(ResourceManager::Resource().getTextureRect(StaticObjIndex::STAND_PLAYER));
//    if (m_old_player_state == PlayerState::RIGHT)
//      m_sprite.setPosition(m_sprite.getPosition().x -
//                               (old_global_bounds.left - m_sprite.getGlobalBounds().left), m_sprite.getPosition().y);
//    else if (m_old_player_state == PlayerState::LEFT)
//      m_sprite.setPosition(m_sprite.getPosition().x +
//                               (m_sprite.getGlobalBounds().left + m_sprite.getGlobalBounds().width -
//                                (old_global_bounds.left + old_global_bounds.width)) , m_sprite.getPosition().y);
