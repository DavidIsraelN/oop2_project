#pragma once
#include <SFML/Audio.hpp>
#include "ResourcesManager.h"

/* ------------------------------------------------------------------
 * Singleton - Sound class for all program sounds.
 * Create the Sounds of the program once and play from anywhere in the program.
 */

class Sound
{
public:
  static Sound& Sounds();
  Sound(const Sound&) = delete;
  void operator=(const Sound&) = delete;
  void Play(SoundIndex type);
  sf::SoundSource::Status GetStatus(SoundIndex type);
  void Stop(SoundIndex type);
  void Mute();
  bool isMute() const;

private:
  Sound();

  sf::Sound m_sounds[SOUND];
  bool m_muted = false;
};
