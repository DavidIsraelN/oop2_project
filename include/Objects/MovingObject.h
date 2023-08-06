#pragma once
#include "Object.h"
#include "ResourcesManager.h"

/* ----------------------------------------------------------
 * an abstract class for all moving objects of the game 
 * (inherited from Object class).
 */

class MovingObject : public Object
{
public:
  virtual void moveObject() = 0;

};
