#include "Objects/Gifts/LifeGift.h"
#include "Objects/Player.h"

//-------------------------------------------------------------------
LifeGift::LifeGift(const sf::Vector2f& position, float floor) 
  : Gift(position, floor) { }

//-------------------------------------------------------------------
void LifeGift::collide(Player& player)
{
  player.collide(*this);
  setDel();
}
