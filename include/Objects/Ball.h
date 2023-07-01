#pragma once
#include "MovingObject.h"
#include "Factory.h"
#include <memory>

class Ball : public MovingObject
{
public:
  Ball(size_t, const sf::Vector2f&);
  void moveObject(const sf::Vector2f&) override;
  bool isDel() const;

private:
  float m_velocity_X = 300.f;
  float m_velocity_Y = -2000.f;
  float m_jump_height;
  bool m_need_to_delete = false;
  static bool m_registerit;
};

//bool Ball::m_registerit = Factory::instance().registerType(ObjectType::BALL,
//                                                 [](const sf::Vector2f& pos) -> std::unique_ptr<Object>
//                                                 {
//                                                   return std::make_unique<Ball>(1, pos);
//                                                 }
//                                                           );
