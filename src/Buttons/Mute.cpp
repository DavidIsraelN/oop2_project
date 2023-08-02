#include "Buttons/Mute.h"
#include "EnumClassAction.h"

//----------------------------------------------------------
Mute::Mute(const sf::Vector2f& size, const sf::Vector2f& position, Action back_to)
  : Button(size, position, "Mute", back_to)
{ }

//-------------------------------------------------------------------
Action Mute::action(sf::RenderWindow& window)
{
  //Sound::Sounds().Mute();
  //m_text.setString(Sound::Sounds().isMute() ? "Unmute" : "Mute");
  return getAction();
}
