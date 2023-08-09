#include "ResourcesManager.h"
#include <exception>

//-------------------------------------------------------------------
ResourceManager::ResourceManager()
{
  if (!m_icon.loadFromFile(m_icon_name))
    throw std::runtime_error("Can't load icon file");

  if (!m_font.loadFromFile(m_font_name))
    throw std::runtime_error("Can't load font file");

  for (auto i = int(0); i < int(TextureIndex::MAX); ++i)
    if (!m_texture_resources[TextureIndex(i)].loadFromFile(m_texture_name[i]))
      throw std::runtime_error("Can't load texture file");

  for (auto i = int(0); i < int(TxtIndex::MAX); ++i)
    if(!(m_files[TxtIndex(i)] = std::fstream(m_files_name[i], TxtIndex(i) == TxtIndex::RECORD ?
      std::ios_base::in | std::ios_base::out : std::ios_base::in)))
      throw std::runtime_error("Can't load txt file");
  
  for (auto i = int(0); i < int(SoundIndex::MAX); ++i)
    if (!m_sounds[SoundIndex(i)].loadFromFile(m_sounds_name[i]))
      throw std::runtime_error("Can't load sound file");
  
  for (auto i = int(0); i < int(BackgroundIndex::MAX); ++i)
    if (!m_backgrounds_texture[BackgroundIndex(i)].loadFromFile(m_backgrounds_name[i]))
      throw std::runtime_error("Can't load background file");

  setStaticMap();
  setPlayerAnimation();
}

//-------------------------------------------------------------------
ResourceManager& ResourceManager::Resource()
{
  static auto m_resource = ResourceManager();
  return m_resource;
}

//-------------------------------------------------------------------
void ResourceManager::setPlayerAnimation()
{
  m_player_animation.emplace_back(27, 41, 31, 67);
  m_player_animation.emplace_back(135, 41, 32, 67);
  m_player_animation.emplace_back(244, 42, 35, 66);
  m_player_animation.emplace_back(356, 41, 35, 67);
  m_player_animation.emplace_back(468, 40, 34, 68);
  m_player_animation.emplace_back(579, 42, 35, 66);
  m_player_animation.emplace_back(691, 42, 34, 66);
}

//-------------------------------------------------------------------
void ResourceManager::setStaticMap()
{
  m_static_rect[StaticObjIndex::WALL] = sf::IntRect(23, 128, 128, 128);
  m_static_rect[StaticObjIndex::BALL] = sf::IntRect(410, 142, 121, 121);
  m_static_rect[StaticObjIndex::STAND_PLAYER] = sf::IntRect(802, 40, 39, 68);
  m_static_rect[StaticObjIndex::SHUT_PLAYER] = sf::IntRect(918, 8, 25, 100);
  m_static_rect[StaticObjIndex::BULLET] = sf::IntRect(355, 123, 24, 149);
  m_static_rect[StaticObjIndex::DOOR] = sf::IntRect(168, 128, 132, 132);
  m_static_rect[StaticObjIndex::GIFT] = sf::IntRect(766, 169, 60, 69);
  m_static_rect[StaticObjIndex::BOOM] = sf::IntRect(545, 182, 45, 47);
}

//-------------------------------------------------------------------
sf::Image& ResourceManager::getIcon()
{ 
  return m_icon; 
}

//-------------------------------------------------------------------
sf::Font& ResourceManager::getFont()
{ 
  return m_font;
}

//-------------------------------------------------------------------
sf::Texture& ResourceManager::getTexture(TextureIndex type)
{
  return m_texture_resources[type];
}

//-------------------------------------------------------------------
sf::SoundBuffer& ResourceManager::getSound(SoundIndex type) 
{ 
  return m_sounds[type]; 
}

//-------------------------------------------------------------------
std::fstream& ResourceManager::getTxtFile(TxtIndex type) 
{
  return m_files[type];
}

//-------------------------------------------------------------------
sf::Texture& ResourceManager::getBackgroundTexture(BackgroundIndex type)
{
  return m_backgrounds_texture[type];
}

//-------------------------------------------------------------------
sf::IntRect& ResourceManager::getTextureRect(StaticObjIndex type)
{
  return m_static_rect[type];
}

//-------------------------------------------------------------------
sf::IntRect& ResourceManager::getWalkingTextureRect(size_t index)
{
  return m_player_animation[index % m_player_animation.size()];
}
