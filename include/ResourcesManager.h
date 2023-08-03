#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <fstream>

/*
 * Singleton - Source class for all program data.
 * Loading the files of the program once - textures, audio, texts, fonts.
 * and receiving the data from anywhere in the program.
 */

//-------------------------------------------------------------------
const size_t OBJECTS = 5;
const size_t FILES = 4;
//const size_t SOUND = 7;
const size_t FONTS = 2;
const size_t BACKGROUNDS = 3;

//-------------------------------------------------------------------
enum class ObjIndex
{
  BALL, PLAYER, BULLET,  WALL, DOOR,
  LIFE, PACMAN_OPEN, PACMAN_CLOSE
};

enum class TxtIndex
{
  LEVEL1, LEVEL2, LEVEL3, RECORD
};

enum class BackgroundIndex
{
  BACKGROUND_1, BACKGROUND_2, BACKGROUND_3
};
//
//enum class SoundIndex
//{
//  START, LEVEL_RUN, COOKIE, GIFTS, S_PACMAN, DEATH, GHOST
//};

enum class FontIndex
{
  TRY, ARIEL
};

//-------------------------------------------------------------------
class ResourceManager
{
public:
  static ResourceManager& Resource()
  {
    static auto m_resource = ResourceManager();
    return m_resource;
  }

  //-------------------------------------------------------------------
  ResourceManager(const ResourceManager&) = delete;
  void operator=(const ResourceManager&) = delete;

  //-------------------------------------------------------------------
  sf::Image&       getIcon()                                  { return m_icon; }
  sf::Font&        getFont(FontIndex type)                    { return m_fonts[size_t(type)]; }
  sf::Texture&     getObjTexture(ObjIndex type)               { return m_objects_texture[size_t(type)]; }
  //sf::SoundBuffer& getSound(SoundIndex type)                  { return m_sounds[size_t(type)]; }
  std::ifstream&   getTxtFile(TxtIndex type)                  { return m_files[size_t(type)]; }
  sf::Texture&     getBackgroundTexture(BackgroundIndex type) { return m_backgrounds_texture[size_t(type)]; }

private:
  ResourceManager()
  {
//    m_icon.loadFromFile("pacman_open.png");

    for (auto i = size_t(0); i < FILES; ++i)
      m_files[i] = std::ifstream(m_files_name[i]);

//    for (auto i = size_t(0); i < SOUND; ++i)
//      m_sounds[i].loadFromFile(m_sounds_name[i]);
//
    for (auto i = size_t(0); i < FONTS; ++i)
      m_fonts[i].loadFromFile(m_fonts_name[i]);

    for (auto i = size_t(0); i < OBJECTS; ++i)
      m_objects_texture[i].loadFromFile(m_textures_name[i]);

    for (auto i = size_t(0); i < BACKGROUNDS; ++i)
      m_backgrounds_texture[i].loadFromFile(m_backgrounds_name[i]);

//    m_fonts[0].loadFromFile("Arial.ttf");
//    m_files[0] = std::ifstream(m_files_name[0]);
  }

  //-------------------------------------------------------------------
  std::string m_textures_name[OBJECTS] =
      { "Ball.png", "Player.png","Bullet.png", "Wall.jpg", "Door.jpg"};
  sf::Texture m_objects_texture[OBJECTS];
  std::string m_backgrounds_name[BACKGROUNDS] = {"Background_1.jpg","Background_2.jpg","Background_3.jpg"};
  sf::Texture m_backgrounds_texture[BACKGROUNDS];

  //std::string m_sounds_name[SOUND] =
  //    { "intermission.wav", "game_start.wav", "credit.wav", "eat_fruit.wav" ,
  //     "retreating.wav", "death_1.wav", "eat_ghost.wav" };
  //sf::SoundBuffer m_sounds[SOUND];

  std::string m_files_name[FILES] = { "Level_1.txt", "Level_2.txt", "Level_3.txt", "Record.txt"};
  std::ifstream m_files[FILES];

  std::string m_fonts_name[FONTS] = { "balloudefont.regular.otf" /*"Vanderick.otf"*/, "Arial.ttf"};
  sf::Font m_fonts[FONTS];

  sf::Image m_icon;
};
