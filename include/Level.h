#pragma once
#include "EnumClassAction.h"
#include "LevelReader.h"
#include "Objects/Ball.h"
#include "Objects/Door.h"
#include "Objects/Gifts/Gift.h"
#include "Objects/Player.h"
#include "Objects/Wall.h"
#include "Objects/Weapon.h"
#include <SFML/Graphics.hpp>
#include <iostream>

class Level
{
public:
  Level(float, float, float);
  void loadLevel(Action);
  void draw(sf::RenderWindow&) const;
  void movePlayer();
  void createBullet();
  void moveBullets();
  void moveBalls();
  void erase();
  void pause();
  void handleCollision();
  void splitBall();

private:
  float getFirstDoor() const;
  void clearLevel();
  void setLevel(Action);
  void chooseLevel();
  void openDoor();
  void buildLevel();
  void addObject(ObjectType, size_t, size_t);

  std::unique_ptr<LevelReader> m_current_board;
  size_t m_win_width, m_win_height, m_info_height, m_world_width;
  std::unique_ptr<Player> m_player;
  std::vector<std::unique_ptr<Ball>> m_balls;
  std::vector<std::unique_ptr<Weapon>> m_bullets;
  std::vector<std::unique_ptr<Wall>> m_walls;
  std::vector<std::unique_ptr<Door>> m_doors;
  std::vector<std::unique_ptr<Gift>> m_gifts;
  sf::Sprite m_background;
  float m_obj_width = 0, m_obj_height = 0;
};

