#include "ResourcesManager.h"

//-------------------------------------------------------------------
ResourceManager::ResourceManager()
{
  m_icon.loadFromFile("RedBall.png");
  
  for (auto i = size_t(0); i < FILES; ++i)
    m_files[i] = std::ifstream(m_files_name[i]);
  
  for (auto i = size_t(0); i < SOUND; ++i)
    m_sounds[i].loadFromFile(m_sounds_name[i]);
  
  for (auto i = size_t(0); i < FONTS; ++i)
    m_fonts[i].loadFromFile(m_fonts_name[i]);
  
  for (auto i = size_t(0); i < OBJECTS; ++i)
    m_objects_texture[i].loadFromFile(m_textures_name[i]);
  
  for (auto i = size_t(0); i < BACKGROUNDS; ++i)
    m_backgrounds_texture[i].loadFromFile(m_backgrounds_name[i]);
}

//-------------------------------------------------------------------
ResourceManager& ResourceManager::Resource()
{
  static auto m_resource = ResourceManager();
  return m_resource;
}

//-------------------------------------------------------------------
sf::Image& ResourceManager::getIcon()
{ 
  return m_icon; 
}

//-------------------------------------------------------------------
sf::Font& ResourceManager::getFont(FontIndex type)
{ 
  return m_fonts[size_t(type)]; 
}

//-------------------------------------------------------------------
sf::Texture& ResourceManager::getObjTexture(ObjIndex type) 
{ 
  return m_objects_texture[size_t(type)]; 
}

//-------------------------------------------------------------------
sf::SoundBuffer& ResourceManager::getSound(SoundIndex type) 
{ 
  return m_sounds[size_t(type)]; 
}

//-------------------------------------------------------------------
std::ifstream& ResourceManager::getTxtFile(TxtIndex type) 
{
  return m_files[size_t(type)];
}

//-------------------------------------------------------------------
sf::Texture& ResourceManager::getBackgroundTexture(BackgroundIndex type)
{
  return m_backgrounds_texture[size_t(type)];
}
