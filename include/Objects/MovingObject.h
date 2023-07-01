#pragma once
#include "Object.h"
#include "ResourcesManager.h"

class MovingObject : public Object
{
public:
  virtual void moveObject(const sf::Vector2f& direction) = 0;
private:

};

