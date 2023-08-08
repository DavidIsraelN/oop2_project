#include "ResourcesManager.h"

//-------------------------------------------------------------------
ResourceManager::ResourceManager()
{
  m_icon.loadFromFile("RedBall.png");


//  if (!m_texture.loadFromFile("Pacman.png"))
//  {
//    throw std::runtime_error("Can't load file");
//  }

  m_texture_resources.loadFromFile(m_texture_name);

  m_static_rect[StaticObjIndex::WALL] = sf::IntRect(23, 128, 128, 128);
  m_static_rect[StaticObjIndex::BALL] = sf::IntRect(410, 142, 121, 121);
  m_static_rect[StaticObjIndex::STAY_PLAYER] = sf::IntRect(802, 40, 39, 68);
  m_static_rect[StaticObjIndex::BULLET] = sf::IntRect(355, 123, 24, 149);
  m_static_rect[StaticObjIndex::DOOR] = sf::IntRect(168, 128, 132, 132);
  m_static_rect[StaticObjIndex::GIFT] = sf::IntRect(766, 169, 60, 69);
  m_static_rect[StaticObjIndex::BOOM] = sf::IntRect(545, 182, 45, 47);

  setPlayerMap();

  for (auto i = size_t(0); i < FILES; ++i)
    m_files[i] = std::fstream(m_files_name[i], 
      TxtIndex(i) == TxtIndex::RECORD ? std::ios_base::in | std::ios_base::out : std::ios_base::in);
  
  for (auto i = size_t(0); i < SOUND; ++i)
    m_sounds[i].loadFromFile(m_sounds_name[i]);
  
  for (auto i = size_t(0); i < FONTS; ++i)
    m_fonts[i].loadFromFile(m_fonts_name[i]);
  
//  for (auto i = size_t(0); i < OBJECTS; ++i)
//    m_objects_texture[i].loadFromFile(m_textures_name[i]);
  
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

sf::IntRect& ResourceManager::getTextureRect(StaticObjIndex type)
{
  return m_static_rect[type];
}

void ResourceManager::setPlayerMap()
{
  const auto size = sf::Vector2i(40, 40);
  const auto initSpace = sf::Vector2i(851, 2);
  const auto middleSpace = sf::Vector2i(0, 10);

//  auto pacman = AnimationData {};
  auto currentStart = initSpace;

  auto nextStart = [&]()
  {
    currentStart += middleSpace;
    currentStart.y += size.y;
    return currentStart;
  };
  m_player_animation[PlayerIndex::WALK];

}


//
////-------------------------------------------------------------------
//sf::Texture& ResourceManager::getObjTexture(ObjIndex type)
//{
//  return m_objects_texture[size_t(type)];
//}

////-------------------------------------------------------------------
//sf::Texture& ResourceManager::getObjTexture(ObjIndex type)
//{
//  return m_objects_texture[size_t(type)];
//}

//-------------------------------------------------------------------
sf::Texture& ResourceManager::getTexture()
{
  return m_texture_resources;
}

//-------------------------------------------------------------------
sf::SoundBuffer& ResourceManager::getSound(SoundIndex type) 
{ 
  return m_sounds[size_t(type)]; 
}

//-------------------------------------------------------------------
std::fstream& ResourceManager::getTxtFile(TxtIndex type) 
{
  return m_files[size_t(type)];
}

//-------------------------------------------------------------------
sf::Texture& ResourceManager::getBackgroundTexture(BackgroundIndex type)
{
  return m_backgrounds_texture[size_t(type)];
}
