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
  auto viewSize = sf::Vector2f (m_win_width, m_win_height + m_info_height);
  float viewCenterX;
  if (m_player->getGlobalBounds().left + m_player->getGlobalBounds().width / 2 - m_win_width / 2.0f < 0.0f)
    viewCenterX = m_win_width / 2.0f;
  else if (m_player->getGlobalBounds().left + m_player->getGlobalBounds().width / 2 + m_win_width / 2.0f > getFirstDoor())
    viewCenterX = getFirstDoor() - m_win_width  / 2.0f;
  else
    viewCenterX = m_player->getGlobalBounds().left + m_player->getGlobalBounds().width / 2;

  sf::Vector2f viewPosition(viewCenterX, (m_win_height + m_info_height) / 2);

  sf::View view(viewPosition, viewSize);

  //window.clear();
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
    m_balls.push_back(std::make_unique<Ball>((size_t(type) - '0'), m_obj_width, position,
                                              m_win_height - m_obj_height, 1)); break;

  case ObjectType::WALL:
    m_walls.push_back(std::make_unique<Wall>(position, m_obj_width, m_obj_height)); break;

  case ObjectType::DOOR:
    m_doors.push_back(std::make_unique<Door>(position, m_obj_width, m_obj_height)); break;
  }
}

void Level::createBullet()
{
  auto middle_player_position = sf::Vector2f(m_player->getGlobalBounds().left + 
                                             m_player->getGlobalBounds().width / 2,
                                             m_player->getGlobalBounds().top +
                                             m_player->getGlobalBounds().height / 2);
  m_bullets.push_back(std::make_unique<GunWeapon>(50, middle_player_position));
}

void Level::movePlayer()
{
  auto direction = sf::Keyboard::isKeyPressed(sf::Keyboard::Left) ? -1
                 : sf::Keyboard::isKeyPressed(sf::Keyboard::Right) ? 1 : 0;

  if (!direction) return;

  m_player->setDirection(direction);

  m_player->moveObject(/*sf::Vector2f(m_world_width, m_win_height)*/);
//  for (auto &wall : m_walls)
//    if (wall->collidesWith(*m_player))
  bool go_back = false;
  std::for_each(m_walls.begin(), m_walls.end(), [&](auto &wall)
  { if (wall->collidesWith(*m_player)) go_back = true; });
  std::for_each(m_doors.begin(), m_doors.end(), [&](auto &door)
  { if (door->collidesWith(*m_player)) go_back = true; });

  if (go_back)
  {
    m_player->setDirection(direction * -1);
    m_player->moveObject(/*sf::Vector2f(m_world_width, m_win_height)*/);
  }
}

void Level::moveBalls()
{
  for (auto &ball : m_balls)
    ball->moveObject(/*sf::Vector2f(m_world_width, m_win_height)*/);
}

void Level::moveBullets()
{
  for (auto &bullet : m_bullets)
    bullet->moveObject(/*sf::Vector2f(m_world_width, m_win_height)*/);
}

void Level::erase()
{
  std::erase_if(m_bullets, [](const auto &bullet) { return bullet->isDel(); });
  std::erase_if(m_balls, [](const auto &ball) { return ball->isDel(); });
  openDoor();
}

void Level::openDoor()
{
  auto first_ball = std::min_element(m_balls.begin(), m_balls.end(),
    [](const auto& ball1, const auto& ball2) -> bool {
      return ball1->getGlobalBounds().left < ball2->getGlobalBounds().left; });

  auto first_door_pos = getFirstDoor();

  //std::cout << "first_door_pos - " << first_door_pos << "\n";

  if (m_doors.empty() || (!m_balls.empty() && first_door_pos > first_ball->get()->getGlobalBounds().left))
    return;
  
  std::erase_if(m_doors, [&first_door_pos](const auto& door) { 
    return door->getGlobalBounds().left + door->getGlobalBounds().width == first_door_pos; });
}

void Level::splitBall()
{
  for (auto i = size_t(0); i < m_balls.size(); ++i)
    if (m_balls[i]->isDel() && m_balls[i]->getRatio() > 1)
    {
      m_balls.push_back(std::make_unique<Ball>(m_balls[i]->getRatio() - 1, m_obj_width,
              sf::Vector2f(m_balls[i]->getGlobalBounds().left + m_balls[i]->getGlobalBounds().width / 2,
                           m_balls[i]->getGlobalBounds().top + m_balls[i]->getGlobalBounds().height / 2),
                           m_win_height - m_obj_height, 1));
      m_balls.push_back(std::make_unique<Ball>(m_balls[i]->getRatio() - 1, m_obj_width,
              sf::Vector2f(m_balls[i]->getGlobalBounds().left + m_balls[i]->getGlobalBounds().width / 2,
                           m_balls[i]->getGlobalBounds().top + m_balls[i]->getGlobalBounds().height / 2),
                           m_win_height - m_obj_height, -1));
    }
}

void Level::pause()
{
  TimerManager::Timer().startPause();
}

void Level::handleCollision()
{
  for (auto &ball : m_balls)
  {
    std::for_each(m_walls.begin(), m_walls.end(),
                  [&ball](const auto& wall){if (wall->collidesWith(*ball)) wall->collide(*ball); });
    std::for_each(m_doors.begin(), m_doors.end(),
                  [&ball](const auto& door){if (door->collidesWith(*ball)) door->collide(*ball); });
    std::for_each(m_bullets.begin(), m_bullets.end(),
                  [&ball](const auto& bullet){if (bullet->collidesWith(*ball)) bullet->collide(*ball);});
    if (m_player->collidesWith(*ball)) m_player->collide(*ball);
  }
  for (auto &bullet : m_bullets)
    std::for_each(m_walls.begin(), m_walls.end(),
                  [&bullet](const auto& wall){if (wall->collidesWith(*bullet)) wall->collide(*bullet); });
}

float Level::getFirstDoor() const
{
  auto first_door = std::min_element(m_doors.begin(), m_doors.end(),
                    [](const auto& door1, const auto& door2) -> bool {
                    return door1->getGlobalBounds().left < door2->getGlobalBounds().left; });

  return m_doors.empty()? 0 : 
    first_door->get()->getGlobalBounds().left + first_door->get()->getGlobalBounds().width;
}
