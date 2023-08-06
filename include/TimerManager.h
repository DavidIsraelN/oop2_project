#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <iomanip>
#include <sstream>

/* ------------------------------------------------------------------
 * Singleton - Timer class for all program timers.
 * Create the Timer of the program once and get to him from anywhere in the program.
 */

//-------------------------------------------------------------------
class TimerManager
{
public:
  static TimerManager& Timer();
  TimerManager(const TimerManager&) = delete;
  void operator=(const TimerManager&) = delete;
  float getDeltaTime() const;
  void updateTimer();
  void startPause();
  std::string getRemainingTime(float level_time);
  void resetClock();
  float getElapsedTime() const;

private:
  TimerManager();

  sf::Clock m_clock;
  float m_delta_time = 0, m_elapsed_time = 0;
  bool m_pause = false;
};
