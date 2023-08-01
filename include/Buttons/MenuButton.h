#pragma once
#include "Button.h"

class MenuButton : public Button
{
public:
  MenuButton(float, float);
  Action action(sf::RenderWindow&) override;
private:

};

