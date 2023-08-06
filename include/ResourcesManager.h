#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <fstream>

/* ------------------------------------------------------------------
 * Singleton - Source class for all program data.
 * Loading the files of the program once - textures, audio, texts, fonts.
 * and receiving the data from anywhere in the program.
 */

//-------------------------------------------------------------------
const size_t OBJECTS = 5;
const size_t FILES = 4;
const size_t SOUND = 4;
const size_t FONTS = 2;
const size_t BACKGROUNDS = 3;

//-------------------------------------------------------------------
enum class ObjIndex
{
  BALL, PLAYER, BULLET, WALL, DOOR,
  LIFE
};

enum class TxtIndex
{
  LEVEL1, LEVEL2, LEVEL3, RECORD
};

enum class BackgroundIndex
{
  BACKGROUND_1, BACKGROUND_2, BACKGROUND_3
};

enum class SoundIndex
{
  SHUT, HIT, DEATH, BACKGROUND /*, LEVEL_RUN, GIFTS */
};

enum class FontIndex
{
  TRY, ARIEL
};

//-------------------------------------------------------------------
class ResourceManager
{
public:
  static ResourceManager& Resource();
  ResourceManager(const ResourceManager&) = delete;
  void operator=(const ResourceManager&) = delete;
  sf::Image& getIcon();
  sf::Font& getFont(FontIndex type);
  sf::Texture& getObjTexture(ObjIndex type);
  sf::SoundBuffer& getSound(SoundIndex type);
  std::ifstream& getTxtFile(TxtIndex type);
  sf::Texture& getBackgroundTexture(BackgroundIndex type);

private:
  ResourceManager();

  std::string m_textures_name[OBJECTS] = 
  { "Ball.png", "Player.png","Bullet.png", "Wall.jpg", "Door.jpg"};
  sf::Texture m_objects_texture[OBJECTS];

  std::string m_backgrounds_name[BACKGROUNDS] = 
  {"Background_1.jpg","Background_2.jpg","Background_3.jpg"};
  sf::Texture m_backgrounds_texture[BACKGROUNDS];

  std::string m_sounds_name[SOUND] = 
  { "gun_shot.wav", "hit.wav", "dead.wav", "background.wav" };
  sf::SoundBuffer m_sounds[SOUND];

  std::string m_files_name[FILES] = 
  { "Level_1.txt", "Level_2.txt", "Level_3.txt", "Record.txt"};
  std::ifstream m_files[FILES];

  std::string m_fonts_name[FONTS] = 
  { "balloudefont.otf", "Arial.ttf"};
  sf::Font m_fonts[FONTS];

  sf::Image m_icon;
};
