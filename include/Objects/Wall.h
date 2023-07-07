#pragma once
#include "ResourcesManager.h"
#include "StaticObject.h"

class Wall : public StaticObject
{
public:
  Wall(const sf::Vector2f& position, float width, float height);
  void collide(Ball&) override;
  void collide(Weapon&) override;

  //  void collide(Pacman& pacman) override { }

private:

};
