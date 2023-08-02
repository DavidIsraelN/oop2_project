#include "LevelReader.h"

//-------------------------------------------------------------------
LevelReader::LevelReader(std::ifstream& board) : m_level_board(board) { }

//-------------------------------------------------------------------
void LevelReader::setDimensions()
{
  std::string line;
  std::getline(m_level_board, line);
  auto size = std::istringstream(line);
  size >> m_rows >> m_window_cols >> m_world_cols;
}

//-------------------------------------------------------------------
char LevelReader::getChar() const
{
  char c;
  do {
    c = m_level_board.get();
  } while (c == '\n');
  return c;
}

//-------------------------------------------------------------------
size_t LevelReader::getRows() const 
{
  return m_rows; 
}

//-------------------------------------------------------------------
size_t LevelReader::getWindowCols() const
{
  return m_window_cols;
}

//-------------------------------------------------------------------
size_t LevelReader::getWorldCols() const
{
  return m_world_cols;
}
 
//-------------------------------------------------------------------
void LevelReader::backToStart()
{
  m_level_board.seekg(0, m_level_board.beg);
}

////-------------------------------------------------------------------
//float LevelReader::getObjWidth() const
//{
//  return m_obj_width;
//}
//
////-------------------------------------------------------------------
//float LevelReader::getObjHeight() const
//{ 
//  return m_obj_height;
//}
//
////-------------------------------------------------------------------
//float LevelReader::getWorldWidth() const
//{
//  return m_world_width;
//}
