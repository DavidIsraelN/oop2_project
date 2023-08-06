#include "Sound.h"

//-------------------------------------------------------------------
Sound::Sound()
{
  for (auto i = size_t(0); i < SOUND; ++i)
    m_sounds[i].setBuffer(ResourceManager::Resource().getSound(SoundIndex(i)));

  m_sounds[size_t(SoundIndex::BACKGROUND)].setLoop(true);
}

//-------------------------------------------------------------------
Sound& Sound::Sounds()
{
  static auto m_sound = Sound();
  return m_sound;
}

//-------------------------------------------------------------------
void Sound::Play(SoundIndex type)
{
  if (m_muted) return;
  m_sounds[size_t(type)].play();
}

//-------------------------------------------------------------------
sf::SoundSource::Status Sound::GetStatus(SoundIndex type)
{
  return m_sounds[size_t(type)].getStatus();
};

//-------------------------------------------------------------------
void Sound::Stop(SoundIndex type)
{
  m_sounds[size_t(type)].stop();
}

//-------------------------------------------------------------------
void Sound::Mute()
{
  m_muted = !m_muted;
  if (!m_muted) return;
  for (auto i = size_t(0); i < SOUND; ++i)
    Stop(SoundIndex(i));
}

//-------------------------------------------------------------------
bool Sound::isMute() const
{
  return m_muted; 
}
