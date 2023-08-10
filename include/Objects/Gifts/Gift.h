#pragma once
#include "Objects/MovingObject.h"

/* ----------------------------------------------------------
 * class for gifts object (inherited from MovingObject class).
 * the game can be expanded to contain more types of gifts (like defense etc..)
 */

class Gift : public MovingObject
{
public:
  Gift(const sf::Vector2f&, float);
  void moveObject() override;
  bool isDel() const;
  void setDel();

private:
  bool checkTimer();

  float m_floor, m_speed_y = SPEED_GIFT_Y, m_gift_timer = GIFT_TIMER;
  bool m_deleted = false;
};

