#include "Level.h"
#include "EnumAndMacroes.h"
#include "Objects/Gifts/LifeGift.h"
#include "Objects/Gifts/TimeGift.h"
#include "Objects/GunWeapon.h"
#include "Sound.h"
#include "TimerManager.h"
#include <algorithm>
#include <exception>
#include <memory>
#include <vector>

//-------------------------------------------------------------------
Level::Level(float win_width, float win_height)
  : m_win_width(win_width), m_win_height(win_height),
   m_old_view_x(win_width / 2)
{
  srand(time(0));
}

//-------------------------------------------------------------------
void Level::loadLevel(Action level, bool new_game)
{
  clearLevel(new_game);
  setLevel(level, new_game);
  TimerManager::Timer().resetClock();
}

//-------------------------------------------------------------------
void Level::clearLevel(bool new_game)
{
  disqualification = false;
  m_bullet_time = -1.f;
  m_old_view_x = m_win_width / 2;
  m_balls.clear();
  m_bullets.clear();
  m_walls.clear();
  m_doors.clear();
  m_gifts.clear();
  if (new_game) m_player.release();
}

//-------------------------------------------------------------------
void Level::setLevel(Action level, bool new_game)
{
  m_level_num = size_t(level) + 1;
  m_current_board = std::make_unique<LevelReader>(ResourceManager::Resource().getTxtFile(TxtIndex(level)));
  m_current_board->setDimensions();
  m_background = sf::Sprite(ResourceManager::Resource().getBackgroundTexture(BackgroundIndex(level)));
  buildLevel(new_game);
  m_current_board->backToStart();
  m_original_balls = m_balls;
}

//-------------------------------------------------------------------
void Level::buildLevel(bool new_game)
{
  m_obj_height = float(m_win_height) / m_current_board->getRows();
  m_obj_width = float(m_win_width) / m_current_board->getWindowCols();
  m_world_width = m_obj_width * m_current_board->getWorldCols();
  m_background.setScale(m_world_width / m_background.getGlobalBounds().width,
                        m_win_height / m_background.getGlobalBounds().height);

  for (auto i = size_t(0); i < m_current_board->getRows(); ++i)
    for (auto j = size_t(0); j < m_current_board->getWorldCols(); ++j)
    {
      char c = m_current_board->getChar();
      if (c == char(ObjectType::SPACE)) continue;
      addObject(ObjectType(c), i, j, new_game);
    }
}

//-------------------------------------------------------------------
void Level::addObject(ObjectType type, size_t i, size_t j, bool new_game)
{
  auto x_pos = m_obj_width * j + m_obj_width / 2;
  auto y_pos = m_obj_height * i + m_obj_height / 2;
  auto position = sf::Vector2f({ x_pos, y_pos });

  switch (type)
  {
  case ObjectType::PLAYER:
    if (new_game)
      m_player = std::make_unique<Player>(position, m_obj_width, m_obj_height);
    else
      m_player->setPosition(position);
  break;

  case ObjectType::BALL_1:
  case ObjectType::BALL_2:
  case ObjectType::BALL_3:
  case ObjectType::BALL_4:
    m_balls.emplace_back(std::make_shared<Ball>((size_t(type) - '0'), m_obj_width, position,
                                              m_win_height - 2 * m_obj_height, 1)); break;

  case ObjectType::WALL:
    m_walls.emplace_back(std::make_unique<Wall>(position, m_obj_width, m_obj_height)); break;

  case ObjectType::DOOR:
    m_doors.emplace_back(std::make_unique<Door>(position, m_obj_width, m_obj_height)); break;

  default:
    throw std::invalid_argument("invalid character\n");
  }
}

//-------------------------------------------------------------------
void Level::resetLevel()
{
  m_bullet_time = -1.f;
  m_player->setOriginalState();
  m_bullets.clear();
  m_balls.clear();
  m_balls = m_original_balls;
  std::for_each(m_balls.begin(), m_balls.end(), [](auto &ball){ball->setOriginalState();});
  disqualification = false;
}

//-------------------------------------------------------------------
sf::View Level::currentView()
{
  auto player_position = m_player->getGlobalBounds().left + m_player->getGlobalBounds().width / 2;
  auto viewSize = sf::Vector2f(m_win_width, m_win_height);
  float viewCenterX;

  if (player_position - m_win_width / 2.f < 0)
    viewCenterX = m_win_width / 2.f;
  else if (player_position + m_win_width / 2.f > getFirstDoor())
    viewCenterX = getFirstDoor() - m_win_width / 2.f;
   else if (player_position - m_old_view_x > 20.f)
    viewCenterX = m_old_view_x + 1.f;
  else
    viewCenterX = player_position;

  m_old_view_x = viewCenterX;
  sf::Vector2f viewPosition(viewCenterX, (m_win_height) / 2);
  return sf::View(viewPosition, viewSize);
}

