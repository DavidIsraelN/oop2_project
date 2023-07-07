#pragma once
#include <SFML/Graphics.hpp>

class Door;
class Player;
class Ball;
class Wall;
class Weapon;

class Object
{
public:
  virtual ~Object() { }
  void draw(sf::RenderWindow&) const;
  virtual bool collidesWith(Object&) const;
  virtual void collide(Object&) { }
  virtual void collide(Door&) { }
  virtual void collide(Player&) { }
  virtual void collide(Ball&) { }
  virtual void collide(Wall&) { }
  virtual void collide(Weapon&) { }
  sf::FloatRect getGlobalBounds() const;

protected:
  sf::Sprite m_sprite;
};

