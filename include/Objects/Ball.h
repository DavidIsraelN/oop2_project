#pragma once
#include "MovingObject.h"
#include "Factory.h"
#include <memory>

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

private:
  void setDirection(const sf::FloatRect&);

  float m_velocity_x = 350.f, m_velocity_y = -2000.f, m_ceiling, m_begin_ceiling, m_ratio, m_floor;
  bool m_deleted = false, m_active_ceiling = false;
};
