#pragma once
#include <SFML/Graphics.hpp>

enum class Action;

class Button
{
public:
  Button(const sf::Vector2f&, const sf::Vector2f&, const std::string&);
  virtual ~Button() { };
  void draw(sf::RenderWindow&) const;
  virtual Action action(sf::RenderWindow&) = 0;
  bool clickMe(const sf::Vector2f&) const;

protected:
  Action m_action;
  sf::RectangleShape m_rectangle;
  sf::Text m_text;
};

