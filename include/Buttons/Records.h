#pragma once
#include "Button.h"

class Records : public Button
{
public:
  Records(float, float);
  Action action(sf::RenderWindow&) override;

private:

};

