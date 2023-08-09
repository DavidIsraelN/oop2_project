#pragma once
#include "LevelReader.h"
#include "Objects/Ball.h"
#include "Objects/Door.h"
#include "Objects/Gifts/Gift.h"
#include "Objects/Player.h"
#include "Objects/Wall.h"
#include "Objects/Weapon.h"
#include "StatusBar.h"
#include <iostream>

/* ------------------------------------------------------------------
 * This class is responsible for the levels.
 * loads the desired level, contains in vectors all the level objects, 
 * responsible for performing the actions required in the current level
 * according to the existing situation
 */

class Level
{
public:
  Level(float, float);
  void loadLevel(Action, bool);
  void draw(sf::RenderWindow&);
  void movePlayer();
  void createBullet();
  void createGift(sf::Vector2f);
  void moveBullets();
  void moveGifts();
  void moveBalls();
  void erase(bool&);
  void pause();
  void handleCollision();
  void splitBall();
  void updateStatusBar(StatusBar&);
  bool levelOver();
  bool lifeEnd() const;
  size_t getScore() const;
  size_t getLevelNum() const;
  bool isDisqualification() const;
  float getObjHeight() const;

private:
  float getFirstDoor() const;
  void clearLevel(bool);
  void resetLevel();
  void setLevel(Action, bool);
  void openDoor(bool&);
  void buildLevel(bool);
  void addObject(ObjectType, size_t, size_t, bool);
  sf::View currentView();

  std::unique_ptr<LevelReader> m_current_board;
  size_t m_level_num = 0;

  std::unique_ptr<Player> m_player;
  std::vector<std::shared_ptr<Ball>> m_balls, m_original_balls;
  std::vector<std::unique_ptr<Wall>> m_walls;
  std::vector<std::unique_ptr<Door>> m_doors;
  std::vector<std::unique_ptr<Weapon>> m_bullets;
  std::vector<std::unique_ptr<Gift>> m_gifts;
  sf::Sprite m_background, m_boom;

  float m_win_width, m_win_height, m_old_view_x, m_world_width = 0,
    m_obj_height = 0, m_obj_width = 0, m_bullet_time = -1.f, m_boom_timer = BOOM_TIMER;
  bool disqualification = false, m_is_boom = false;
};
