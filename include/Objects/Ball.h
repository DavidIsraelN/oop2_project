#pragma once
#include "MovingObject.h"
#include "Factory.h"
#include <memory>

class Ball : public MovingObject
{
public:
  Ball(size_t, float, const sf::Vector2f&);
  void moveObject(const sf::Vector2f&) override;
  bool collidesWith(const Object&) const override;
  bool isDel() const;

private:
  float m_velocity_x = 300.f;
  float m_velocity_y = 2000.f;
  float m_ceiling, m_begin_ceiling;
  bool m_deleted = false, m_active_ceiling = false;
  static bool m_registerit;
};

//bool Ball::m_registerit = Factory::instance().registerType(ObjectType::BALL,
//                                                 [](const sf::Vector2f& pos) -> std::unique_ptr<Object>
//                                                 {
//                                                   return std::make_unique<Ball>(1, pos);
//                                                 }
//                                                           );
