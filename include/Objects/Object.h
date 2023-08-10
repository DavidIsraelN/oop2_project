#pragma once
#include "EnumAndMacros.h"
#include <SFML/Graphics.hpp>

/* ----------------------------------------------------------
 * an abstract class that is responsible for all the object of the game.
 */

class Door;
class Player;
class Ball;
class Wall;
class Weapon;
class LifeGift;
class TimeGift;

class Object
{
public:
  virtual ~Object() = 0 { } // to be abstract
  void draw(sf::RenderWindow&) const;
  virtual bool collidesWith(Object&) const;
  virtual void collide(Object&) { }
  virtual void collide(Door&) { }
  virtual void collide(Player&) { }
  virtual void collide(Ball&) { }
  virtual void collide(Wall&) { }
  virtual void collide(Weapon&) { }
  virtual void collide(LifeGift&) { }
  virtual void collide(TimeGift&) { }
  sf::FloatRect getGlobalBounds() const;

protected:
  sf::Sprite m_sprite;
};
