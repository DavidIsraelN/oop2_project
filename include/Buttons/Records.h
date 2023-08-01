#pragma once
#include "Button.h"

class Records : public Button
{
public:
  Records(float, float);
  Action action(sf::RenderWindow&) override;
  size_t getRecord() const;
  void updateRecord(size_t);

private:
  size_t m_record;
};

