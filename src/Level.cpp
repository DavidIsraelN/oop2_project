#include "Level.h"
#include "Objects/GunWeapon.h"
#include "TimerManager.h"
#include <algorithm>
#include <memory>
#include <vector>

Level::Level(float win_width, float win_height, float info_height) : m_win_width(win_width), m_win_height(win_height), m_info_height(info_height) { }

void Level::loadLevel(Action level)
{
  clearLevel();
  setLevel(level);
}

void Level::setLevel(Action level)
{
  m_current_board = std::make_unique<LevelReader>(ResourceManager::Resource().getTxtFile(TxtIndex(level)));
  m_current_board->setDimensions();
  m_background = sf::Sprite(ResourceManager::Resource().getBackgroundTexture(BackgroundIndex(level)));
  buildLevel();
  m_current_board->backToStart();

}

void Level::draw(sf::RenderWindow& window) const
{
//  auto viewSize = sf::Vector2f (m_win_width, m_win_height + m_info_height);
//
//  auto distance_left = m_player->getGlobalBounds().left;
//  auto distance_right = m_world_width - (m_player->getGlobalBounds().left + m_player->getGlobalBounds().width);
//
//  auto ratio = (distance_left <= distance_right) ? (distance_left / distance_right / 2) : (1 - distance_right / distance_left / 2);
//  auto calculate_x = ratio * (m_world_width - m_win_width) + m_win_width / 2;
//  sf::Vector2f viewPosition(calculate_x, (m_win_height + m_info_height) / 2);
//
//
    auto viewSize = sf::Vector2f (m_win_width, m_win_height + m_info_height);
    float viewCenterX;
    if (m_player->getGlobalBounds().left + m_player->getGlobalBounds().width / 2 - m_win_width / 2.0f < 0.0f)
      viewCenterX = m_win_width / 2.0f;
    else if (m_player->getGlobalBounds().left + m_player->getGlobalBounds().width / 2 + m_win_width / 2.0f > m_world_width)
      viewCenterX = m_world_width - m_win_width / 2.0f;
    else
      viewCenterX = m_player->getGlobalBounds().left + m_player->getGlobalBounds().width / 2;
          //    view.setCenter(viewCenterX, view.getCenter().y);

    sf::Vector2f viewPosition(viewCenterX, (m_win_height + m_info_height) / 2);

  sf::View view(viewPosition, viewSize);

  window.clear();
  window.setView(view);
  window.draw(m_background);

  for (auto &ball : m_balls)
    ball->draw(window);

  for (auto &bullet : m_bullets)
    bullet->draw(window);

  for (auto &wall : m_walls)
    wall->draw(window);

  for (auto &door : m_doors)
    door->draw(window);

  m_player->draw(window);

  window.setView(window.getDefaultView());
}

void Level::clearLevel()
{
  m_balls.clear();
  m_bullets.clear();
  TimerManager::Timer().resetClock();
}

//-------------------------------------------------------------------
void Level::buildLevel()
{
  m_obj_height = float(m_win_height) / m_current_board->getRows();
  m_obj_width = float(m_win_width) / m_current_board->getWindowCols();
  m_world_width = m_obj_width * m_current_board->getWorldCols();
  m_background.setScale(m_world_width / m_background.getGlobalBounds().width, m_win_height / m_background.getGlobalBounds().height);

  for (auto i = size_t(0); i < m_current_board->getRows(); ++i)
    for (auto j = size_t(0); j < m_current_board->getWorldCols(); ++j)
    {
      char c = m_current_board->getChar();
      if (c == char(ObjectType::SPACE)) { continue; };
      addObject(ObjectType(c), i, j);
    }
}

//-------------------------------------------------------------------
void Level::addObject(ObjectType type, size_t i, size_t j)
{
  auto x_pos = m_obj_width * j + m_obj_width / 2;
  auto y_pos = m_obj_height * i + m_obj_height / 2;
  auto position = sf::Vector2f({ x_pos, y_pos });

  switch (type)
  {
  case ObjectType::PLAYER:
    m_player = std::make_unique<Player>(position, m_obj_width, m_obj_height); break;

  case ObjectType::BALL_1:
  case ObjectType::BALL_2:
  case ObjectType::BALL_3:
  case ObjectType::BALL_4:
    m_balls.push_back(std::make_unique<Ball>((size_t(type) - '0'), m_obj_width, position)); break;

  case ObjectType::WALL:
    m_walls.push_back(std::make_unique<Wall>(position, m_obj_width, m_obj_height)); break;

  case ObjectType::DOOR:
    m_doors.push_back(std::make_unique<Door>(position, m_obj_width, m_obj_height)); break;
  }
}

void Level::createBullet()
{
  auto middle_player_position = sf::Vector2f(m_player->getGlobalBounds().left + m_player->getGlobalBounds().width / 2,
                                                     m_player->getGlobalBounds().top + m_player->getGlobalBounds().height / 2);
  m_bullets.push_back(std::make_unique<GunWeapon>(50, middle_player_position));
}

void Level::movePlayer()
{
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    m_player->setDirection(-1);
  else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    m_player->setDirection(1);
  else return;

  m_player->moveObject(sf::Vector2f(m_world_width, m_win_height));
}

void Level::moveBalls()
{
  for (auto &ball : m_balls)
    ball->moveObject(sf::Vector2f(m_world_width, m_win_height));
}

void Level::moveBullets()
{
  for (auto &bullet : m_bullets)
    bullet->moveObject(sf::Vector2f(m_world_width, m_win_height));
}

void Level::erase()
{
  std::erase_if(m_bullets, [](const auto &bullet) {return bullet->isDel(); });
}

void Level::pause()
{
  TimerManager::Timer().startPause();
}

void Level::handleCollision() const
{
  for (auto &wall : m_walls)
    if (wall)
}
