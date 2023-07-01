#pragma once
#include <sstream>
#include "ResourcesManager.h"
/*
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
  LevelReader(std::ifstream& board) : m_level_board(board) { }

  //-------------------------------------------------------------------
  void setDimensions()
  {
    std::string line;
    std::getline(m_level_board, line);
    auto size = std::istringstream(line);
    size >> m_level_rows >> m_level_cols;
  }

  //-------------------------------------------------------------------
  char getChar() const
  {
    char c;
    do {
      c = m_level_board.get();
    } while (c == '\n');
    return c;
  }

  //-------------------------------------------------------------------
  void backToStart()
  {
    m_level_board.seekg(0, m_level_board.beg);
  }

  //-------------------------------------------------------------------
  size_t getRows() const { return m_level_rows; }
  size_t getCols() const { return m_level_cols; }

private:
  std::ifstream& m_level_board;
  size_t m_level_rows = 0, m_level_cols = 0;
};
