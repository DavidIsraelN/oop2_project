#pragma once
#include "ResourcesManager.h"

/* ----------------------------------------------------------
 * Class that is responsible for reading the correct file of the level,
 * and extracting the data from it.
 */

//------------------------
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

//------------------------
class LevelReader
{
public:
  LevelReader(std::fstream&);
  void setDimensions();
  char getChar() const;
  size_t getRows() const;
  size_t getWindowCols() const;
  size_t getWorldCols() const;
  void backToStart();
  //float getObjHeight() const;
  //float getObjWidth() const;
  //float getWorldWidth() const;

private:
  std::fstream& m_level_board;
  size_t m_rows = 0, m_window_cols = 0, m_world_cols = 0;
  //float m_win_width, m_win_height, m_obj_width, m_obj_height, m_world_width;
};
