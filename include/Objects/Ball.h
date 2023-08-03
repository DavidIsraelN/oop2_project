#pragma once
#include "MovingObject.h"
#include "Factory.h"
#include <memory>

const float SPEED_X = 350.f, SPEED_Y = -1500.f;
//const float SPEED_X = 200.f, SPEED_Y = -700.f;

class Ball : public MovingObject
{
public:
  Ball(size_t, float, const sf::Vector2f&, float, int);
  void moveObject(/*const sf::Vector2f&*/) override;
  bool collidesWith(Object&) const override;
  void collide(Door&) override;
  void collide(Wall&) override;
  void collide(Weapon&) override;
  void collide(Player&) override;
  bool isDel() const;
  void setDel();
  size_t getRatio() const;
  void setOriginalPosition();

private:
  void setDirection(const sf::FloatRect&);

  float m_speed_x = SPEED_X, m_speed_y = SPEED_Y, m_ceiling, m_begin_ceiling, m_floor;
  size_t m_ratio;
  bool m_deleted = false, m_active_ceiling = false;
  sf::Vector2f m_original_position;
};
