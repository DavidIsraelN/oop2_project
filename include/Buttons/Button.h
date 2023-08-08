#pragma once
#include "EnumAndMacroes.h"
#include <SFML/Graphics.hpp>

/* ----------------------------------------------------------
 * an abstract class that is responsible for all the buttons.
 */

//enum class Action;

class Button
{
public:
  Button(const sf::Vector2f&, const sf::Vector2f&, const std::string&, Action = Action::NOTHING);
  virtual ~Button() { };
  void draw(sf::RenderWindow&) const;
  virtual Action action(sf::RenderWindow&) = 0;
  bool clickMe(const sf::Vector2f&) const;

protected:
  Action getAction() const;
  sf::Text m_text;

private:
  void setButton(const sf::Vector2f&, const sf::Vector2f&);

  Action m_action;
  sf::RectangleShape m_rectangle;
};

