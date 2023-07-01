#pragma once
#include "Button.h"

class Back : public Button
{
public:
  Back(const sf::Vector2f&, const sf::Vector2f&, Action);
  Action action(sf::RenderWindow&) override;
private:

};

