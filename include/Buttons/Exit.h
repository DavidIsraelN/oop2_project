#pragma once
#include "Button.h"

class Exit : public Button
{
public:
  Exit(float, float);
  Action action(sf::RenderWindow&) override;
private:

};

