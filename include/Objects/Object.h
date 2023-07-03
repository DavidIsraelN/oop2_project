#pragma once
#include <SFML/Graphics.hpp>
class Object
{
public:
  virtual ~Object() { }
  void draw(sf::RenderWindow&) const;
  virtual bool collidesWith(const Object&) const;

protected:
  sf::Sprite m_sprite;
};

