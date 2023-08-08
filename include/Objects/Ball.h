#pragma once
#include "MovingObject.h"
#include "EnumAndMacroes.h"

/* ----------------------------------------------------------
 * class for ball object (inherited from MovingObject class).
 */

class Ball : public MovingObject
{
public:
  Ball(size_t, float, const sf::Vector2f&, float, int);
  void moveObject() override;
  bool collidesWith(Object&) const override;
  void collide(Door&) override;
  void collide(Wall&) override;
  void collide(Weapon&) override;
  void collide(Player&) override;
  bool isDel() const;
  void setDel();
  size_t getRatio() const;
  void setOriginalState();

private:
  void setDirection(const sf::FloatRect&);

  float m_speed_x = SPEED_BALL_X, m_speed_y = SPEED_BALL_Y, m_ceiling, m_begin_ceiling, m_floor;
  size_t m_ratio;
  bool m_deleted = false, m_active_ceiling = false;
  sf::Vector2f m_original_position;
};
