#pragma once
#include "Button.h"

class ChooseLevel : public Button
{
public:
  ChooseLevel(const sf::Vector2f&, const sf::Vector2f&, Action);
  Action action(sf::RenderWindow&) override;
private:
};

