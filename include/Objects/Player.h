#pragma once
#include "MovingObject.h"
#include "Buttons/Records.h"

/* ----------------------------------------------------------
 * class for Player object (inherited from MovingObject class).
 */

const size_t STARTING_LIFE = 3;
const size_t SPEED = 500;

class Player : public MovingObject
{
public:
  Player(const sf::Vector2f&, float, float);
  void moveObject() override;
  void setDirection(int);
  void setAnimation();
  void collide(Ball&) override;
  size_t getScore() const;
  size_t getLife() const;
  void incOrDecScore(int);
  void setOriginalState();
  void setPosition(const sf::Vector2f&);
  void decreaseLife();
  void setShut();

private:
  void setAnimationIndex();
  void fixPosition(sf::FloatRect&);

  int m_x_direction, m_old_x_direction;
  size_t m_life = STARTING_LIFE, m_score = 0,  m_animation_index = 0;
  sf::Vector2f m_original_position;
  float m_speed = SPEED, m_animation_timer = ANIMATION_TIMER, m_shut_timer = SHUT_TIMER;
  bool m_is_shut = false;
};
