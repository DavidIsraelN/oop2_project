#pragma once
#include "MovingObject.h"

class Player : public MovingObject
{
public:
  Player() { }
  Player(const sf::Vector2f&, float, float);
  void moveObject(/*const sf::Vector2f&*/) override;
  void setDirection(int);
  void collide(Ball&) override;


private:
  int m_x_direction;
  float m_velocity_X = 1000;
};
