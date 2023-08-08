#include "StatusBar.h"
#include <iostream>
#include "ResourcesManager.h"
#include "TimerManager.h"
#include "Colors.h"

//-------------------------------------------------------------------
StatusBar::StatusBar(float bar_width, float win_height)
  : m_width(bar_width), m_height(win_height),
  m_timer("00:00",   ResourceManager::Resource().getFont()),
  m_level("LEVEL  ", ResourceManager::Resource().getFont()),
  m_score("SCORE:   ", ResourceManager::Resource().getFont()),
  m_life("LIFE:  ", ResourceManager::Resource().getFont())
{
  m_timer.setFillColor(sf::Color::White);
  m_score.setFillColor(sf::Color::White);
  m_level.setFillColor(sf::Color::White);
  m_life.setFillColor(sf::Color::White);

  m_timer.setOutlineThickness(2);
  m_score.setOutlineThickness(2);
  m_level.setOutlineThickness(2);
  m_life.setOutlineThickness(2);
}

//-------------------------------------------------------------------
void StatusBar::setStatusBar(float obj_height, size_t level_num)
{
  m_level_time = float(BASE_TIME * (level_num == 1 ? 1 : level_num == 2 ? 1.5 : 2));

  auto bar_height = 2 * obj_height;

  m_timer.setCharacterSize(bar_height / 2);
  m_score.setCharacterSize(bar_height / 2);
  m_life.setCharacterSize(bar_height / 2);
  m_level.setCharacterSize(obj_height / 1.2);

  m_timer.setPosition(m_width / 2, m_height - bar_height / 1.7);
  m_score.setPosition(19 * m_width / 24, m_height - bar_height / 1.7);
  m_life.setPosition(5 * m_width / 24, m_height - bar_height / 1.7);
  m_level.setPosition(m_width / 2, 0);

  m_timer.setOrigin(m_timer.getLocalBounds().width / 2, m_timer.getLocalBounds().height / 2);
  m_score.setOrigin(m_score.getLocalBounds().width / 2, m_score.getLocalBounds().height / 2);
  m_life.setOrigin(m_life.getLocalBounds().width / 2, m_life.getLocalBounds().height / 2);
  m_level.setOrigin(m_level.getLocalBounds().width / 2, 0);
}

//-------------------------------------------------------------------
void StatusBar::setTime()
{
  m_timer.setString(TimerManager::Timer().getRemainingTime(m_level_time));
  m_timer.setFillColor(getRemainingTime() <= 30 ? 
    sf::Color(181, 49, 60) : sf::Color::White);
}

//-------------------------------------------------------------------
void StatusBar::setLevel(size_t level)
{
  m_level.setString("LEVEL " + std::to_string(level));
}

//-------------------------------------------------------------------
void StatusBar::setScore(size_t score)
{
  m_score.setString("SCORE: " + std::to_string(score));
}

//-------------------------------------------------------------------
void StatusBar::setLife(size_t life)
{
  m_life.setString("LIFE: " + std::to_string(life));
}

//-------------------------------------------------------------------
void StatusBar::draw(sf::RenderWindow& window) const
{
  window.draw(m_rectangle);
  window.draw(m_level);
  window.draw(m_score);
  window.draw(m_life);
  window.draw(m_timer);
}

//-------------------------------------------------------------------
float StatusBar::getRemainingTime() const
{
  return m_level_time - TimerManager::Timer().getElapsedTime();
}

//-------------------------------------------------------------------
bool StatusBar::timeOver() const
{
  return getRemainingTime() <= 0;
}
