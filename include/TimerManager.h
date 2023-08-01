#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <iomanip>
#include <sstream>

//-------------------------------------------------------------------
class TimerManager
{
public:
  static TimerManager& Timer()
  {
    static auto m_timer = TimerManager();
    return m_timer;
  }

  //-------------------------------------------------------------------
  TimerManager(const TimerManager&) = delete;
  void operator=(const TimerManager&) = delete;

  //-------------------------------------------------------------------

//  void printTime() const
//  {
//    std::cout << m_elapsed_time << std::endl;
//  }

  float getDeltaTime() const
  {
    return m_delta_time;
  }

  void updateTimer()
  {
    if (m_pause)
    {
      m_clock.restart();
      m_pause = false;
    }
    m_delta_time = m_clock.restart().asSeconds();
    m_elapsed_time += m_delta_time;
  }

  void startPause()
  {
    m_pause = true;
  }

  std::string getRemainingTime(float level_time)
  {
    size_t remaining_time = level_time - m_elapsed_time;

    auto minutes = remaining_time / 60 % 60;
    auto seconds = remaining_time % 60;

    std::stringstream ss;
    ss << std::setfill('0') << std::setw(2) << minutes << ":"
       << std::setfill('0') << std::setw(2) << seconds;

    return ss.str();
  };

  void resetClock()
  {
    m_clock.restart();
    m_delta_time = 0;
    m_elapsed_time = 0;
  }

  float getElapsedTime() const
  {
    return m_elapsed_time;
  }

private:
  TimerManager()
  {
    m_clock.restart();
  }

  //-------------------------------------------------------------------
  sf::Clock m_clock;
  float m_delta_time, m_elapsed_time;
  bool m_pause;
};
