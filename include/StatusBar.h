#pragma once
#include <SFML/Graphics.hpp>

class StatusBar
{
public:
  StatusBar(float, float);
  void draw(sf::RenderWindow&) const;
  void setLife(size_t);
  void setTime();
  void setLevel(size_t);
  void setScore(size_t);
  void setStatusBar(float);
  float getRemainingTime() const;
  bool timeOver() const;

private:
  float m_width, m_height, m_level_time = 180.f; // need to set time for level
  sf::RectangleShape m_rectangle;
  sf::Text m_timer, m_level, m_score, m_life;
};

