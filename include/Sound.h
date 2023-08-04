#pragma once
#include <SFML/Audio.hpp>
#include "ResourcesManager.h"

/*
 * Singleton - Sound class for all program sounds.
 * Create the Sounds of the program once and play from anywhere in the program.
 */

class Sound
{
public:
  static Sound& Sounds()
  {
    static auto m_sound = Sound();
    return m_sound;
  }

  //-------------------------------------------------------------------
  Sound(const Sound&) = delete;
  void operator=(const Sound&) = delete;

  //-------------------------------------------------------------------
  void Play(SoundIndex type)
  {
    if (m_muted) return;
    m_sounds[size_t(type)].play();
  }

  //-------------------------------------------------------------------
  sf::SoundSource::Status GetStatus(SoundIndex type)
  {
    return m_sounds[size_t(type)].getStatus();
  };

  //-------------------------------------------------------------------
  void Stop(SoundIndex type)
  {
    m_sounds[size_t(type)].stop();
  }

  //-------------------------------------------------------------------
  void Mute()
  {
    m_muted = !m_muted;
    if(!m_muted) return;
    for (auto i = size_t(0); i < SOUND; ++i)
      Stop(SoundIndex(i));
  }

  //-------------------------------------------------------------------
  bool isMute() const { return m_muted;}

private:
  Sound()
  {
    for (auto i = size_t(0); i < SOUND; ++i)
      m_sounds[i].setBuffer(ResourceManager::Resource().getSound(SoundIndex(i)));

    m_sounds[size_t(SoundIndex::START)].setLoop(true);
  }

  //-------------------------------------------------------------------
  sf::Sound m_sounds[SOUND];
  bool m_muted = false;
};