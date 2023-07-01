#include "Level.h"
#include "Objects/GunWeapon.h"
#include "TimerManager.h"
#include <algorithm>
#include <vector>
#include <memory>


Level::Level(float win_width, float win_height) : m_win_width(win_width), m_win_height(win_height), m_world_width(win_width*1.5) { }

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
  m_background.setScale(m_world_width / m_background.getGlobalBounds().width, m_win_height / m_background.getGlobalBounds().height);
  buildLevel();
  m_current_board->backToStart();

}

void Level::draw(sf::RenderWindow& window) const
{
  auto viewSize = sf::Vector2f (m_win_width, window.getSize().y);

  auto distance_left = m_player->getGlobalBounds().left;
  auto distance_right = m_world_width - (m_player->getGlobalBounds().left + m_player->getGlobalBounds().width);

  auto ratio = (distance_left <= distance_right) ? (distance_left / distance_right / 2) : (1 - distance_right / distance_left / 2);
  auto calculate_x = ratio * (m_world_width - m_win_width) + m_win_width / 2;
  sf::Vector2f viewPosition(calculate_x, window.getSize().y / 2);
  sf::View view(viewPosition, viewSize);

  window.clear();
  window.setView(view);
  window.draw(m_background);

  for (auto &ball : m_balls)
    ball->draw(window);

  for (auto &bullet : m_bullets)
    bullet->draw(window);

  m_player->draw(window);
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
  m_obj_width = m_world_width / m_current_board->getCols();
  m_obj_height = m_win_height / m_current_board->getRows();

  for (auto i = size_t(0); i < m_current_board->getRows(); ++i)
    for (auto j = size_t(0); j < m_current_board->getCols(); ++j)
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

//  case ObjType::DEMON:
//    m_demons.push_back(std::make_unique<Demon>(position, m_obj_width, m_obj_height)); break;
//
//  case ObjType::WALL:
//    m_walls.push_back(std::make_unique<Wall>(position, m_obj_width, m_obj_height)); break;
//
//  case ObjType::COOKIE:
//    m_erasable_obj[size_t(ObjIndex::COOKIE)].push_back(
//        std::make_unique<Cookie>(position, m_obj_width, m_obj_height));break;
//
//  case ObjType::GIFT:
//    m_erasable_obj[size_t(ObjIndex::GIFT)].push_back(chooseRandomGift(position)); break;
//
//  case ObjType::DOOR:
//    m_erasable_obj[size_t(ObjIndex::DOOR)].push_back(
//        std::make_unique<Door>(position, m_obj_width, m_obj_height)); break;
//
//  case ObjType::KEY:
//    m_erasable_obj[size_t(ObjIndex::KEY)].push_back(std::make_unique<Key>(position, m_obj_width, m_obj_height));
//
//    m_balls.push_back(std::make_unique<Ball>(200, sf::Vector2f(m_world_width / 2, m_win_height / 2)));
//    m_balls.push_back(std::make_unique<Ball>(150, sf::Vector2f(m_world_width / 3, m_win_height / 2)));
//    m_balls.push_back(std::make_unique<Ball>(180, sf::Vector2f(m_world_width / 5, m_win_height / 2)));
//    m_balls.push_back(std::make_unique<Ball>(100, sf::Vector2f(m_world_width / 6, m_win_height / 2)));
//
//
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
