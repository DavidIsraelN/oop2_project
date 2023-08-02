#include "LevelReader.h"

//-------------------------------------------------------------------
LevelReader::LevelReader(std::ifstream& board, float win_width, float win_height)
  : m_level_board(board), m_win_width(win_width), m_win_height(win_height)
{
  clear();
  buildLevel();
}

//-------------------------------------------------------------------
void LevelReader::buildLevel()
{
  setDimensions();
  readLevel();
}

//-------------------------------------------------------------------
void LevelReader::setDimensions()
{
  std::string line;
  std::getline(m_level_board, line);
  auto size = std::istringstream(line);
  size >> m_rows >> m_window_cols >> m_world_cols;
}

//-------------------------------------------------------------------
void LevelReader::readLevel()
{
  m_obj_height = float(m_win_height) / m_rows;
  m_obj_width = float(m_win_width) / m_window_cols;
  m_world_width = m_obj_width * m_world_cols;

  for (auto i = size_t(0); i < m_rows; ++i)
    for (auto j = size_t(0); j < m_world_cols; ++j)
    {
      char c = getChar();
      if (c == char(ObjectType::SPACE)) continue;
      addObject(ObjectType(c), i, j);
    }
}

//-------------------------------------------------------------------
void LevelReader::addObject(ObjectType type, size_t i, size_t j)
{
  auto x_pos = m_obj_width * j + m_obj_width / 2;
  auto y_pos = m_obj_height * i + m_obj_height / 2;
  auto position = sf::Vector2f({ x_pos, y_pos });

  switch (type)
  {
  case ObjectType::PLAYER:
    m_player = std::make_shared<Player>(position, m_obj_width, m_obj_height); break;

  case ObjectType::BALL_1:
  case ObjectType::BALL_2:
  case ObjectType::BALL_3:
  case ObjectType::BALL_4:
    m_balls->push_back(std::make_shared<Ball>((size_t(type) - '0'), m_obj_width, position,
                                              m_win_height - m_obj_height, 1)); break;

  case ObjectType::WALL:
    m_walls->push_back(std::make_shared<Wall>(position, m_obj_width, m_obj_height)); break;

  case ObjectType::DOOR:
    m_doors->push_back(std::make_shared<Door>(position, m_obj_width, m_obj_height)); break;

  default:
    throw std::invalid_argument(/*std::to_string(char(type)) +*/ "invalid character\n");
  }
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
void LevelReader::getLevel(std::shared_ptr<Player>& player,
                           std::shared_ptr<std::vector<std::shared_ptr<Ball>>> balls,
                           std::shared_ptr<std::vector<std::shared_ptr<Wall>>> walls,
                           std::shared_ptr<std::vector<std::shared_ptr<Door>>> doors) const
{
  player.reset(m_player.get());
  balls = m_balls;
  walls = m_walls;
  doors = m_doors;
}

//-------------------------------------------------------------------
void LevelReader::getOriginalBalls(std::shared_ptr<std::vector<std::shared_ptr<Ball>>> balls) const
{
  balls = m_balls;
}

//-------------------------------------------------------------------
void LevelReader::clear()
{
  m_player.reset();
  m_balls->clear();
  m_doors->clear();
  m_walls->clear();
}

//-------------------------------------------------------------------
float LevelReader::getObjWidth() const
{
  return m_obj_width;
}

//-------------------------------------------------------------------
float LevelReader::getObjHeight() const
{ 
  return m_obj_height;
}

//-------------------------------------------------------------------
float LevelReader::getWorldWidth() const
{
  return m_world_width;
}

////-------------------------------------------------------------------
//void LevelReader::backToStart()
//{
//  m_level_board.seekg(0, m_level_board.beg);
//}