#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <fstream>
#include <unordered_map>

/* ------------------------------------------------------------------
 * Singleton - Source class for all program data.
 * Loading the files of the program once - textures, audio, texts, fonts.
 * and receiving the data from anywhere in the program.
 */

//-------------------------------------------------------------------
enum class StaticObjIndex
{
  BALL, STAND_PLAYER, SHUT_PLAYER, BULLET, WALL, DOOR, GIFT, BOOM
};

enum class TxtIndex
{
  LEVEL1, LEVEL2, LEVEL3, RECORD, MAX
};

enum class TextureIndex
{
  SPRITE_SEET, HELP, MAX
};

enum class BackgroundIndex
{
  BACKGROUND_1, BACKGROUND_2, BACKGROUND_3, MAX
};

enum class SoundIndex
{
  SHUT, HIT, DEATH, BACKGROUND, GIFT /*, LEVEL_RUN */, MAX
};

//-------------------------------------------------------------------
class ResourceManager
{
public:
  static ResourceManager& Resource();
  ResourceManager(const ResourceManager&) = delete;
  void operator=(const ResourceManager&) = delete;
  sf::Image& getIcon();
  sf::Font& getFont();
  sf::Texture& getTexture(TextureIndex);
  sf::IntRect& getTextureRect(StaticObjIndex);
  sf::IntRect& getWalkingTextureRect(size_t);
  sf::SoundBuffer& getSound(SoundIndex);
  std::fstream& getTxtFile(TxtIndex);
  sf::Texture& getBackgroundTexture(BackgroundIndex);

private:
  ResourceManager();
  void setStaticMap();
  void setPlayerAnimation();

  std::string m_icon_name = "RedBall.png";
  sf::Image m_icon;

  std::string m_font_name = "balloudefont.otf";
  sf::Font m_font;

  std::string m_texture_name[size_t(TextureIndex::MAX)] = 
  { "SpriteSheet.png", "Help.jpeg" };
  std::unordered_map<TextureIndex, sf::Texture> m_texture_resources;

  std::string m_files_name[size_t(TxtIndex::MAX)] =
  { "Level_1.txt", "Level_2.txt", "Level_3.txt", "Record.txt"};
  std::unordered_map<TxtIndex, std::fstream> m_files;

  std::string m_sounds_name[size_t(SoundIndex::MAX)] =
  { "gun_shot.wav", "hit.wav", "dead.wav", "background.wav", "gift.wav" };
  std::unordered_map<SoundIndex, sf::SoundBuffer> m_sounds;

  std::string m_backgrounds_name[size_t(BackgroundIndex::MAX)] =
  {"Background_1.jpg","Background_2.jpg","Background_3.jpg"};
  std::unordered_map<BackgroundIndex, sf::Texture> m_backgrounds_texture;

  std::unordered_map<StaticObjIndex, sf::IntRect> m_static_rect;
  std::vector<sf::IntRect> m_player_animation;
};
