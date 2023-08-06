#include "Buttons/Mute.h"
#include "Sound.h"
#include "EnumClassAction.h"

//----------------------------------------------------------
Mute::Mute(const sf::Vector2f& size, const sf::Vector2f& position, Action back_to)
  : Button(size, position, "MUTE", back_to)
{ }

//-------------------------------------------------------------------
Action Mute::action(sf::RenderWindow& window)
{
  Sound::Sounds().Mute();
  m_text.setStyle(Sound::Sounds().isMute() ? sf::Text::StrikeThrough : sf::Text::Regular);
  if(!Sound::Sounds().isMute()) Sound::Sounds().Play(SoundIndex::BACKGROUND);
  return getAction();
}
