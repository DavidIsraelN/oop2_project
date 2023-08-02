#pragma once
#include <sstream>
#include "ResourcesManager.h"
#include "Objects/Ball.h"
#include "Objects/Door.h"
#include "Objects/Player.h"
#include "Objects/Wall.h"

/* ----------------------------------------------------------
 * Class that is responsible for reading the correct file of the level,
 * and extracting the data from it.
 */

//-------------------------------------------------------------------
enum class ObjectType
{
  PLAYER = 'P',
  WALL = '#',
  DOOR = 'D',
  BALL_1 = '1',
  BALL_2 = '2',
  BALL_3 = '3',
  BALL_4 = '4',
  SPACE = ' '
};

//-------------------------------------------------------------------
class LevelReader
{
public:
  LevelReader(std::ifstream&, float, float);
  void setDimensions();
  char getChar() const;
  void getLevel(std::shared_ptr<Player>&, 
                std::shared_ptr<std::vector<std::shared_ptr<Ball>>>,
                std::shared_ptr<std::vector<std::shared_ptr<Wall>>> walls, 
                std::shared_ptr<std::vector<std::shared_ptr<Door>>> doors) const;
  void getOriginalBalls(std::shared_ptr<std::vector<std::shared_ptr<Ball>>>) const;
  float getObjHeight() const;
  float getObjWidth() const;
  float getWorldWidth() const;
  void clear();

private:
  void buildLevel();
  void readLevel();
  void addObject(ObjectType, size_t, size_t);

  std::ifstream& m_level_board;
  size_t m_rows = 0, m_window_cols = 0, m_world_cols = 0;
  float m_win_width, m_win_height, m_obj_width, m_obj_height, m_world_width;

  std::shared_ptr<Player> m_player;
  std::shared_ptr<std::vector<std::shared_ptr<Ball>>> m_balls;
  std::shared_ptr<std::vector<std::shared_ptr<Wall>>> m_walls;
  std::shared_ptr<std::vector<std::shared_ptr<Door>>> m_doors;
};
