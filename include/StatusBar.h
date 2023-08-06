#pragma once
#include <SFML/Graphics.hpp>

/* ------------------------------------------------------------------
 * This class is responsible for the status bar of the game.
 * Presents level number, life, score and the time left to finish.
 */

const size_t BASE_TIME = 120; //seconds

class StatusBar
{
public:
  StatusBar(float, float);
  void draw(sf::RenderWindow&) const;
  void setLife(size_t);
  void setTime();
  void setLevel(size_t);
  void setScore(size_t);
  void setStatusBar(float, size_t);
  float getRemainingTime() const;
  bool timeOver() const;

private:
  float m_width, m_height, m_level_time = 0;
  sf::RectangleShape m_rectangle;
  sf::Text m_timer, m_level, m_score, m_life;
};
