#pragma once
#include "MovingObject.h"
#include "Buttons/Records.h"

class Player : public MovingObject
{
public:
  Player(const sf::Vector2f&, float, float);
  void moveObject(/*const sf::Vector2f&*/) override;
  void setDirection(int);
  void collide(Ball&) override;
  size_t getScore() const;
  void increaseScore();
  void setOriginalPosition();

private:
  int m_x_direction;
  size_t m_life = 3, m_score = 0;
  sf::Vector2f m_original_position;
//  Records m_record;
  float m_velocity_X = 1000;
};
