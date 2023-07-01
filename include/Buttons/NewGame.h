#pragma once
#include "Button.h"

enum class Action;

class NewGame : public Button
{
public:
  NewGame(float, float);
  Action action(sf::RenderWindow&) override;

  void drawLevels(sf::RenderWindow&) const;
  //void action() override;
  void createLevelButtons();

private:
  sf::Text m_text_title;
  std::vector<std::unique_ptr<Button>> m_levels;
};