//-------------------------------------------------------------------
void Level::draw(sf::RenderWindow& window)
{
  window.setView(currentView());
  window.draw(m_background);

  std::for_each(m_bullets.begin(), m_bullets.end(), [&window] (auto &bullet) {bullet->draw(window);});
  std::for_each(m_gifts.begin(), m_gifts.end(), [&window] (auto &gift) {gift->draw(window);});
  m_player->draw(window);
  std::for_each(m_walls.begin(), m_walls.end(), [&window] (auto &wall) {wall->draw(window);});
  std::for_each(m_doors.begin(), m_doors.end(), [&window] (auto &door) {door->draw(window);});
  std::for_each(m_balls.begin(), m_balls.end(), [&window] (auto &ball) {ball->draw(window);});
  if (m_is_boom) window.draw(m_boom);
  window.setView(window.getDefaultView());
}

//-------------------------------------------------------------------
void Level::createBullet()
{
  if (TimerManager::Timer().getElapsedTime() - m_bullet_time < BULLET_DELAY)
    return;

  m_player->setShut();
  auto player_rifle_position = sf::Vector2f(
    m_player->getGlobalBounds().left + m_player->getGlobalBounds().width / 2,
    m_player->getGlobalBounds().top + m_player->getGlobalBounds().height / 2);

  auto position_accuracy = sf::Vector2f(player_rifle_position.x + m_player->getGlobalBounds().width / 9.5f,
                                        player_rifle_position.y - m_player->getGlobalBounds().height / 2.5f);

  m_bullets.emplace_back(std::make_unique<GunWeapon>(position_accuracy));
  m_bullet_time = TimerManager::Timer().getElapsedTime();
  Sound::Sounds().Play(SoundIndex::SHUT);
}

//-------------------------------------------------------------------
void Level::createGift(sf::Vector2f position)
{
  auto gift = rand() % 15;
  switch (gift)
  {
  case 0:
    m_gifts.emplace_back(std::make_unique<TimeGift>(position, m_win_height - 2 * m_obj_height));
    break;

  case 1:
    m_gifts.emplace_back(std::make_unique<LifeGift>(position, m_win_height - 2 * m_obj_height));
    break;

  default:
    return;
  }
}


//-------------------------------------------------------------------
void Level::movePlayer()
{
  auto direction = sf::Keyboard::isKeyPressed(sf::Keyboard::Left) ? LEFT_DIRECTION
    : sf::Keyboard::isKeyPressed(sf::Keyboard::Right) ? RIGHT_DIRECTION : STAND;

  m_player->setDirection(direction);
  m_player->setAnimation();
  if (!direction) return;

  m_player->moveObject();
  bool go_back = false;
  std::for_each(m_walls.begin(), m_walls.end(), [&](auto& wall)
    { if (wall->collidesWith(*m_player)) go_back = true; });
  std::for_each(m_doors.begin(), m_doors.end(), [&](auto& door)
    { if (door->collidesWith(*m_player)) go_back = true; });

  if (go_back)
  {
    m_player->setDirection(direction * -1);
    m_player->moveObject();
  }
}

//-------------------------------------------------------------------
void Level::moveBalls()
{
  std::for_each(m_balls.begin(), m_balls.end(), [](auto& ball){ball->moveObject();});
}

//-------------------------------------------------------------------
void Level::moveBullets()
{
  std::for_each(m_bullets.begin(), m_bullets.end(), [](auto& bullet) {bullet->moveObject();});
}

//-------------------------------------------------------------------
void Level::moveGifts()
{
  std::for_each(m_gifts.begin(), m_gifts.end(), [](auto& gift) {gift->moveObject();});
}

//-------------------------------------------------------------------
void Level::erase(bool& door_opened)
{
  std::erase_if(m_bullets, [](const auto &bullet) {return bullet->isDel();});
  std::erase_if(m_balls, [](const auto& ball) {return ball->isDel();});
  std::erase_if(m_gifts, [](const auto& gift) {return gift->isDel();});
  openDoor(door_opened);
}

//-------------------------------------------------------------------
void Level::openDoor(bool& door_opened)
{
  auto first_ball = std::min_element(m_balls.begin(), m_balls.end(),
    [](const auto& ball1, const auto& ball2) -> bool {
      return ball1->getGlobalBounds().left < ball2->getGlobalBounds().left; });

  auto first_door_pos = getFirstDoor();

  if (m_doors.empty() || (!m_balls.empty() && first_door_pos > first_ball->get()->getGlobalBounds().left))
    return;

  auto old_size = m_doors.size();

  std::erase_if(m_doors, [&first_door_pos](const auto& door) {
    return door->getGlobalBounds().left + door->getGlobalBounds().width == first_door_pos; });

  door_opened = m_doors.size() && old_size - m_doors.size();
}

