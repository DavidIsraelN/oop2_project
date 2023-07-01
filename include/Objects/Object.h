#pragma once
#include <SFML/Graphics.hpp>
class Object
{
public:
  virtual ~Object() { }
  void draw(sf::RenderWindow&) const;
protected:
  sf::Sprite m_sprite;
};

