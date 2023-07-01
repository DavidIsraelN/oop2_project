#pragma once
#include "Button.h"

class Help : public Button
{
public:
  Help(float, float);
  void draw(sf::RenderWindow&) const;
  Action action(sf::RenderWindow&) override;

private:
};

