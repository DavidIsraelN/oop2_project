#pragma once
#include "ResourcesManager.h"
#include "StaticObject.h"

class Door : public StaticObject
{
public:
  Door(const sf::Vector2f&, float, float);
  void collide(Ball&) override;


private:

};