//-------------------------------------------------------------------
void Level::splitBall()
{
  // create boom:
  m_boom_timer -= TimerManager::Timer().getDeltaTime();
  if (m_boom_timer <= 0) m_is_boom = false;

  for (auto i = size_t(0); i < m_balls.size(); ++i)
    if (m_balls[i]->isDel())
    {
      m_boom = sf::Sprite(ResourceManager::Resource().getTexture(TextureIndex::SPRITE_SEET));
      m_boom.setTextureRect(ResourceManager::Resource().getTextureRect(StaticObjIndex::BOOM));
      m_boom.setPosition(m_balls[i]->getGlobalBounds().left - m_balls[i]->getGlobalBounds().width / 6,
                         m_balls[i]->getGlobalBounds().top - m_balls[i]->getGlobalBounds().height / 5);
      m_boom.setScale(m_balls[i]->getGlobalBounds().width / m_boom.getGlobalBounds().width * 1.3f,
                      m_balls[i]->getGlobalBounds().height / m_boom.getGlobalBounds().height * 1.3f);
      m_boom_timer = BOOM_TIMER;
      m_is_boom = true;
      break;
    } // end create boom

  // create gift
  for (auto i = size_t(0); i < m_balls.size(); ++i)
    if (m_balls[i]->isDel())
    {
      createGift(sf::Vector2f(m_balls[i]->getGlobalBounds().left + m_balls[i]->getGlobalBounds().width / 2,
                              m_balls[i]->getGlobalBounds().top + m_balls[i]->getGlobalBounds().height / 2));
      break;
    } // end create gift


  for (auto i = size_t(0); i < m_balls.size(); ++i)
    if (m_balls[i]->isDel() && m_balls[i]->getRatio() > 1)
    {
      m_balls.emplace_back(std::make_shared<Ball>(m_balls[i]->getRatio() - 1, m_obj_width,
        sf::Vector2f(m_balls[i]->getGlobalBounds().left + m_balls[i]->getGlobalBounds().width / 2,
                     m_balls[i]->getGlobalBounds().top + m_balls[i]->getGlobalBounds().height / 2),
        m_win_height - 2 * m_obj_height, 1));

      m_balls.emplace_back(std::make_shared<Ball>(m_balls[i]->getRatio() - 1, m_obj_width,
        sf::Vector2f(m_balls[i]->getGlobalBounds().left + m_balls[i]->getGlobalBounds().width / 2,
                     m_balls[i]->getGlobalBounds().top + m_balls[i]->getGlobalBounds().height / 2),
        m_win_height - 2 * m_obj_height, -1));
    }
}

//-------------------------------------------------------------------
void Level::pause()
{
  TimerManager::Timer().startPause();
}

//-------------------------------------------------------------------
void Level::handleCollision()
{
  disqualification = false;
  for (auto &ball : m_balls)
  {
    std::for_each(m_bullets.begin(), m_bullets.end(), [&] (const auto& bullet) {
      if (bullet->collidesWith(*ball)) {
      m_player->incOrDecScore(BALLS_KIND + 1 - ball->getRatio()); bullet->collide(*ball);} });

    std::for_each(m_walls.begin(), m_walls.end(), [&ball] (const auto& wall) {
      if (wall->collidesWith(*ball)) wall->collide(*ball); });

    std::for_each(m_doors.begin(), m_doors.end(), [&ball] (const auto& door) {
      if (door->collidesWith(*ball)) door->collide(*ball); });

    if (m_player->collidesWith(*ball))
    {
      m_player->collide(*ball);
      resetLevel();
      disqualification = true;
      return;
    }
  }

  for (auto &bullet : m_bullets)
    std::for_each(m_walls.begin(), m_walls.end(), [&bullet] (const auto& wall) {
      if (wall->collidesWith(*bullet)) wall->collide(*bullet); });

  for (auto &gift : m_gifts)
    if (m_player->collidesWith(*gift)) gift->collide(*m_player);
}

//-------------------------------------------------------------------
float Level::getFirstDoor() const
{
  auto first_door = std::min_element(m_doors.begin(), m_doors.end(),
    [](const auto& door1, const auto& door2) -> bool {
      return door1->getGlobalBounds().left < door2->getGlobalBounds().left; });

  return m_doors.empty() ? m_world_width :
    first_door->get()->getGlobalBounds().left + first_door->get()->getGlobalBounds().width;
}

//-------------------------------------------------------------------
void Level::updateStatusBar(StatusBar& status_bar)
{
  TimerManager::Timer().updateTimer();
  status_bar.setTime();
  status_bar.setScore(m_player->getScore());
  status_bar.setLevel(m_level_num);
  status_bar.setLife(m_player->getLife());
  if (status_bar.getRemainingTime() <= 0)
  {
    TimerManager::Timer().resetClock();
    m_player->decreaseLife();
    resetLevel();
    disqualification = true;
  }
}

//-------------------------------------------------------------------
bool Level::levelOver()
{
  auto over = m_player->getGlobalBounds().left > m_world_width;
  if (over) m_player->incOrDecScore(NEXT_LEVEL_SCORE);
  return over;
}

//-------------------------------------------------------------------
bool Level::lifeEnd() const
{
  return m_player->getLife() <= 0;
}

//-------------------------------------------------------------------
size_t Level::getLevelNum() const
{
  return m_level_num;
}

//-------------------------------------------------------------------
bool Level::isDisqualification() const
{
  return disqualification;
};

//-------------------------------------------------------------------
size_t Level::getScore() const
{
  return m_player->getScore();
}

//-------------------------------------------------------------------
float Level::getObjHeight() const
{
  return m_obj_height;
}
