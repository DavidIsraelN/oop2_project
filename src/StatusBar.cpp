#include "StatusBar.h"
#include <iostream>
#include "ResourcesManager.h"
#include "TimerManager.h"

StatusBar::StatusBar(float bar_width, float bar_y, float bar_height)
    : m_width(bar_width), m_height(bar_height), m_rectangle(sf::Vector2f(m_width, m_height)),
      m_timer("00:00", ResourceManager::Resource().getFont(FontIndex::ARIEL),bar_height / 2),
      m_level("LEVEL  ", ResourceManager::Resource().getFont(FontIndex::ARIEL),bar_height / 2),
      m_score("SCORE  ", ResourceManager::Resource().getFont(FontIndex::ARIEL),bar_height / 2)
{
  setStatusBar(bar_y);
}

void StatusBar::setStatusBar(float bar_y)
{
  m_rectangle.setPosition(0, bar_y);
  m_rectangle.setFillColor(sf::Color::Blue);

  m_timer.setFillColor(sf::Color::White);
  m_score.setFillColor(sf::Color::White);
  m_level.setFillColor(sf::Color::White);

  m_timer.setPosition(m_width / 2, bar_y + m_height / 4);
  m_score.setPosition(3 * m_width / 4, bar_y + m_height / 4);
  m_level.setPosition(m_width / 4, bar_y + m_height / 4);

  m_timer.setOrigin(m_timer.getLocalBounds().width / 2,0);
  m_score.setOrigin(m_score.getLocalBounds().width / 2,0);
  m_level.setOrigin(m_level.getLocalBounds().width / 2,0);
}

void StatusBar::setTime()
{
  m_timer.setString(TimerManager::Timer().getRemainingTime(m_level_time));
}

void StatusBar::setLevel(size_t)
{
}

void StatusBar::draw(sf::RenderWindow& window) const
{
  window.draw(m_rectangle);
  window.draw(m_level);
  window.draw(m_score);
  window.draw(m_timer);
}