#include "TimerManager.h"

//-------------------------------------------------------------------
TimerManager::TimerManager()
{
  m_clock.restart();
}

//-------------------------------------------------------------------
TimerManager& TimerManager::Timer()
{
  static auto m_timer = TimerManager();
  return m_timer;
}

//-------------------------------------------------------------------
float TimerManager::getDeltaTime() const
{
  return m_delta_time;
}

//-------------------------------------------------------------------
void TimerManager::updateTimer()
{
  if (m_pause)
  {
    m_clock.restart();
    m_pause = false;
  }
  m_delta_time = m_clock.restart().asSeconds();
  m_elapsed_time += m_delta_time;
}

//-------------------------------------------------------------------
void TimerManager::startPause()
{
  m_pause = true;
}

//-------------------------------------------------------------------
std::string TimerManager::getRemainingTime(float level_time)
{
  size_t remaining_time = level_time + m_additional_time - m_elapsed_time;

  auto minutes = remaining_time / 60 % 60;
  auto seconds = remaining_time % 60;

  std::stringstream ss;
  ss << std::setfill('0') << std::setw(2) << minutes << ":"
    << std::setfill('0') << std::setw(2) << seconds;

  return ss.str();
};

//-------------------------------------------------------------------
void TimerManager::resetClock()
{
  m_clock.restart();
  m_delta_time = 0;
  m_elapsed_time = 0;
  m_additional_time = 0;
}

//-------------------------------------------------------------------
float TimerManager::getElapsedTime() const
{
  return m_elapsed_time;
}

void TimerManager::addTime(float additional_time)
{
  m_additional_time += additional_time;
}