#pragma once
#include "Objects/MovingObject.h"

class Gift : public MovingObject
{
public:
  Gift(const sf::Vector2f&, float);
  void moveObject() override;
  bool isDel() const;
  void setDel();

private:
  float m_floor, m_speed_y = SPEED_GIFT_Y;
  bool m_deleted = false;
};

