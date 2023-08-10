#include "Objects/Gifts/TimeGift.h"
#include "Objects/Player.h"

//-------------------------------------------------------------------
TimeGift::TimeGift(const sf::Vector2f& position, float floor) 
  : Gift(position, floor) { }

//-------------------------------------------------------------------
void TimeGift::collide(Player& player)
{
  player.collide(*this);
  setDel();
}
